from threading import Thread, Lock
import threading as trd
from gpiozero import LED
import time, socket

addr = socket.getaddrinfo('0.0.0.0', 2310)[0][-1]
s = socket.socket()
s.bind(addr)
s.listen(1)

mutex_l3 = Lock()
mutex_l5 = Lock()
mutex_l4 = Lock()
mutex_l6 = Lock()
mutex_l10 = Lock()

t1_s = 5
t2_s = 5
t3_s = 5
t4_s = 5

debug = 0

t1_l = [1,2,3,4]
t2_l = [7,5,6,3]
t3_l = [8,9,10,5]
t4_l = [13,11,4,6,10,12]

### leds do trem verde
l1_led = LED(2)
l2_led = LED(3)
l3vd_led = LED(4)
l4vd_led = LED(15)

### leds do trem azul
l3az_led = LED(14)
l7_led = LED(24)
l5az_led = LED(17)
l6az_led = LED(22)

### leds do trem amarelo
l5am_led = LED(27)
l8_led = LED(10)
l9_led = LED(9)
l10am_led = LED(11)

### leds do trem vermelho
l13_led = LED(5)
l11_led = LED(8)
l4vm_led = LED(18)
l6vm_led = LED(23)
l10vm_led = LED(25)
l12_led = LED(6)

class connIn(trd.Thread):
    def __init__(self, conn):
        global t1_s
        global t2_s
        global t3_s
        global t4_s

        trd.Thread.__init__(self)
        request = conn.recv(1024)
        r_decoded = request.decode('utf-8')
        t1_s = int(r_decoded[1])
        t2_s = int(r_decoded[4])
        t3_s = int(r_decoded[7])
        t4_s = int(r_decoded[10])
        conn.close()

def trem1():
    global t1_s

    while True:
        for l in t1_l:
            time.sleep(t1_s*0.2)
            if l == 3:
                if (mutex_l3.locked() or mutex_l6.locked()) and debug:
                    print('t1 esperando l3 ficar livre')
                while mutex_l3.locked() or mutex_l6.locked():
                    pass
                if debug:
                    print('t1 encontrou l3 livre')
                mutex_l3.acquire()
            if l == 4:
                if mutex_l4.locked() and debug:
                    print('t1 esperando l4 ficar livre')
                while mutex_l4.locked() == True:
                    pass
                if debug:
                    print('t1 encontrou l4 livre')
                mutex_l4.acquire()
                if mutex_l3.locked():
                    if debug:
                        print('t1 liberou l3')
                    mutex_l3.release()
            if l == 1:
                if mutex_l4.locked():
                    if debug:
                        print('t1 liberou l4')
                    mutex_l4.release()
            print('t1: ' + str(l))
            if l == 1:
                l1_led.on()
                l2_led.off()
                l3vd_led.off()
                l4vd_led.off()
            if l == 2:
                l1_led.off()
                l2_led.on()
                l3vd_led.off()
                l4vd_led.off()
            if l == 3:
                l1_led.off()
                l2_led.off()
                l3vd_led.on()
                l4vd_led.off()
            if l == 4:
                l1_led.off()
                l2_led.off()
                l3vd_led.off()
                l4vd_led.on()

def trem2():
    global t2_s

    while True:
        for l in t2_l:
            time.sleep(t2_s*0.2)
            if l == 3:
                if mutex_l3.locked() and debug:
                    print('t2 esperando l3 ficar livre')
                while mutex_l3.locked() == True:
                    pass
                if debug:
                    print('t2 encontrou l3 livre')
                mutex_l3.acquire()
                if mutex_l6.locked():
                    if debug:
                        print('t2 liberou l6')
                    mutex_l6.release()
            if l == 6:
                if (mutex_l6.locked() or mutex_l3.locked() or mutex_l4.locked()) and debug:
                    print('t2 esperando l6 ficar livre')
                while mutex_l6.locked() or mutex_l3.locked() or mutex_l4.locked():
                    pass
                if debug:
                    print('t2 encontrou l6 livre')
                mutex_l6.acquire()
                if mutex_l5.locked():
                    if debug:
                        print('t2 liberou l5')
                    mutex_l5.release()
            if l == 5:
                if (mutex_l5.locked() or mutex_l10.locked()) and debug:
                    print('t2 esperando l5 ficar livre')
                while mutex_l5.locked() or mutex_l10.locked():
                    pass
                if debug:
                    print('t2 encontrou l5 livre')
                mutex_l5.acquire()
            if l == 7:
                if mutex_l3.locked():
                    if debug:
                        print('t2 liberou l3')
                    mutex_l3.release()
            print('t2: ' + str(l))
            if l == 3:
                l3az_led.on()
                l7_led.off()
                l5az_led.off()
                l6az_led.off()
            if l == 7:
                l3az_led.off()
                l7_led.on()
                l5az_led.off()
                l6az_led.off()
            if l == 5:
                l3az_led.off()
                l7_led.off()
                l5az_led.on()
                l6az_led.off()
            if l == 6:
                l3az_led.off()
                l7_led.off()
                l5az_led.off()
                l6az_led.on()

def trem3():
    global t3_s

    while True:
        for l in t3_l:
            time.sleep(t3_s*0.2)
            if l == 5:
                if mutex_l5.locked() and debug:
                    print('t3 esperando l5 ficar livre')
                while mutex_l5.locked() == True:
                    pass
                if debug:
                    print('t3 encontrou l5 livre')
                mutex_l5.acquire()
                if mutex_l10.locked():
                    if debug:
                        print('t3 liberou l10')
                    mutex_l10.release()
            if l == 10:
                if (mutex_l10.locked() or mutex_l5.locked() or mutex_l6.locked() or mutex_l4.locked()) and debug:
                    print('t3 esperando l10 ficar livre')
                while mutex_l10.locked() or mutex_l5.locked() or mutex_l6.locked() or mutex_l4.locked():
                    pass
                if debug:
                    print('t3 encontrou l10 livre')
                mutex_l10.acquire()
            if l == 8:
                if mutex_l5.locked():
                    if debug:
                        print('t3 liberou l5')
                    mutex_l5.release()
            print('t3: ' + str(l))
            if l == 5:
                l5am_led.on()
                l8_led.off()
                l9_led.off()
                l10am_led.off()
            if l == 8:
                l5am_led.off()
                l8_led.on()
                l9_led.off()
                l10am_led.off()
            if l == 9:
                l5am_led.off()
                l8_led.off()
                l9_led.on()
                l10am_led.off()
            if l == 10:
                l5am_led.off()
                l8_led.off()
                l9_led.off()
                l10am_led.on()

def trem4():
    global t4_s

    while True:
        for l in t4_l:
            time.sleep(t4_s*0.2)
            if l == 4:
                if mutex_l4.locked() and debug:
                    print('t4 esperando l4 ficar livre')
                while mutex_l4.locked() == True:
                    pass
                if debug:
                    print('t4 encontrou l4 livre')
                mutex_l4.acquire()
            if l == 6:
                if mutex_l6.locked() and debug:
                    print('t4 esperando l6 ficar livre')
                while mutex_l6.locked() == True:
                    pass
                if debug:
                    print('t4 encontrou l6 livre')
                mutex_l6.acquire()
                if mutex_l4.locked():
                    if debug:
                        print('t4 liberou l4')
                    mutex_l4.release()
            if l == 10:
                if mutex_l10.locked() and debug:
                    print('t4 esperando l10 ficar livre')
                while mutex_l10.locked() == True:
                    pass
                if debug:
                    print('t4 encontrou l10 livre')
                mutex_l10.acquire()
                if mutex_l6.locked():
                    if debug:
                        print('t4 liberou l6')
                    mutex_l6.release()
            if l == 12:
                if mutex_l10.locked():
                    if debug:
                        print('t4 liberou l10')
                    mutex_l10.release()
            print('t4: ' + str(l))
            if l == 13:
                l13_led.on()
                l11_led.off()
                l4vm_led.off()
                l6vm_led.off()
                l10vm_led.off()
                l12_led.off()
            if l == 11:
                l13_led.off()
                l11_led.on()
                l4vm_led.off()
                l6vm_led.off()
                l10vm_led.off()
                l12_led.off()
            if l == 4:
                l13_led.off()
                l11_led.off()
                l4vm_led.on()
                l6vm_led.off()
                l10vm_led.off()
                l12_led.off()
            if l == 6:
                l13_led.off()
                l11_led.off()
                l4vm_led.off()
                l6vm_led.on()
                l10vm_led.off()
                l12_led.off()
            if l == 10:
                l13_led.off()
                l11_led.off()
                l4vm_led.off()
                l6vm_led.off()
                l10vm_led.on()
                l12_led.off()
            if l == 12:
                l13_led.off()
                l11_led.off()
                l4vm_led.off()
                l6vm_led.off()
                l10vm_led.off()
                l12_led.on()

t1 = Thread(target = trem1)
t1.start()
t2 = Thread(target = trem2)
t2.start()
t3 = Thread(target = trem3)
t3.start()
t4 = Thread(target = trem4)
t4.start()

try:
    while True:
        conn, addr = s.accept()
        if conn:
            serverIn = connIn(conn)
            serverIn.start()
finally:
    s.close()
