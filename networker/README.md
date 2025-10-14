# Networker

(this section is not not used)

install MicroPython firmware

```bash
# download ESP8266_GENERIC-20250415-v1.25.0.bin
#   …from https://micropython.org/download/ESP8266_GENERIC/
pip install esptool
esptool --port /dev/ttyUSB0 erase-flash
esptool --port /dev/ttyUSB0 --baud 460800 write-flash --flash-size=detect 0 ESP8266_GENERIC-20250415-v1.25.0.bin
```

install `rshell` to talk to MicroPython device

```bash
py -m venv env
source env/bin/activate
pip install rshell
PORT=/dev/ttyUSB0; rshell --buffer-size 512 --quiet -p $PORT
# files on device are now at /pyboard
# use `repl` to enter repl (CTRL+X to quit)
```

use `rshell` to upload the `boot.py` file to the board

```bash
PORT=/dev/ttyUSB0; rshell --buffer-size 512 --quiet -p $PORT
> # libraries and boot.py
> cp src/secrets.py /pyboard/
> cp src/boot.py /pyboard/
> cp src/micropyserver.py /pyboard/
> # for different main.py files
> cp src/main-blink.py /pyboard/main.py
> cp src/main-webhost.py /pyboard/main.py
```

use `rshell` to upload a project environment to the board

```bash
PORT=/dev/ttyUSB0; rshell --buffer-size 512 --quiet -p $PORT
> rsync ./src/blink/ /pyboard
```

## Breadboard

Using an ESP, you can get Wi-Fi, but it outputs only 3.3V logic, which you can use a level converter to shift to 5V logic. You might have to slow down the polling rate to make sure it is correctly sent.

For the 1-8 pin meanings of the ribbon cables, see: <https://github.com/ConnectedHumber/Bus-Terminal-Signs?tab=readme-ov-file#pin-designation>

![picture of breadboard layout](images/breadboard.png)
