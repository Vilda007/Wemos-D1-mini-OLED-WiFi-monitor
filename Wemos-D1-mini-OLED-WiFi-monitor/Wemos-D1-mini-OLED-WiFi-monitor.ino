long lastJob1s = 0, lastJob30s = 0, lastJob1min = 0;
byte enc = 0;

// připojení potřebných knihoven
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

ESP8266WiFiMulti wifiMulti;

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
  delay(100);

  wifiMulti.addAP("AP1", "PWD1");
  wifiMulti.addAP("AP2", "PWD2");
  wifiMulti.addAP("AP3", "PWD3");

  Serial.println("Setup done");

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 64x48)
  // Show image buffer on the display hardware.
  // Since the buffer is intialized with an Adafruit splashscreen
  // internally, this will display the splashscreen.
  display.display();
  delay(2000);
  // Clear the buffer.
  SmazOLED();
  ConnectWiFi();
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


    lastJob30s = millis();
  }

  //LOOP-BLOCK-1min-LOOP-BLOCK-1min-LOOP-BLOCK-1min-LOOP-BLOCK-1min-LOOP-BLOCK-1min-LOOP-BLOCK-1min-LOOP-BLOCK-1min-LOOP-BLOCK-1min-LOOP-BLOCK-1min-LOOP-BLOCK-1min
  if (millis() > (60000 + lastJob1min))
  {
    // kód vykonaný každou 1 minutu (60000 ms)
    // WiFi.scanNetworks will return the number of networks found
    WiFi.disconnect();
    delay(300);
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
      display.print("  ");
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
        display.drawLine(0, 10, 63, 10, WHITE);
        display.setCursor(0, 12);
        display.println(WiFi.SSID(i));
        Serial.print(" (");
        Serial.print(WiFi.RSSI(i));
        display.setCursor(0, 29);
        display.print("sig:");
        display.print(WiFi.RSSI(i));
        display.println(" dB");
        Serial.print(" dB) ");
        /*
          TKIP (WPA) = 2
          WEP = 5
          CCMP (WPA) = 4
          NONE = 7
          AUTO = 8
        */
        enc = WiFi.encryptionType(i);
        switch (enc) {
          case 2:
            Serial.print("Encoding: ");
            Serial.print(enc);
            Serial.println(" - TKIP (WPA)");
            display.println("TKIP(WPA)");
            break;
          case 5:
            Serial.print("Encoding: ");
            Serial.print(enc);
            Serial.println(" - WEP");
            display.println("WEP");
            break;
          case 4:
            Serial.print("Encoding: ");
            Serial.print(enc);
            Serial.println(" - CCMP(WPA)");
            display.println("CCMP(WPA)");
            break;
          case 7:
            Serial.print("Encoding: ");
            Serial.print(enc);
            Serial.println(" - NONE");
            display.println("NONE");
            break;
          case 8:
            Serial.print("Encoding: ");
            Serial.print(enc);
            Serial.println(" - AUTO");
            display.println("AUTO");
            break;
          default:
            Serial.print("Encoding: ");
            Serial.print(enc);
            Serial.println(" - UNKNOWN");
            display.println("UNKNOWN");
            break;
        }
        /*
          Serial.println((WiFi.encryptionType(i) == ENC_TYPE_NONE) ? " " : "*");
          display.println((WiFi.encryptionType(i) == ENC_TYPE_NONE) ? " " : "*");
        */
        display.drawLine(0, 47, (100 + WiFi.RSSI(i)) * 0.63, 47, WHITE);
        display.display();
      }
    }
    Serial.println("");
    delay(4500);
    ConnectWiFi();

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

void ConnectWiFi() {
  SmazOLED();
  Serial.print("Connecting Wifi");
  display.print("Connecting");
  display.display();
  /*
  while (wifiMulti.run() != WL_CONNECTED) {
    Serial.print(" .");
    display.print(".");
    display.display();
    delay(1000);
  }
  */
  if (wifiMulti.run() == WL_CONNECTED) {
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    SmazOLED();
    display.println("WiFi ready");
    display.println("IP address:");
    display.println(WiFi.localIP());
    display.display();
  }
}
