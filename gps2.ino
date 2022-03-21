

// Interfacing Arduino with NEO-6M GPS module

#include <TinyGPS++.h>           // Include TinyGPS++ library
//#include <SoftwareSerial.h>      // Include software serial library


TinyGPSPlus gps;
 
//#define S_RX    13                // Define software serial RX pin
//#define S_TX    4                // Define software serial TX pin

//#define RXD2 16
//#define TXD2 17
 
//SoftwareSerial SoftSerial(S_RX, S_TX);    // Configure SoftSerial library


 
void setup(void) {
   pinMode(23,OUTPUT);
  //Serial2.begin(baud-rate, protocol, RX pin, TX pin);
  //Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);
  Serial.begin(115200);
  //SoftSerial.begin(9600); 
  Serial2.begin(9600); 
  Serial.print("GPS interfacing with ESP");
}
 
void loop() {
  //digitalWrite(23,HIGH);
  while (Serial2.available() > 0) {
    
   
    if (gps.encode(Serial2.read())) {
       Serial.println("GPS interfacing with ESP");
     // digitalWrite(23,HIGH);
      if (gps.location.isValid()) {
        Serial.print("Latitude   = ");
        Serial.println(gps.location.lat(), 6);
        Serial.print("Longitude  = ");
        Serial.println(gps.location.lng(), 6);
      }
      else
        Serial.println("Location Invalid");
 
      if (gps.altitude.isValid()) {
        Serial.print("Altitude   = ");
        Serial.print(gps.altitude.meters());
        Serial.println(" meters");
      }
      else
        Serial.println("Altitude Invalid");
 
      if (gps.speed.isValid()) {
        Serial.print("Speed      = ");
        Serial.print(gps.speed.kmph());
        Serial.println(" kmph");
      }
      else
        Serial.println("Speed Invalid");
 
      if (gps.time.isValid()) {
        Serial.print("Time (GMT) : ");
        if(gps.time.hour() < 10)     Serial.print("0");
        Serial.print(gps.time.hour()+5); //time is changed by 5
        Serial.print(":");
        if(gps.time.minute() < 10)   Serial.print("0");
        Serial.print(gps.time.minute());
        Serial.print(":");
        if(gps.time.second() < 10)   Serial.print("0");
        Serial.println(gps.time.second());
      }
      else
        Serial.println("Time Invalid");
 
      if (gps.date.isValid()) {
        Serial.print("Date       : ");
        if(gps.date.day() < 10)      Serial.print("0");
        Serial.print(gps.date.day());
        Serial.print("/");
        if(gps.date.month() < 10)    Serial.print("0");
        Serial.print(gps.date.month());
        Serial.print("/");
        Serial.println(gps.date.year());
      }
      else
        Serial.println("Date Invalid");
 
      if (gps.satellites.isValid()) {
        Serial.print("Satellites = ");
        Serial.println(gps.satellites.value());
      }
      else
        Serial.println("Satellites Invalid");
        
 //int year1,month1,dayOfMonth,hour1,minute1,second1;



    
  //  unsigned long epoch = (((year1/4*(365*4+1)+days[year1%4][month1]+dayOfMonth)*24+hour1)*60+minute1)*60+second1;
    
    
    }




  }
 
}
