"""blink onboard LED every second
"""

import time
from machine import Pin

p = Pin(2, Pin.OUT)

while True:
    print("on")
    p.off()
    time.sleep(1)
    print("off")
    p.on()
    time.sleep(1)
