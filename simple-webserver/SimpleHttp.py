"""
   This code is licensed under Apache Apache Version 2.0, January 2004

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.

This is the Simple HTTP Server.
It has HTML/CSS text intermixed with Python code.
It provides very limited functionality.
"""
import binascii
import machine
import os
import platform
import usocket
import _thread
import time
import gc
import network
from network import WLAN
from machine import RTC

import config

class SimpleHttpServer:
    SSID = None
    do_action = None

    def __init__(self, do_action):
        self.do_action = do_action
        self.name = os.uname()[-1].split(' ')[-1]
        self.SSID = self.name + '_' + binascii.hexlify(machine.unique_id()).decode('ascii').upper()[-4:]
        gc.enable()

    def client_thread(self, clientsocket):
        received = clientsocket.recv(4096)

        # If received has 0 bytes then the other end closed the connection.
        #
        if len(received) == 0:
            clientsocket.close()
            return
        else:
            # Parse the recieved data and perform any given actions.
            #
            received_str = str(received)
            #
            # Uncomment the following for raw debugging purposes. Lots of output.
            #
            #print("Received: {}".format(received_str))

            # Send out the common webpage header for all pages.
            #
            clientsocket.send("HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nConnection:close \r\n\r\n")
            clientsocket.send("<HTML><HEAD><TITLE>{}</TITLE>".format(self.SSID))
            clientsocket.send(
                "<style>"
                "body {font-family: sans-serif;margin: 20px;}"
                "button {"
                "font-size: 300%;"
                "font-weight: bold;"
                "display: inline-block;"
                "margin: 5px;"
                "padding: 20px 60px;"
                "width: 99%;"
                "height: 150px;"
                "justify-content: center;"
                "align-items: center;"
                "text-decoration: none;"
                "color: #ffffff;"
                "background-color: #556B2F;"
                "border: none;"
                "border-radius: 0px;"
                "outline: none;}"
                "hr {border: 0;height: 2px;"
                "background-image: linear-gradient(to right, rgba(0, 0, 0, 0), rgba(0, 0, 0, 0.75), rgba(0, 0, 0, 0));}"
                "h1 {font-size: 300%;color: #D35F8D;text-align: center;}"
                "h2 {font-size: 200%;color: #5FA3D3;padding-left: 15px;}"
                "</style>"
                "</HEAD><BODY>")
            clientsocket.send("<h1>{}</h1>".format(self.SSID))

            # Start parsing the request, performing the various actions.
            # If there is no defined actions for the request, tell the user.
            #
            if "GET / " in received_str:
                clientsocket.send(
                    "<hr/>"
                    "<a href='/func1'><button style='background-color: #DC143C'>LED Red</button></a>"
                    "<a href='/func2'><button style='background-color: #228B22'>LED Green</button></a>"
                    "<a href='/func3'><button style='background-color: #4169E1'>LED Blue</button></a>"
                    "<a href='/func4'><button style='background-color: #808080'>LED Cycle</button></a>"
                    "<a href='/func5'><button style='background-color: #404040'>LED OFF</button></a>"
                    )
            elif "GET /func1 " in received_str:
                clientsocket.send("<h1>LED Red</h1>")
                self.do_action(config.LED_RED)
            elif "GET /func2 " in received_str:
                clientsocket.send("<h1>LED Green</h1>")
                self.do_action(config.LED_GREEN)
            elif "GET /func3 " in received_str:
                clientsocket.send("<h1>LED Blue</h1>")
                self.do_action(config.LED_BLUE)
            elif "GET /func4 " in received_str:
                clientsocket.send("<h1>LED Cycle</h1>")
                self.do_action(config.LED_CYCLE)
            elif "GET /func5 " in received_str:
                clientsocket.send("<h1>LED OFF</h1>")
                self.do_action(config.LED_OFF)
            else:
                clientsocket.send("<h1>Undefined Action</h1>" + received_str)

            clientsocket.send("<a href='/'><button style='background-color: #007C80'><em>Home</em></button></a>")
            clientsocket.send("<HR/>")
            clientsocket.send("<h2>Header Size: {:,} bytes</h2>".format(len(received)))
            clientsocket.send("<h2>Memory Free: {:,} bytes</h2>".format(gc.mem_free()))
            clientsocket.send("<h2>{}</h2>".format(', '.join(os.uname())))
            clientsocket.send("<h2>{}</h2>".format(platform.platform()))
            clientsocket.send("</BODY></HTML>")
            gc.collect()

            # Close the socket and terminate the thread
            clientsocket.close()

        time.sleep_ms(500)

    def run(self):
        # create as an access point
        #
        wlan = WLAN(network.AP_IF)
        wlan.active(True)

        # configure as an access point
        #
        print(self.SSID)
        wlan.config(essid=self.SSID)
        wlan.ifconfig(('192.168.1.2','255.255.255.0','192.168.1.1','8.8.8.8'))

        # Set up server socket to read client responses from web pages
        #
        serversocket = usocket.socket(usocket.AF_INET, usocket.SOCK_STREAM)
        serversocket.setsockopt(usocket.SOL_SOCKET, usocket.SO_REUSEADDR, 1)
        serversocket.bind(("192.168.1.2", 80))

        # Listen argument defines the maximum connections at the same time.
        #
        serversocket.listen(1)

        while True:
            (clientsocket, address) = serversocket.accept()
            # Start a new thread to handle the client
            #
            _thread.start_new_thread(self.client_thread, (clientsocket, ))
        serversocket.close()
