import network 
import time
import _thread

sta_if = network.WLAN(network.STA_IF) 
if not sta_if.isconnected():
    sta_if.ifconfig(('address','netmask','gw','dns'))
    sta_if.active(True)
    sta_if.connect("ap", "pass")
    while not sta_if.isconnected():
        time.sleep(1)

import socket
addr = socket.getaddrinfo(sta_if.ifconfig()[0], 8000)[0][-1]
s = socket.socket()
s.bind(addr)
s.listen(1)
print('listening on', addr)

import machine
pin = machine.Pin(22, machine.Pin.OUT)
status = False
pin.value(status)

def sleep(mins):
    global status
    time.sleep(mins*60)
    status = True
    pin.value(True)

while True:
    cl, addr = s.accept()
    print('client connected from', addr)
    cl_file = cl.makefile('rwb', 0)
    while True:
        line = cl_file.readline()
        if line:
            break
    print(line, status)
    if line.find(b'onoff') >= 0:
        status = not status
        pin.value(status)
    if line.find(b'sleep') >= 0:
        s1 = line.find(b'sleep')+6
        s2 = line.find(b'H')-1
        try:
            timeout = int(line[s1:s2])
            _thread.start_new_thread(sleep, (timeout,))
        except ValueError:
            print('/sleep needs a numeric timeout')
    cl.close()
    
# vim: tabstop=8 expandtab shiftwidth=4 softtabstop=4
