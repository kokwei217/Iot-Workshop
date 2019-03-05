#include <ESP8266WiFi.h>

const char* ssid = "sarahteh12";
const char* password = "0126890907";
int led = 16;
int value = LOW;

WiFiServer server(80); //default port of http 


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);

  Serial.println();
  Serial.println("Connecting to ...");
  Serial.println(ssid);

  WiFi.begin(ssid , password);

  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }

  server.begin();

  Serial.print("Use this URL to connect:");
  Serial.print("http://");
  Serial.print(WiFi.localIP());

}

void loop() {
  WiFiClient client = server.available(); // Listen for incoming clients

  if (!client) {
    return;
  }

  Serial.println("new client");
  while (!client.available()) ;

  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();

  if (request.indexOf("/LED=ON") != -1) {
    value = HIGH;
    digitalWrite(led, HIGH);
  }

  else if (request.indexOf("/LED=OFF") != -1) {
    value = LOW;
    digitalWrite(led, LOW);
  }

  client.println("HTTP/1.1 200 OK"); 
  client.println("Content-Type : text/html");
  client.println();
  client.println("<!DOCTYPE HTML>"); // specify version of html
  client.println("<html>");
  client.println("<h1> My First website </h1>");

  Serial.println("Client disconnected");

}


