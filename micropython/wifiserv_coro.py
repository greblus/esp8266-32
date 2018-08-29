import network 
import usocket as socket
import errno

sta_if = network.WLAN(network.STA_IF) 
addr = socket.getaddrinfo(sta_if.ifconfig()[0], 8000)[0][-1]
s = socket.socket()
s.setblocking(False)
s.bind(addr)
s.listen(1)
print('listening on', addr)

import machine
pin = machine.Pin(5, machine.Pin.OUT)
status = True; timeout = None
pin.value(status)

import uasyncio as asyncio
loop = asyncio.get_event_loop()

async def sleep(newtm):
    global status, timeout
    if timeout == newtm:
        return
    if timeout != None:
        timeout = newtm
        return
    else:
        timeout = newtm
    while timeout > 0:
        await asyncio.sleep(60)
        timeout = timeout - 60
    status = False; timeout = None
    pin.value(status)

async def worker():
    global status
    while True:
        line = None
        try:
            cl, addr = s.accept()
            print('client connected from', addr)
            cl_file = cl.makefile('rwb', 0)
            while not line:
                line = cl_file.readline()
        except OSError as exc:
            if exc.args[0] in [errno.ETIMEDOUT, errno.EAGAIN]:
                await asyncio.sleep(0)
                continue
        print(line, status)
        if 'onoff' in line:
            status = not status
            pin.value(status)
        if 'sleep' in line:
            s1 = line.find(b'sleep')+6
            s2 = line.find(b'H')-1
            try:
                timeout = int(line[s1:s2])
                loop.create_task(sleep(timeout*60))
            except ValueError:
                print('/sleep needs a numeric timeout')
        cl.close()

loop.create_task(worker())
loop.run_forever()

# vim: tabstop=8 expandtab shiftwidth=4 softtabstop=4
