void Line_Notify(String message) ;
#include <string.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecureAxTLS.h> 


#define WIFI_SSID "toen_teen_2.4G"
#define WIFI_PASSWORD "0636511325"


#define LINE_TOKEN "0jRnYogxafWoGC0w2bUsLLJl5d6j7WBU3dJm5dijnzJ"
int check = 0;
int value = 0;





void setup() {
  
  pinMode(D6, INPUT);

  Serial.begin(9600);

  WiFi.mode(WIFI_STA);
  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
}

void loop() {
   int sensorValue = digitalRead(D6);
  
  if (sensorValue == 0 and check == 1) {
    Serial.print("sensorValue");
    Serial.println(sensorValue);
    Serial.print("check");
    Serial.println(check);
    Serial.println("state 2");
  }
  else if (sensorValue == 0 and check == 0) {
    check = 1;
    Serial.print("sensorValue");
    Serial.println(sensorValue);
    Serial.print("check");
    Serial.println(check);
    Serial.println("state 1");
    value += 1;
    char message[] = "ได้รับของจำนวน  ";
    char str[100];
    char message2[] = " ชิ้น";
    sprintf(str, "%d", value);
    strcat(str, message2);
    strcat(message, str);
    Line_Notify(message);
  }
  else if (sensorValue == 1 and check == 1) {
    check = 0;
    Serial.print("sensorValue");
    Serial.println(sensorValue);
    Serial.print("check");
    Serial.println(check);
    Serial.println("state 3");
  }
  Serial.println(sensorValue);
  delay(1000);
}

void Line_Notify(String message) {
  axTLS::WiFiClientSecure client; 

  if (!client.connect("notify-api.line.me", 443)) {
    Serial.println("connection failed");
    return;   
  }

  String req = "";
  req += "POST /api/notify HTTP/1.1\r\n";
  req += "Host: notify-api.line.me\r\n";
  req += "Authorization: Bearer " + String(LINE_TOKEN) + "\r\n";
  req += "Cache-Control: no-cache\r\n";
  req += "User-Agent: ESP8266\r\n";
  req += "Connection: close\r\n";
  req += "Content-Type: application/x-www-form-urlencoded\r\n";
  req += "Content-Length: " + String(String("message=" + message).length()) + "\r\n";
  req += "\r\n";
  req += "message=" + message;
  // Serial.println(req);
  client.print(req);
    
  delay(20);

  // Serial.println("-------------");
  while(client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") {
      break;
    }
    //Serial.println(line);
  }
  // Serial.println("-------------");
}
