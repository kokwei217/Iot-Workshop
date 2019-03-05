
#include <ESP8266WiFi.h>

const char* ssid = "sarahteh12";
const char* password = "0126890907";

WiFiServer server(80);

void setup() {
  pinMode(16, OUTPUT);

  Serial.begin(115200);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) delay(100);

  server.begin();
  Serial.println("Connected");
  Serial.println(WiFi.localIP());
}

void loop() {

  WiFiClient client = server.available();

  if (client) {

    while (client.connected()) {
      
      if (client.available()) {
        
        char c = client.read();
        Serial.print( c);
        client.flush();

        if (c == '1')  digitalWrite(16, HIGH);
      }
    }
  }
}

