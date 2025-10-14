# Bus Signs

Based on code from <https://github.com/ConnectedHumber/Bus-Terminal-Signs>.

| | name | function |
| --- | --- | --- |
| ![picture of Arduino Uno R3](images/arduino_uno_r3.png) | Arduino Uno R3 | microcontroller with logic |
| ![picture of W5500 ethernet shield](images/w5500_ethernet_shield.png) | WizNet W5500 Ethernet Shield | provides networking to Arduino |
| ![picture of breadboard connections](images/sign_connections.png) | sign connection | connects Arduino to sign |

## Controller

see [controller/README.md](./controller/README.md)

```bash
# enter directory
cd controller
# upload tests to Arduino
pio run -e blink -t upload
pio run -e testblink -t upload
pio run -e scrolling -t upload
pio run -e test-ethernet-http-fetch -t upload
pio run -e test-ethernet-http-listen -t upload
# upload code to Arduino
pio run -e test-ethernet-sign -t upload
```
