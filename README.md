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
2. [Arduino_IDE: Setting up code + libraries and linking the API code](#arduino_ide)
3. [Tinkering: customize your prompts and commando's](#tinkering)
4. [Making different lightmodes for your smarthome](#lightmodes)

<br /><br />

## Telegram 
### Getting your chatbot in the app
So first things first, you should download Telegram. Just the regular app./
Then on the app, start a new chat (the icon in the right-top of the screen, and search for: Botfather
![botfather](https://github.com/user-attachments/assets/a0627eb2-d9cd-4422-a484-b9789df255ba)

<br />

After that go to the botFather chat and type in: /start

![start](https://github.com/user-attachments/assets/4fd9ad89-587e-4d57-bc1b-1ff877eed030)

You'll see all the commands you could use, but we won't use these much in this case, but feel free to tinker around with these if you'd like :)

Follow the steps that you read in the chat > give your bot a name:
![newbot](https://github.com/user-attachments/assets/6b328cea-c1a3-4bb7-9162-6d3a88249ed0)

And after, give your bot a username. It must be unique, and you won't see it in the chat, so no worries on choosing a complex name here.
Tip: your bot name bust end with Bot (with the capital_ or _bot (with the underscore).

After you've chosen a name, you get a message with a key. You'll need this key in the next step.

![choosename](https://github.com/user-attachments/assets/4f462443-9e72-4fd9-8d2f-02195b4d72a0)

Alright, so now your bot is ready, so leave this chat, and you'll see your own bot with your name.
Thats good. In telegram you're set now!


## Arduino_IDE 
### Setting up code + libraries and linking the API code
Let's head over to Arduino IDE, and install some things you need.
If you don't have your esp32 board downloaded yet, download so:
![board](https://github.com/user-attachments/assets/40bfbd4f-678e-412b-b60d-3bda37ff470a)

And download the "UniversalTelegramBot" library. Newest version is good.
![telegramlibrary](https://github.com/user-attachments/assets/eea0b424-5ab1-43c0-9b2a-d6f1abdbcca2)

Now, we can import our basic code (we don't even have to write that ourself!)
Go to: File > examples > UniversalTelegramBot > ESP32 > EchoBot
![import sample](https://github.com/user-attachments/assets/a0ea8169-1844-4f90-a92d-0bb4f18bc97e)

And there, you have your first bit of code almost ready to go. 
From here you have to do 2 things.
1. Add the key you got in the botFather chat and fill that in the placceholder:
```
#define BOT_TOKEN "###########:################################"
```
2. Add your Wifi-network name and password:
```
#define WIFI_SSID "Your WiFi name"
#define WIFI_PASSWORD "Your WiFi password"
```

## Tinkering
### customize your prompts and commando's

## Tinkering
### customize your prompts and commando's
