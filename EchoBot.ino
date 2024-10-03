/*******************************************************************
    A telegram bot for your ESP32 that responds
    with whatever message you send it.

    Parts:
    ESP32 D1 Mini stlye Dev board* - http://s.click.aliexpress.com/e/C6ds4my
    (or any ESP32 board)

      = Affilate

    If you find what I do useful and would like to support me,
    please consider becoming a sponsor on Github
    https://github.com/sponsors/witnessmenow/


    Written by Brian Lough
    YouTube: https://www.youtube.com/brianlough
    Tindie: https://www.tindie.com/stores/brianlough/
    Twitter: https://twitter.com/witnessmenow
 *******************************************************************/

#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <Adafruit_NeoPixel.h>


// Wifi network station credentials
#define WIFI_SSID "iPhone van Kim (3)"
#define WIFI_PASSWORD "esp8266wifi"
// Telegram BOT Token (Get from Botfather)
#define BOT_TOKEN "8103918153:AAFQ-yCkAwPTSNpiogWCkxLnM17agxWuvFQ"

#define PIN 5 // Dit is GPIO 5 (D5)
#define NUM_LEDS 12

Adafruit_NeoPixel strip(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);

const unsigned long BOT_MTBS = 1000; // mean time between scan messages

WiFiClientSecure secured_client;
UniversalTelegramBot bot(BOT_TOKEN, secured_client);
unsigned long bot_lasttime; // last time messages' scan has been done

void handleNewMessages(int numNewMessages)
{
  for (int i = 0; i < numNewMessages; i++)
  {
    String chat_id = bot.messages[i].chat_id;
    String text = bot.messages[i].text;

    Serial.println(bot.messages[i].text);
    
    if (text == "Licht aan") {
      setLightOn();
      bot.sendMessage(chat_id, "Is goed g, fix ik ff voor je toch! BEMM je licht is aan");
    }

    else if (text == "Licht uit") {
      setLightout();
      bot.sendMessage(chat_id, "No worries homie, ik heb het licht voor je uitgedaan ;)");
    }

    else if (text == "Audio, video") {
      discoEffect(50);
      bot.sendMessage(chat_id, "...Disco");
    }

    else if (text == "Kampvuurtje") {
      setCampfire();
      bot.sendMessage(chat_id, "Oee got it, pak jij alvast de marshmellows");
    }

    else if (text == "De boy is er") {
      setBoy();
      bot.sendMessage(chat_id, "Gotcha! Time for some easy and chill ambience");
    }

    else {
      bot.sendMessage(chat_id, "Dit C0mmand0 bestaat niet gap. Kies uit: 'Licht aan', 'Licht uit', 'Audio, video', 'Kampvuurtje' of 'De boy is er'...");
    }
  }
}

void setup()
{
  Serial.begin(115200);
  Serial.println();

  // attempt to connect to Wifi network:
  Serial.print("Connecting to Wifi SSID ");
  Serial.print(WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  secured_client.setCACert(TELEGRAM_CERTIFICATE_ROOT); // Add root certificate for api.telegram.org
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.print("\nWiFi connected. IP address: ");
  Serial.println(WiFi.localIP());

  Serial.print("Retrieving time: ");
  configTime(0, 0, "pool.ntp.org"); // get UTC time via NTP
  time_t now = time(nullptr);
  while (now < 24 * 3600)
  {
    Serial.print(".");
    delay(100);
    now = time(nullptr);
  }
  Serial.println(now);

  strip.begin(); // Initialiseer de LED-strip
  strip.show();  // Zorg ervoor dat de LED's eerst uit staan
}

void loop()
{
  if (millis() - bot_lasttime > BOT_MTBS)
  {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

    while (numNewMessages)
    {
      Serial.println("got response");
      handleNewMessages(numNewMessages);

      String chat_id = bot.messages[0].chat_id;
      bot.sendMessage(chat_id, "Kan ik je verder nog helpen? Let me know!", "");


      numNewMessages = bot.getUpdates(bot.last_message_received + 1);

    }

    bot_lasttime = millis();
  }

}

void setLightOn() {
  for (int i = 0; i < NUM_LEDS; i++) {
    strip.setPixelColor(i, strip.Color(255, 255, 102)); // warm geel
  }
  strip.show(); // Update de LED's
}

void setLightout() {
  for (int i = 0; i < NUM_LEDS; i++) {
    strip.setPixelColor(i, strip.Color(0, 0, 0)); // RGB uit
  }
  strip.show(); // Update de LED's
}

void setCampfire() {
  // ik wilde een kampvuurtje, dus een orange licht dat een beetje flikkerd in een random patroon, maar werkt niet :(
  for (int i = 0; i < NUM_LEDS; i++) {
    // Kies een gedimde vuurrood/oranje kleur met flikker effect
    uint32_t color = strip.Color(255, random(40, 100), 0); // Random oranje voor flikkering
    strip.setPixelColor(i, color);
  }
  strip.show();
  delay(random(50, 150)); // Willekeurige delay voor flikkeren
}

void setBoy() {
  // Continu de kleuren laten veranderen
  // Ik wilde een gradient van paars naar roze en terug, maar dit werkt niet op deze ledstrip :(
  for (int j = 0; j < 255; j++) {
    for (int i = 0; i < NUM_LEDS; i++) {
      // Bepaal de interpolatie van de kleuren voor een gradient
      int r = (128 * (255 - j) + 255 * j) / 255;  // van paars naar roze
      int g = (0 * (255 - j) + 105 * j) / 255;    // van 0 naar 105
      int b = (128 * (255 - j) + 180 * j) / 255;  // van 128 naar 180

      strip.setPixelColor(i, strip.Color(r, g, b));
    }
    strip.show();
    delay(20); // Vaste delay waarde voor de gradient
  }

    // In reverse om terug te gaan van roze naar paars
  for (int j = 255; j >= 0; j--) {
    for (int i = 0; i < NUM_LEDS; i++) {
      // Bepaal de interpolatie van de kleuren voor een gradient
      int r = (128 * (255 - j) + 255 * j) / 255;  // van paars naar roze
      int g = (0 * (255 - j) + 105 * j) / 255;    // van 0 naar 105
      int b = (128 * (255 - j) + 180 * j) / 255;  // van 128 naar 180

      strip.setPixelColor(i, strip.Color(r, g, b));
    }
    strip.show();
    delay(20); // Vaste delay waarde voor de gradient
  }
}


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
