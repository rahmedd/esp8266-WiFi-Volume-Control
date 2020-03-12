//Only edit the constants under Wifi setup.

#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

//LCD setup
LiquidCrystal_I2C lcd(0x27, 16, 2);
const int analogInPin = A0;
int sensorValue = 0;

//Wifi setup
WiFiUDP Udp;
const int serverPort = 20001; //can be changed if port is in use on host pc
const char userSSID[] = "SSID";
const char userPASS[] = "PASS";

//Debounce ish?
int prevpercent = 0;

void setup() {
  //Init display and MCU
  lcd.begin();
  Serial.begin(9600);

  //Wifi setup
  WiFi.begin(userSSID, userPASS);
  Serial.print("Connecting...");

  //Shows wifi status on LCD & serial
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    lcd.setCursor(6, 0);
    lcd.print("WiFi");
    lcd.setCursor(2, 1);
    lcd.print("disconnected.");
    Serial.print("WiFi disconnected.");
    Serial.print(".");
  }
  
  //Shows ip address on serial
  Serial.println();
  Serial.print("Succsessfully connected to network.");
  Serial.println();
  Serial.print(WiFi.localIP());

  lcd.clear();
}

void loop() {
  delay(50); //loop delay (mainly to keep display from flickering- need to rewrite display update func to reduce latency)
  
  //Display init
  lcd.clear();
  
  //first row
  lcd.setCursor(6, 0);
  sensorValue = analogRead(analogInPin);
  int percent = (sensorValue*100)/1024;
  lcd.print(percent);
  lcd.print("%");

  //second row
  lcd.setCursor(0, 1);
  char volbar[16] = {};
  for (int i=0; i<percent*0.16; i++){
    volbar[i] = 'O';
  }
  lcd.print(volbar);

  //send UDP packet
  if(percent != prevpercent){ //only send packet if value has updated
    Udp.beginPacket("YOUR PC'S IP", serverPort);
    char perctostr[3] = {}; //Percent to string arr
    itoa(percent, perctostr, 10);
    Udp.write(perctostr);
    Udp.endPacket();
  }

  //Displays error if wifi disconnected
  while (WiFi.status() != WL_CONNECTED){
    lcd.setCursor(6, 0);
    lcd.print("WiFi disconnected.");
    Serial.print("WiFi disconnected.");
  }
  
  prevpercent = percent; //update previous value
}
