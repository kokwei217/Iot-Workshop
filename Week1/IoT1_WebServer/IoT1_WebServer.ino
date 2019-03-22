#include <ESP8266WiFi.h>

const char* ssid = "kokwei";
const char* password = "kokwei97";
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
  WiFiClient client = server.available(); // Listen for incoming clients,if there is a client connection

  if (client) {

    while (client.connected()) {    //wait until client has data available for reading

      if (client.available()) {

        Serial.println("new client");

        String request = client.readStringUntil('\n');  //read the data
        Serial.println(request);

        if (request.indexOf("/LED=ON") != -1) {
          value = HIGH;
          digitalWrite(led, HIGH);
        }

        else if (request.indexOf("/LED=OFF") != -1) {
          value = LOW;
          digitalWrite(led, LOW);
        }


        client.println("HTTP/1.1 200 OK");  //http response header
        client.println("Content-Type : text/html");
        client.println();
        client.println("<!DOCTYPE HTML>"); // specify version of html
        client.println("<html>");
        client.println("<h1> My First website </h1>");
//        client.println("<a href = https://www.google.com> Visit Google  </a>");   
        client.println("<a href = /LED=ON > <button>  <b>turn on led  </button> </b> </a>");
        client.println("<a href = /LED=OFF> turn off led  </a>");

        client.println("</html>");
        Serial.println("Client disconnected");
        break;
      }
    }
  }
}
