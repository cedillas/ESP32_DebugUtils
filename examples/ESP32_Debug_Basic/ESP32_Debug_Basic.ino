#include <WiFi.h>
#include "ESP32_DebugUtils.h"

const char* ssid       = "UniFi";
const char* password   = "I81b4u8!";

const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 0;
const int   daylightOffset_sec = 0;

void setup() {
  Serial.begin(115200);
  Debug.timestampOn();

  //connect to WiFi
  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
  }
  Serial.println(" CONNECTED");

  //init and get the time
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
}

int i = 0;

void loop() {
  Debug.print(DBG_INFO, "i - %d", i);
  i++;
  delay(1000);

  //struct tm timeinfo;
  //asctime(&timeinfo);
  //Serial.println(&timeinfo);


}
