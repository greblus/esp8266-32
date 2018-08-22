import network 
import socket
sta_if = network.WLAN(network.STA_IF) 
addr = socket.getaddrinfo(sta_if.ifconfig()[0], 8000)[0][-1]
s = socket.socket()
s.bind(addr)
s.listen(1)
print('listening on', addr)

import machine
pin = machine.Pin(5, machine.Pin.OUT)
status = True
pin.value(status)

import uasyncio as asyncio
loop = asyncio.get_event_loop()

async def sleep(mins):
    global status
    endtime = loop.time() + mins*1000*60
    while True:
        if (loop.time() + 1.0) >= endtime:
                break
        await asyncio.sleep(0.1)
    status = False
    pin.value(status)
    print('sleep finished')

async def worker():
    global status
    while True:
        cl, addr = s.accept()
        print('client connected from', addr)
        cl_file = cl.makefile('rwb', 0)
        while True:
            line = cl_file.readline()
            if line:
                break
            await asyncio.sleep(0.1)
        print(line, status)
        if line.find(b'onoff') >= 0:
            status = not status
            pin.value(status)
        if line.find(b'sleep') >= 0:
            s1 = line.find(b'sleep')+6
            s2 = line.find(b'H')-1
            try:
                timeout = int(line[s1:s2])
                await sleep(timeout)
            except ValueError:
                print('/sleep needs a numeric timeout')
        cl.close()
        await asyncio.sleep(0.1)

loop.create_task(worker())
loop.run_forever()

# vim: tabstop=8 expandtab shiftwidth=4 softtabstop=4
