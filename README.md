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

After you did this, upload your code your code to your board by clicking the arrow on the top left. 
If the code is uploaded, head over to the serial monitor (in the top right corner > icon), and you should see that the board is connecting to your phone. 

If somethings wrong in this phase, it's probably because you didn't fill in the key, or your Wifi credentials right.

<br />

When thats all good, you can go to your own bot (the one that you named yourself) and send it a message:
![yourbot](https://github.com/user-attachments/assets/9d738ac6-f647-40f2-882d-9ac4e07d645b)

You'll see that it bounces back your own message. In the code that happens in this function:
```
  if (millis() - bot_lasttime > BOT_MTBS)
  {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

    while (numNewMessages)
    {
      Serial.println("got response");
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }

    bot_lasttime = millis();
  }
```

What happens here is a few things:
1. You get a message in the serial monitor "got response"
2. It sends the message that you send back to the chat and bounces back the last message it received

You could change that message to something else as well. I chose to send an automatic text back saying something like "Hello can I help you with anything else?"
In the next steps this may come in handy!

```
      bot.sendMessage(chat_id, "Kan ik je verder nog helpen? Let me know!", "");
```

Alright! So, now we're set, we can send messages, and receive messages as well. 
In the next step we will apply rudimentary intelligence (sounds freaky, but no worries)


## Tinkering
### customize your prompts and commando's

Because we are building a smarthome system where we can adjust the ledstrip to a certain mood using Telegram, we will need to send our bot a specific message to trigger an output > "Lights on" = the lights of the ledstrip will turn on.

We can do this using if else statements. 
So lets head over to the right function > 'handleNewMessages' and let the led go on and of on command. 

```
void handleNewMessages(int numNewMessages)
{
  for (int i = 0; i < numNewMessages; i++)
  {

    // Add these 2 in to define chati_id and text
    String chat_id = bot.messages[i].chat_id; 
    String text = bot.messages[i].text;

    // Let the Serial monitor print the text
    Serial.println(bot.messages[i].text);

    // If the text is "Light on"
    if (text == "Light on") {
      digitalWrite(LED_BUILTIN, HIGH);  // Turn on LED
      bot.sendMessage(chat_id, "Light on");
    }

    // If the text is "Light out"
    else if (text == "Light out") {
      digitalWrite(LED_BUILTIN, LOW);  // Turn on LED
      bot.sendMessage(chat_id, "Light out");
    }

    // If the text is "if anything else is sent"
    else {
// You could also send a message with which commands exist out there. How? see the other if statements...
      bot.sendMessage(chat_id, text, "");
    }
  }
}
```

And in void setup add this to initialise the pin:
```
  pinMode(LED_BUILTIN, OUTPUT);

```

Now, when you upload this to your board, you should see the LED in your board go on and off using your chatbot in Telegram.
![commands](https://github.com/user-attachments/assets/8b4f9e2c-023a-4f17-b80d-7702741bbe63)

This if else function is the main thing inside the code. In these statements we can do anything. Add your code of whatever sensor you want and you can make it work. 

In the next, and last step, we will work with a ledstrip to make the ledstrip go on and off, but also make more modes on command.


## Lightmodes
### making different lightmodes for your smarthome

So what we are going to do is make a few funky lightmodes next to the normal basic lights. 

So first, we want to add the ledstrip to the file and to the board. 

Let's first hook up your ledstrip to the board. You have 3 cables to hook up:
- GND -> GND
- Din -> D5 (or another pin, but remeber to change the pin in the code later on)
- 5V -> 5V or VIN

Now, I think it's best to first check if you hooked up the ledstrip right, before adding the code to our file. 

First we need the Adafruit Neopixel library:
![adafruit](https://github.com/user-attachments/assets/fca9a4f2-2f19-48e8-9c25-b28b21d60ced)

Then, go to: File > examples > Adafruit Neopixel > simple

then define the right pins and leds:
```
// Which pin on the Arduino is connected to the NeoPixels?
#define PIN        6 // your Din pin

#define NUMPIXELS 12 // The number of leds on your ledstrip
```

Now upload this to your board and see if it works. If the led is not working, you probably didn't put the pins on the right places on the board (so please go check), or you didn't define them right in your code. 

If it works, you're good to go and go to our file for the bot.
In the file, we have to add a few new rules. First the define:
```
#include <Adafruit_NeoPixel.h>

#define PIN 5 // Your right pin
#define NUM_LEDS 12 //your amount of leds

Adafruit_NeoPixel strip(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800); 
```

Then, in the void setup():
```
  strip.begin(); // Initialise the LED-strip
  strip.show();  // The ledstrip will be off on default using this
```

Okay so now, we can add the ledstrip in the if else statements

In theory you could make al those lightmodes work inside the if else statements, like this:
```
    if (text == "Light on") {
      strip.setPixelColor(i, strip.Color(255, 255, 102));             bot.sendMessage(chat_id, "Light on");
    }
```

Here the light will turn to a cold yellow color. You could do that with all the lightmodes you want, but the moment you want to let something more happen to the lightstrip, perhaps a disco, then the code becomes a bit cluttery. In that case, I would suggest passing a function down to the if else statement. 

On the bottom of the file, you can make your own function, like this disco one:
```
// Functie om een disco-effect te creëren
void discoEffect(int delayTime) {
  // Herhaal het disco-effect
  for (int repeat = 0; repeat < 50; repeat++) { // Herhaal 50 keer (als ik 500 doe, dan moet ik lang wachten tot ik een ander commando kan geven.)
    for (int i = 0; i < NUM_LEDS; i++) {
      strip.setPixelColor(i, randomColor());  // Zet elke LED naar een willekeurige kleur
    }
    strip.show();  // Update de LED-strip met de nieuwe kleuren
    delay(delayTime);  // Wacht een bepaalde tijd voor de volgende update

    shiftPixels();  // Laat de kleuren verschuiven
    strip.show();   // Update de LED's na het verschuiven
  }
}

// Functie om een willekeurige kleur te genereren
uint32_t randomColor() {
  return strip.Color(random(0, 256), random(0, 256), random(0, 256)); // Random RGB waarden
}

// Functie om alle LED's 1 positie op te schuiven
void shiftPixels() {
  uint32_t lastPixel = strip.getPixelColor(NUM_LEDS - 1); // Sla de kleur van de laatste LED op
  for (int i = NUM_LEDS - 1; i > 0; i--) {
    strip.setPixelColor(i, strip.getPixelColor(i - 1)); // Schuif elke kleur naar de volgende positie
  }
  strip.setPixelColor(0, lastPixel); // Zet de laatste kleur naar de eerste LED
}
```

and then you pass this function to the if else:
```
    else if (text == "Audio, video") {
      discoEffect(50); // here I pass on the function that I just made, and gave it a delay as a parametre
      bot.sendMessage(chat_id, "...Disco");
    }
```

Like this, you can keep your if else list clean, and have another place to change the codes. 

I made some more fun modes like a campfire and a mode for when the boy is at home, but feel free to experiment with your own modes.

![morecommands](https://github.com/user-attachments/assets/73f2b592-1013-45b6-860f-fbef8bd34191)


The manual is now done, and you can see my finished codefile in the repo. 

Have fun making!


## Contributors
- Kim Dekker [Github](https://github.com/Kimdekker/)


## Licentie

This project is provided under the [MIT](/LICENSE) License
