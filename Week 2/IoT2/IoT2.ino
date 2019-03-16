#include <ESP8266WiFi.h>

const char* ssid = "kokwei";
const char* password = "kokwei97";
int red = 16;
int green = 5;
int blue = 4;
int value = LOW; 

int sequence [8][3] {
  {0, 0, 0},
  {0, 0, 1},
  {0, 1, 0},
  {0, 1, 1},
  {1, 0, 0},
  {1, 0, 1},
  {1, 1, 0},
  {1, 1, 1}
};

WiFiServer server(80); //default port of http

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);

  digitalWrite(red, HIGH);
  digitalWrite(green, HIGH);
  digitalWrite(blue, HIGH);


  Serial.println();
  Serial.println("Connecting to ...");
  Serial.println(ssid);

  WiFi.begin(ssid , password);

  while (WiFi.status() != WL_CONNECTED) //check wifi status and wait for it to connect
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
//  for (int i = 0; i < 8; i ++) {   //Loop through all rgb colors
//    digitalWrite(red, sequence[i][0]);
//    digitalWrite(green, sequence[i][1]);
//    digitalWrite(blue, sequence[i][2]);
//    delay(500);
//  }


  WiFiClient client = server.available(); // Listen for incoming clients,if there is a client connection

  if (client) {

    while (!client.available()); //wait until client has data available for reading

    Serial.println("new client");

    String request = client.readStringUntil('\n');  //read the data
    Serial.println(request);

    if (request.indexOf("/r1") != -1) {
      value = HIGH;
      digitalWrite(red, LOW);
    }

    else if (request.indexOf("/r0") != -1) {
      value = LOW;
      digitalWrite(red, HIGH);
    }

    else if (request.indexOf("/g1") != -1) {
      value = LOW;
      digitalWrite(green, LOW);
    }
    else if (request.indexOf("/g0") != -1) {
      value = LOW;
      digitalWrite(green, HIGH);
    }
    else if (request.indexOf("/b1") != -1) {
      value = LOW;
      digitalWrite(blue, LOW);
    }
    else if (request.indexOf("/b0") != -1) {
      value = LOW;
      digitalWrite(blue, HIGH);
    }


    client.println("HTTP/1.1 200 OK");  //http response header
    client.println("Content-Type : text/html");
    client.println();
    client.println("<!DOCTYPE HTML>"); // specify version of html
    client.println("<html>");
    client.println("<h1> My First website </h1>");

    client.println("<br>");
    client.print("LED is now ");
    if (value == HIGH ) client.println ("ON");
    else if (value == LOW ) client.println("OFF");
    //      client.println("<a href = https://www.google.com> Visit Google </a>");
    client.println("<a href =/LED=ON> <button> Turn on LED</button> </a>");
    client.println("<a href= /LED=OFF> <button> Turn off LED </button> </a>");

    client.println("</html>");
    Serial.println("Client disconnected");

  }
}


