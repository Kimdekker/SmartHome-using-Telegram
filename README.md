# Manual to making a smarthome system yourself

First things first, what do you need for this manual (sensors you can choose yourself, I'm using a ledstrip for explanation):
- Arduino IDE (or another IDE)
- Board: ESP32 or ESP8266 (I'm using an ESP32, so you might need to adjust the feedback a little if using an ESP8266)
- Ledstrip
- Wiring
- Cable from your PC import to your board
- WiFi or your phone's hotspot
- Telegram (the app)

## what we are going to make during this manual
We will make a little smarthome system where we can control a ledstrip using telegram (by chatting with your own chatbot).
No worries, we will go step by step, and it's not all that hard ;)

So the steps we will folllow:
1. [Telegram: Getting your chatbot in the app](#telegram)
2. [Arduino IDE: Setting up code + libraries and linking the API code](#arduino)
3. [Tinkering around with the code: customize your prompts and commando's](#tinkering)
4. [Making different lightmodes for your smarthome](#lightmodes)

