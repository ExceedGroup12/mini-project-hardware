int ldr1 = 32;
int ldr2 = 33;
int ldr3 = 34;
int led1 = 19;
int led2 = 21;
int led3 = 5;
int state1 = 0; //0 คือ ว่าง
int state2 = 0;
int state3 = 0;
#include<WiFi.h>
#include<HTTPClient.h>
#include<ArduinoJson.h>
#include <string.h>
#include <stdio.h>
const char* ssid="pooh A52s";
const char* password = "Xxxmen_2543";
const char* urlPOST = "https://ecourse.cpe.ku.ac.th/exceed12/api/update";
char str[50];


const int _size = 2*JSON_OBJECT_SIZE(4);
StaticJsonDocument<_size> JSONPost;
StaticJsonDocument<_size> JSONGet;


void WiFi_Connect(){
  WiFi.disconnect();
  WiFi.begin(ssid,password);
  while(WiFi.status()!=WL_CONNECTED){
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to the WiFi network");
  Serial.print("IP Address : ");
  Serial.println(WiFi.localIP());
}

void _post(String room,int statusroom){
  if(WiFi.status() == WL_CONNECTED){
    HTTPClient http;

    http.begin(urlPOST);
    http.addHeader("Content-Type","application/json");
  
    JSONPost["room"] = room;
    JSONPost["status"] = statusroom;
    serializeJson(JSONPost,str);
    int httpCode = http.POST(str);

    if(httpCode == HTTP_CODE_OK){
      String payload = http.getString();
      Serial.println(httpCode);
      Serial.println(payload);     
    }
    else{
      Serial.println(httpCode);
      Serial.println("ERROR on HTTP Request");
    }
  }
  else{
    WiFi_Connect();
  } 
}

void setup() {
  digitalWrite(led1,HIGH);
  digitalWrite(led2,HIGH);
  digitalWrite(led3,LOW);
  pinMode(led1,OUTPUT);
  pinMode(ldr1,INPUT);
  pinMode(led2,OUTPUT);
  pinMode(ldr2,INPUT);
  pinMode(led3,OUTPUT);
  pinMode(ldr3,INPUT);
  Serial.begin(9600); 
  WiFi_Connect();
}



void loop(){
   //Serial.println(analogRead(ldr0));
   //ห้อง1
   if(analogRead(ldr1)>1000 and state1 == 0)
   { 
     digitalWrite(led1,LOW);
     state1 = 1; 
     _post("l1",1);     
     //Serial.println("R1,1");
     //Serial.println(digitalRead(led1));
     //room1 = "R1";
     //statusroom1 = "1";
   }  
   else if(analogRead(ldr1)<1000 and state1 == 1)
   {
     digitalWrite(led1,HIGH);
     state1 = 0;
     _post("l1",0);     
     //Serial.println("R1,0");
     //Serial.println(digitalRead(led1));
     //room1 = "R1";
     //statusroom1 = "0";
   }

   //ห้อง2
   if(analogRead(ldr2)>1000 and state2 == 0)
   { 
     digitalWrite(led2,LOW);
     state2 = 1; 
     _post("l2",1);     
     //Serial.println("R2,1");
     //Serial.println(digitalRead(led2));
     //room2 = "R2";
     //statusroom2 = "1";
   }  
   else if(analogRead(ldr2)<1000 and state2 == 1)
   {
     digitalWrite(led2,HIGH);
     state2 = 0;
     _post("l2",0);     
     //Serial.println("R2,0");
     //Serial.println(digitalRead(led2));
     //room2 = "R2";
     //statusroom2 = "0";
   }

   //ห้อง3
   if(analogRead(ldr3)>1000 and state3 == 0)
   { 
     digitalWrite(led3,HIGH);
     state3 = 1; 
     _post("l3",1);     
     //Serial.println("R3,1");
     //Serial.println(digitalRead(led3));
     //room3 = "R3";
     //statusroom3 = "1";
   }  
   else if(analogRead(ldr3)<1000 and state3 == 1)
   {
     digitalWrite(led3,LOW);
     state3 = 0;
     _post("l3",0);     
     //Serial.println("R3,0");
     //Serial.println(digitalRead(led3));
     //room3 = "R3";
     //statusroom3 = "0";
   }
   delay(10);  
}
