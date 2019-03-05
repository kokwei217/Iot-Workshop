#include <ESP8266WiFi.h>

const char* ssid     = "sarahteh12";
const char* password = "0126890907";
const char* host = "192.168.0.166";
const int port = 80;
int button = 5;
int previous = HIGH;
int current;

void setup() {
  Serial.begin(9600);
  pinMode(button, INPUT_PULLUP);
  
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) delay(100);
  
  Serial.println("ready");
}

void loop() {
  current = digitalRead(button);
  WiFiClient client;
  if (!client.connect (host, port)) Serial.println("Connection failed");
  if (current == LOW && previous == HIGH) {
    client.println('1');
    Serial.println("sucess");
  }

  previous = current;

}
