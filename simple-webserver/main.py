"""
   This code is licensed under Apache Version 2.0, January 2004

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
"""
import machine  as ma
import neopixel as neo
import time     as ti
import _thread
import config

import os
print(', '.join(os.uname()))

import platform
print(platform.platform())

import esp
print("Flash size {:,} bytes".format(esp.flash_size()))
import gc
print("Memory free {:,} bytes.".format(gc.mem_free()))

name = os.uname()[-1].split(' ')[-1]
if name is "ESP32S3":
    pinnum = 48
elif name is 'ESP32':
    # Setup specifically for Adafruit Huzzah ESP32 V2.
    # Pin 0 is the data pin to the NeoPixel,
    # Pin 2 is the power pin that must be set as an
    # an output and on, or high.
    #
    pinnum = 0
    #
    # Turn on the power for the NeoPixel.
    #
    pwr = ma.Pin(2, ma.Pin.OUT)
    pwr.value(1)
else:
    pinnum = 8

np = neo.NeoPixel(ma.Pin(pinnum), 1)

neopixel_colors = [
    (64, 0, 0),  # red
    (0, 64, 0),  # green
    (0, 0, 64),  # blue
    (64, 32, 0), # orange
    (0, 64, 64), # cyan
    (0, 0, 0)    # black
    ]

def cycle_colors():
    for color in neopixel_colors:
        np[0] = color
        np.write()
        ti.sleep_ms(400)
    np[0] = neopixel_colors[-1]
    np.write()

def do_action(action_to_do):
    if action_to_do == config.LED_RED or action_to_do == config.LED_GREEN or action_to_do == config.LED_BLUE or action_to_do == config.LED_OFF:
        np[0] = neopixel_colors[action_to_do]
        np.write()
    elif action_to_do == config.LED_CYCLE:
        cycle_colors();

#_thread.start_new_thread(cycle_colors, ())

from SimpleHttp import SimpleHttpServer
shs = SimpleHttpServer(do_action)
shs.run()
