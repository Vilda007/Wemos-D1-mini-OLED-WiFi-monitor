long lastJob1s = 0, lastJob30s = 0, lastJob1min = 0;

// připojení potřebných knihoven
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "ESP8266WiFi.h"

// nastavení OLED
#define OLED_RESET 0  // GPIO0
// inicializace OLED
Adafruit_SSD1306 display(OLED_RESET);

//SETUP-SETUP-SETUP-SETUP-SETUP-SETUP-SETUP-SETUP-SETUP-SETUP-SETUP-SETUP-SETUP-SETUP-SETUP-SETUP-SETUP-SETUP-SETUP-
void setup() {
  // komunikace po sériové lince rychlostí 9600 baud
  Serial.begin(9600);

  // Set WiFi to station mode and disconnect from an AP if it was previously connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  Serial.println("Setup done");

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 64x48)
  // Show image buffer on the display hardware.
  // Since the buffer is intialized with an Adafruit splashscreen
  // internally, this will display the splashscreen.
  display.display();
  delay(2000);
  // Clear the buffer.
  SmazOLED();
}

//LOOP-LOOP-LOOP-LOOP-LOOP-LOOP-LOOP-LOOP-LOOP-LOOP-LOOP-LOOP-LOOP-LOOP-LOOP-LOOP-LOOP-LOOP-LOOP-LOOP-LOOP-LOOP-LOOP-
void loop() {



  //LOOP-BLOCK-1s-LOOP-BLOCK-1s-LOOP-BLOCK-1s-LOOP-BLOCK-1s-LOOP-BLOCK-1s-LOOP-BLOCK-1s-LOOP-BLOCK-1s-LOOP-BLOCK-1s-LOOP-BLOCK-1s-LOOP-BLOCK-1s-LOOP-BLOCK-1s-LOOP-BLOCK-1s
  if (millis() > (1000 + lastJob1s))
  {
    // kód vykonaný každou 1 vteřinu (1000 ms)


    lastJob1s = millis();
  }

  //LOOP-BLOCK-30s-LOOP-BLOCK-30s-LOOP-BLOCK-30s-LOOP-BLOCK-30s-LOOP-BLOCK-30s-LOOP-BLOCK-30s-LOOP-BLOCK-30s-LOOP-BLOCK-30s-LOOP-BLOCK-30s-LOOP-BLOCK-30s-LOOP-BLOCK-30s-
  if (millis() > (30000 + lastJob30s))
  {
    // kód vykonaný každých 30 vteřin (30000 ms)
    // WiFi.scanNetworks will return the number of networks found
    Serial.println("scan start");
    SmazOLED();
    display.println("scan start");
    display.display();
    int n = WiFi.scanNetworks();
    Serial.println("scan done");
    display.println("scan done");
    display.display();
    if (n == 0) {
      Serial.println("No WiFi found");
      display.setTextSize(2);
      display.println("No");
      display.setTextSize(1);
      display.println("WiFi found");
      display.display();
    } else {
      Serial.print(n);
      Serial.println(" WiFi found");
      display.setTextSize(2);
      display.println(n);
      display.setTextSize(1);
      display.println("WiFi found");
      display.display();
      for (int i = 0; i < n; ++i) {
        delay(4500);
        SmazOLED();
        // Print SSID and RSSI for each network found
        display.print("WiFi #");
        Serial.print(i + 1);
        display.print(i + 1);
        display.print("/");
        display.println(n);
        Serial.print(": ");
        Serial.print(WiFi.SSID(i));
        display.setTextColor(RED);
        display.println(WiFi.SSID(i));
        display.setTextColor(WHITE);
        Serial.print(" (");
        Serial.print(WiFi.RSSI(i));
        display.print("sig:");
        display.print(WiFi.RSSI(i));
        display.println(" dB");
        Serial.print(")");
        Serial.println((WiFi.encryptionType(i) == ENC_TYPE_NONE) ? " " : "*");
        display.println((WiFi.encryptionType(i) == ENC_TYPE_NONE) ? " " : "*");
        display.display();
      }
    }
    Serial.println("");

    lastJob30s = millis();
  }

  //LOOP-BLOCK-1min-LOOP-BLOCK-1min-LOOP-BLOCK-1min-LOOP-BLOCK-1min-LOOP-BLOCK-1min-LOOP-BLOCK-1min-LOOP-BLOCK-1min-LOOP-BLOCK-1min-LOOP-BLOCK-1min-LOOP-BLOCK-1min
  if (millis() > (60000 + lastJob1min))
  {
    // kód vykonaný každou 1 minutu (60000 ms)


    lastJob1min = millis();
  }

  //LOOP-BLOCK-LOOP-BLOCK-LOOP-BLOCK-LOOP-BLOCK-LOOP-BLOCK-LOOP-BLOCK-LOOP-BLOCK-LOOP-BLOCK-LOOP-BLOCK-LOOP-BLOCK-LOOP-BLOCK-LOOP-BLOCK-LOOP-BLOCK-LOOP-BLOCK-LOOP-BLOCK-
}
//FUNCTIONS - FUNCTIONS - FUNCTIONS - FUNCTIONS - FUNCTIONS - FUNCTIONS - FUNCTIONS - FUNCTIONS - FUNCTIONS - FUNCTIONS - FUNCTIONS - FUNCTIONS - FUNCTIONS -
void SmazOLED() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 1);
}
