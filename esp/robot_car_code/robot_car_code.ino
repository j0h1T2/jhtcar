//more details on robohub instructables page//

#define ENA   14          // Enable/speed motors Right        GPIO14(D5)
#define ENB   12          // Enable/speed motors Left         GPIO12(D6)
#define IN_1  15          // L298N in1 motors Right           GPIO15(D8)
#define IN_2  13          // L298N in2 motors Right           GPIO13(D7)
#define IN_3  2           // L298N in3 motors Left            GPIO2(D4)
#define IN_4  0           // L298N in4 motors Left            GPIO0(D3)

#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>

String command;             //String to store app command state.
int speedCar = 800;         // 400 - 1023.
int speed_Coeff = 3;

const char* ssid = "jhtCar";
const char* password = "20201026tu";
ESP8266WebServer server(80);//创建了一个在 ESP8266 上运行的简单 web 服务器，并将其绑定到标准的 HTTP 端口（端口 80）。

void setup() {
 
 pinMode(ENA, OUTPUT);
 pinMode(ENB, OUTPUT);  
 pinMode(IN_1, OUTPUT);
 pinMode(IN_2, OUTPUT);
 pinMode(IN_3, OUTPUT);
 pinMode(IN_4, OUTPUT);
 pinMode(LED_BUILTIN, OUTPUT); 
 digitalWrite(LED_BUILTIN,HIGH);
  
  Serial.begin(115200);
  
// Connecting WiFi

  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid,password);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
 
 // Starting WEB-server 
     server.on ( "/", HTTP_handleRoot );
     server.onNotFound ( HTTP_handleRoot );
     server.begin();    
}

void goAhead(){ 

      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, HIGH);
      analogWrite(ENA, speedCar);

      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, HIGH);
      analogWrite(ENB, speedCar);
  }

void goBack(){ 

      digitalWrite(IN_1, HIGH);
      digitalWrite(IN_2, LOW);
      analogWrite(ENA, speedCar);

      digitalWrite(IN_3, HIGH);
      digitalWrite(IN_4, LOW);
      analogWrite(ENB, speedCar);
  }

void goRight(){ 

      digitalWrite(IN_1, HIGH);
      digitalWrite(IN_2, LOW);
      analogWrite(ENA, speedCar);

      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, HIGH);
      analogWrite(ENB, speedCar);
  }

void goLeft(){

      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, HIGH);
      analogWrite(ENA, speedCar);

      digitalWrite(IN_3, HIGH);
      digitalWrite(IN_4, LOW);
      analogWrite(ENB, speedCar);
  }

void goAheadRight(){
      
      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, HIGH);
      analogWrite(ENA, speedCar/speed_Coeff);
 
      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, HIGH);
      analogWrite(ENB, speedCar);
   }

void goAheadLeft(){
      
      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, HIGH);
      analogWrite(ENA, speedCar);

      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, HIGH);
      analogWrite(ENB, speedCar/speed_Coeff);
  }

void goBackRight(){ 

      digitalWrite(IN_1, HIGH);
      digitalWrite(IN_2, LOW);
      analogWrite(ENA, speedCar/speed_Coeff);

      digitalWrite(IN_3, HIGH);
      digitalWrite(IN_4, LOW);
      analogWrite(ENB, speedCar);
  }

void goBackLeft(){ 

      digitalWrite(IN_1, HIGH);
      digitalWrite(IN_2, LOW);
      analogWrite(ENA, speedCar);

      digitalWrite(IN_3, HIGH);
      digitalWrite(IN_4, LOW);
      analogWrite(ENB, speedCar/speed_Coeff);
  }

void stopRobot(){  

      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, LOW);
      analogWrite(ENA, 0);

      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, LOW);
      analogWrite(ENB, 0);
 }

void loop() {
    server.handleClient();//来自客户端的请求，使设备可以进行通信
    
      command = server.arg("State");
  if (command == "W") {
    goAhead();
    server.send(200, "text/plain", "Moving forward");
    flashLED();
  } else if (command == "S") {
    goBack();
    flashLED();
  } else if (command == "A") {
    goLeft();
    flashLED();
  } else if (command == "D") {
    goRight();
    flashLED();
  } else if (command == "E") {
    goAheadRight();
    flashLED();
  } else if (command == "Q") {
    goAheadLeft();
    flashLED();
  } else if (command == "C") {
    goBackRight();
    flashLED();
  } else if (command == "Z") {
    goBackLeft();
    flashLED();
  } else if (command == "0") {
    speedCar = 400;
    flashLED();
  } else if (command == "1") {
    speedCar = 470;
    flashLED();
  } else if (command == "2") {
    speedCar = 540;
    flashLED();
  } else if (command == "3") {
    speedCar = 610;
    flashLED();
  } else if (command == "4") {
    speedCar = 680;
    flashLED();
  } else if (command == "5") {
    speedCar = 750;
    flashLED();
  } else if (command == "6") {
    speedCar = 820;
    flashLED();
  } else if (command == "7") {
    speedCar = 890;
    flashLED();
  } else if (command == "8") {
    speedCar = 960;
    flashLED();
  } else if (command == "9") {
    speedCar = 1023;
    flashLED();
  } else if (command == "G") {
    server.send(200, "text/plain", "CLOSED");
    digitalWrite(LED_BUILTIN, LOW);
    stopRobot();    
  }
  else{}
}

void flashLED(){
  digitalWrite(LED_BUILTIN,LOW);
  delay(100);
  digitalWrite(LED_BUILTIN,HIGH);
}

void HTTP_handleRoot(void) {

if( server.hasArg("State") ){
       Serial.println(server.arg("State"));
  }
  server.send ( 200, "text/html", "" );
  delay(1000);
}
