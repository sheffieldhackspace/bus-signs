"""continually send messages over Serial, for testing"""

from machine import UART, Pin
import time

led = Pin(2, Pin.OUT)
led.off()

link = UART(1)
link.init(9600, bits=8, parity=None, stop=1)


def send_to_sign(message):
    print("sending message to UART (pin 2/D4):")
    print(message)
    link.write(message)
    link.write("\0")


while True:
    time.sleep_ms(250)
    led.off()
    send_to_sign("i am a dwarf")

    time.sleep_ms(250)
    led.on()

    time.sleep_ms(250)
    led.off()
    send_to_sign("and i am digging a hole")

    time.sleep_ms(250)
    led.on()
