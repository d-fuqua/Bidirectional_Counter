#include <WiFi.h>
#include <HTTPClient.h>

int irPin1 = 25;
int irPin2 = 26;
int count = 0;
boolean state1 = true;
boolean state2 = true;
boolean insideState = false;
boolean outsideIr = false;
boolean isPeopleExiting = false;
int i = 1;
int restaurantId = 15;
char ssid[] = "ZyXEL045ED8";
char  pass[] = "F4ME3V79PVH9R";
int status = WL_IDLE_STATUS;
char server[] = "https://gunnarhoffman.com/sos";
String postData;
String postVariable = "Current People Count = ";
WiFiClient client;

     
void setup() {
  Serial.begin(9600);
  pinMode(irPin1, INPUT);
  pinMode(irPin2, INPUT);
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to Network named: ");
    Serial.println(ssid);
    status = WiFi.begin(ssid, pass);
    delay(1000);}
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());
  IPAddress ip = WiFi.localIP();
  IPAddress gateway = WiFi.gatewayIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
}
void loop() {
 
 

  if (!digitalRead(irPin1) && i == 1 && state1) {
    outsideIr = true;
    delay(50);
    i++;
    state1 = false;
  }

  if (!digitalRead(irPin2) && i == 2 &&   state2) {
    outsideIr = true;
    delay(50);
    i = 1 ;
    count++;
    Serial.println("entered ");
                   
  postData = postVariable + count;
                    if (client.connect(server, 80)) {
                    char data[100]; 
                     sprintf(data,"%d",count);
                     Serial.println("Connected to server");
                     client.println("POST /sos HTTP/1.1");
                     client.println("content-type: application/json");
                     client.print("content-length: ");
                     client.println(strlen(data));
                     client.print("Host: ");
                     client.println("gunnarhoffman.com/sos");
                     client.println("Connection: close");
                     client.println();
                     client.println(data);}
    state2 = false;
  }

  if (!digitalRead(irPin2) && i == 1 && state2 ) {
    outsideIr = true;
    delay(50);
    i = 2 ;
    state2 = false;
  }

  if (!digitalRead(irPin1) && i == 2 && state1 ) {
    outsideIr = true;
    delay(50);
    count--;
    Serial.println("exited");

 postData = postVariable + count;               
                     if (client.connect(server, 80)) {
                     char data[100]; 
                     sprintf(data,"%d",count);
                     Serial.println("Connected to server");
                     client.println("POST /sos HTTP/1.1");
                     client.println("content-type: application/json");
                     client.print("content-length: ");
                     client.println(strlen(data));
                     client.print("Host: ");
                     client.println("gunnarhoffman.com/sos");
                     client.println("Connection: close");
                     client.println();
                     client.println(data);}
    i = 1;
    state1 = false;
  }

  if (digitalRead(irPin1)) {
    state1 = true;
  }

  if (digitalRead(irPin2)) {
    state2 = true;
  }
                     while(client.available()){
                     String line = client.readStringUntil('\r');
                     Serial.println(line);}

                       if (client.connected()) {
                       client.stop();
                        }
                        Serial.println(postData);

                        delay(100);
                     
}
