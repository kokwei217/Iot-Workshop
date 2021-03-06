#include <ESP8266WiFi.h>

const char* ssid     = "kokwei";
const char* password = "kokwei97";
const char* host = "192.168.43.57";
const int port = 80;
int button = 5;
int previous = HIGH;
int current;
unsigned long int pressed_time = 0;
int state = LOW;

void setup() {
  Serial.begin(115200);
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
    state = !state;
    if(state == HIGH)
      client.println("/LED=ON");
    else if (state == LOW)
          client.println("/LED=OFF");

   
    
  }

  

  previous = current;

}
