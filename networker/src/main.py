"""A web server which sends query parameters to UART1"""

from machine import UART, Pin
from micropyserver import MicroPyServer
import utils

led = Pin(2, Pin.OUT)
led.off()

link = UART(1)
link.init(9600, bits=8, parity=None, stop=1)


def send_to_sign(message):
    print("sending message to UART (pin 2/D4):")
    print(message)
    link.write(message)
    link.write("\0")


send_to_sign("initialising...")

MAIN_PAGE = """
<!DOCTYPE html>
<html>
<head>
    <title>ESP bus sign!</title>
    <meta charset="utf-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1" />
</head>
<body>
    <h1>ESP Bus Sign</h1>
    <form action="/send" method="POST">
        <label for="signtext">Sign Text</label>
        <input type="text" name="signtext" id="signtext">
        <input type="submit" value="Send to sign!">
    </form>
</body>
</html>
"""

BACK_PAGE = """
<!DOCTYPE html>
<html>
<head>
    <title>ESP bus sign!</title>
    <meta charset="utf-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1" />
    <meta http-equiv="refresh" content="3;url=/" />
</head>
<body>
    <h1>ESP Bus Sign</h1>
    <h2>Submission sent!</h2>
    <p>You sent:</p>
    <code><pre>%s</pre></code>
    <p>
        <a href="/">back to main page</a> (you will be redirected in 3 seconds)
    </p>
</body>
</html>
"""


def mainpage(request):
    """request handler for main page"""
    print("request for main page!")
    print(request)
    utils.send_response(server, MAIN_PAGE)


def send(request):
    """request handler for action page"""
    post_params = utils.get_request_post_params(request)
    signtext = post_params.get("signtext", "N/A")
    send_to_sign(signtext)
    utils.send_response(server, BACK_PAGE % signtext)


server = MicroPyServer()
server.add_route("/", mainpage)
server.add_route("/send", send, method="POST")

server.start()

led.on()
