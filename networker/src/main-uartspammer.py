"""continually send messages over Serial, for testing"""

import time
from machine import UART, Pin

led = Pin(2, Pin.OUT)
led.off()

link = UART(1)
link.init(9600, bits=8, parity=None, stop=1)


def send_to_sign(message):
    print("sending message to UART (pin 2/D4):")
    print(message)
    link.write(message)
    link.write("\0")


MESSAGE_FLAT = [int(28282828 / (i + j + 1)) % 2 for i in range(192) for j in range(18)]
MESSAGE_BYTELIST = [
    int("".join(map(str, MESSAGE_FLAT[i : i + 8])), 2)
    for i in range(0, len(MESSAGE_FLAT), 8)
]

while True:
    time.sleep_ms(1000)
    print("led on")
    led.off()
    send_to_sign(bytes(MESSAGE_BYTELIST))

    time.sleep_ms(1000)
    print("led off")
    led.on()
