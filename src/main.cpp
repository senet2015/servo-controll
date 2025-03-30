#include <Arduino.h>
#include <ESP32Servo.h>
#include <ESP32Time.h>

#include <WiFi.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
#include <ESP32Time.h>

//const char* ssid = "CS_Sayeogsil"; // Replace with your network SSID
//const char* password = ""; // Replace with your network password

const char* ssid = "iptime_hunslab"; // Replace with your network SSID
const char* password = "87654321"; // Replace with your network password

WiFiUDP udp;
NTPClient timeClient(udp, "pool.ntp.org", 32400, 60000); // 32400 seconds offset for Korea (GMT+9)

//ESP32Time rtc;
ESP32Time rtc(3600);  // offset in seconds GMT+1

// put function declarations here:
Servo myServo;
//int servoPin = 18;
int servoPin = 17;

void testServo() {
    for (int angle = 0; angle <= 180; angle += 30) {
        myServo.write(angle);
        delay(500);
    }
    for (int angle = 180; angle >= 0; angle -= 30) {
        myServo.write(angle);
        delay(500);
    }
}

void setup() {
  // put your setup code here, to run once:
  myServo.attach(servoPin);
  myServo.write(0);
  Serial.begin(115200);
  WiFi.begin(ssid, password);
    
  while (WiFi.status() != WL_CONNECTED) {
      delay(1000);
      Serial.println("Connecting to WiFi...");
  }
    
  Serial.println("Connected to WiFi");
  timeClient.begin();
  //rtc.setTime(30, 24, 15, 17, 1, 2021);  // 17th Jan 2021 15:24:30
  //rtc.setTime(1609459200);  // 1st Jan 2021 00:00:00
  //rtc.offset = 7200; // change offset value

  Serial.println("Servo Motor Test start");   // (String) returns time with specified format 
  // myServo.write(45);
  // delay(20);
  // myServo.write(0);
  testServo();
/*---------set with NTP---------------*/
//  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
//  struct tm timeinfo;
//  if (getLocalTime(&timeinfo)){
//    rtc.setTimeStruct(timeinfo); 
//  }
}

void loop() {
  //  Serial.println(rtc.getTime());          //  (String) 15:24:38
  //  Serial.println(rtc.getDate());          //  (String) Sun, Jan 17 2021
  //  Serial.println(rtc.getDate(true));      //  (String) Sunday, January 17 2021
  //  Serial.println(rtc.getDateTime());      //  (String) Sun, Jan 17 2021 15:24:38
  //  Serial.println(rtc.getDateTime(true));  //  (String) Sunday, January 17 2021 15:24:38
  //  Serial.println(rtc.getTimeDate());      //  (String) 15:24:38 Sun, Jan 17 2021
  //  Serial.println(rtc.getTimeDate(true));  //  (String) 15:24:38 Sunday, January 17 2021
  //
  //  Serial.println(rtc.getMicros());        //  (long)    723546
  //  Serial.println(rtc.getMillis());        //  (long)    723
  //  Serial.println(rtc.getEpoch());         //  (long)    1609459200
  //  Serial.println(rtc.getSecond());        //  (int)     38    (0-59)
  //  Serial.println(rtc.getMinute());        //  (int)     24    (0-59)
  //  Serial.println(rtc.getHour());          //  (int)     3     (1-12)
  //  Serial.println(rtc.getHour(true));      //  (int)     15    (0-23)
  //  Serial.println(rtc.getAmPm());          //  (String)  pm
  //  Serial.println(rtc.getAmPm(true));      //  (String)  PM
  //  Serial.println(rtc.getDay());           //  (int)     17    (1-31)
  //  Serial.println(rtc.getDayofWeek());     //  (int)     0     (0-6)
  //  Serial.println(rtc.getDayofYear());     //  (int)     16    (0-365)
  //  Serial.println(rtc.getMonth());         //  (int)     0     (0-11)
  //  Serial.println(rtc.getYear());          //  (int)     2021

  //  Serial.println(rtc.getLocalEpoch());         //  (long)    1609459200 epoch without offset
  //  Serial.println(rtc.getTime("%A, %B %d %Y %H:%M:%S"));   // (String) returns time with specified format 
  // formating options  http://www.cplusplus.com/reference/ctime/strftime/


  timeClient.update();
    
  Serial.print("Current time: ");
  Serial.println(timeClient.getFormattedTime());
    
  //delay(1000); // Update every second
  
  //struct tm timeinfo = rtc.getTimeStruct();
  //Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");   //  (tm struct) Sunday, January 17 2021 07:24:38
  
  delay(960);
  // put your main code here, to run repeatedly:
  int hour = timeClient.getHours();
  int minuite = timeClient.getMinutes();
  int second = timeClient.getSeconds();

  //Serial.printf("%d %d %d",hour, minuite, second);   // (String) returns time with specified format 
  if(/*hour == 3 && minuite == 57 && */second == 40){
    myServo.write(45);
    Serial.println("Click OK");   // (String) returns time with specified format 
  }
  /*
  if(Serial.available()){
    int angle = Serial.parseInt();
    myServo.write(angle);
  }
  */
  delay(20);
  myServo.write(0);
  delay(20);
}