"""Fetch a file from the web and print to Serial/REPL"""

import requests
import network

wlan = network.WLAN(network.STA_IF)
wifi_is_on = wlan.active()


def main():
    if not wifi_is_on:
        print("no wifi!")
        return
    print("we have wifi :]")

    response = requests.get("http://server.alifeee.net/static/test.txt")
    response_code = response.status_code
    content = response.content

    print(f"Response: {response}")
    print(f"Request: {response_code}")
    print(f"Content: {content}")


main()
