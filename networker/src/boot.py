# This file is executed on every boot (including wake-boot from deepsleep)
# import esp
# esp.osdebug(None)
import os, machine
import network
import time
from machine import Pin
from secrets import WIFI_SSID, WIFI_PASS

# os.dupterm(None, 1) # disable REPL on UART(0)
import gc

# import webrepl
# webrepl.start()
gc.collect()

led = Pin(2, Pin.OUT)
led.off()

# Replace with your network credentials


# Set up the Wi - Fi interface
wlan = network.WLAN(network.STA_IF)
wlan.active(True)

# Connect to the Wi - Fi network
wlan.connect(WIFI_SSID, WIFI_PASS)

# Wait for the connection
max_wait = 10
while max_wait > 0:
    if wlan.isconnected():
        break
    max_wait -= 1
    print("Waiting for connection...")
    time.sleep(1)

# Check if the connection was successful
if wlan.isconnected():
    print("Connected to Wi - Fi")
    print("Network config:", wlan.ifconfig())
    led.on()
else:
    print("Connection failed")
