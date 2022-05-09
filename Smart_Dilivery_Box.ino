#include <MicroGear.h>
#include "WiFi.h"
#include <ESP32Servo.h>
#include <Keypad.h>
#include <LiquidCrystal_I2C.h>

// set the LCD number of columns and rows
int lcdColumns = 16;
int lcdRows = 2;
const int ROW_NUM = 4; //four rows
const int COLUMN_NUM = 4; //three columns
char keys[ROW_NUM][COLUMN_NUM] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte pin_rows[ROW_NUM] = {13,12,14,27}; //connect to the row pinouts of the keypad
byte pin_column[COLUMN_NUM] = {25,26,32,33}; //connect to the column pinouts of the keypad
Keypad keypad = Keypad( makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM );
 
int pass_attempt_no=0;
int  disable_flag =0;
const char* ssid = "ThailandFang24_2G"; //Enter SSID
const char* password = "0887688468"; //Enter Password

//const char* ssid = "blush"; //Enter SSID
//const char* password = "987654321"; //Enter 

  #define APPID   "IoTSmartDeliveryBox"              // use group AppID 
  #define KEY     "CC0IB4rbIMvbKe9"                // use group Key
  #define SECRET  "1zhnZ9P8rHN3HXRWt3lBSI5eC"             // use group Secret
  #define ALIAS   "IoTProject"  // your device name, ex. "A01"
  #define DATATOPIC "/Lock/IoTProject"         // topic   
  #define LatTOPIC "/Lat/IoTProject"         // topic for lat  
  #define LongTOPIC "/Long/IoTProject"         // topic for long
String input_password;
const String password_1 = "9999"; // change your password here
const String password_2 = "7951"; // change your password here
String password_3 = "dummyvariacjffjghgg"; // change your password here

Servo myservo;  // create servo object to control a servo

LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);  
 
int pos = 0;    // variable to store the servo position
// Recommended PWM GPIO pins on the ESP32 include 2,4,12-19,21-23,25-27,32-33 
int servoPin = 15;

   WiFiClient client;
     MicroGear microgear(client);
       int timer = 0;
  int lastSend = 0;
bool lock_status = 1;
  int currentLEDState = 1;
  int key_count=0;

  float lat_value = 13.75;
  float long_value = 100.5;

/* If a new message arrives, do this */
void onMsghandler(char *topic, uint8_t* msg, unsigned int msglen) {
    Serial.print("Incoming message --> ");
    msg[msglen] = '\0';
    Serial.println((char *)msg);
    
    if(*(char *)msg == 'L') 
{
Serial.println("Locking");
myservo.write(90);
lock_status = 0;
lcd.clear();
lcd.setCursor(0,0);
lcd.print("DOOR LOCKED");
delay(1000);
lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("ENTER PASSWORD");
}
   else if(*(char *)msg == 'C') 
{
input_password = ""; // reset the input password
Serial.println("Clearing Passowrd");
}

   else if (*(char *)msg == 'U')
    {
        disable_flag = 0;
        Serial.println("Device Enabled");
        lcd.clear();
       lcd.setCursor(0, 0);
       lcd.print("Device");
       lcd.setCursor(0, 1);
       lcd.print("Enabled");
       pass_attempt_no=0;
       delay(2000);
       lcd.clear();
       lcd.print("Enter Password");
      }

   else if (*(char *)msg == 'E')
    {
      Serial.println("The Password is:");
      Serial.println(input_password);
      password_3=input_password;
      input_password = "";
      }
    else 
{
input_password += *(char *)msg; // append new character to input password string
}
}

void onFoundgear(char *attribute, uint8_t* msg, unsigned int msglen) {
    Serial.print("Found new member --> ");
    for (int i=0; i<msglen; i++)
        Serial.print((char)msg[i]);
    Serial.println();  
}

void onLostgear(char *attribute, uint8_t* msg, unsigned int msglen) {
    Serial.print("Lost member --> ");
    for (int i=0; i<msglen; i++)
        Serial.print((char)msg[i]);
    Serial.println();
}

/* When a microgear is connected, do this */
void onConnected(char *attribute, uint8_t* msg, unsigned int msglen) {
    Serial.println("Connected to NETPIE...");
    /* Set the alias of this microgear ALIAS */
    microgear.setAlias(ALIAS);
}

     

void setup(void)
{ 

    // Allow allocation of all timers
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);
  myservo.setPeriodHertz(50);    // standard 50 hz servo
  myservo.attach(servoPin, 500, 2400); // attaches the servo on pin 18 to the servo object
   input_password.reserve(32); // maximum input characters is 33, change if needed
  
  Serial.begin(115200);


 /* Add Event listeners */

    /* Call onMsghandler() when new message arraives */
    microgear.on(MESSAGE,onMsghandler);

    /* Call onFoundgear() when new gear appear */
    microgear.on(PRESENT,onFoundgear);

    /* Call onLostgear() when some gear goes offline */
    microgear.on(ABSENT,onLostgear);

    /* Call onConnected() when NETPIE connection is established */
    microgear.on(CONNECTED,onConnected);
    // initialize LCD
   lcd.init();
   // turn on LCD backlight                      
   lcd.backlight();
     lcd.setCursor(0, 0);
  // print message
  lcd.print("SMART DILIVERY");
  lcd.setCursor(0,1);
  lcd.print("BOX");
  
    Serial.println("Starting..."); 
      // Connect to WiFi
    if (WiFi.begin(ssid, password)) {
        while (WiFi.status() != WL_CONNECTED) {
            delay(500);
            Serial.print(".");
        }
    }

    Serial.println("WiFi connected");  
    lcd.clear();
   lcd.setCursor(0, 0);
  lcd.print("WiFi Connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    /* Initial with KEY, SECRET and also set the ALIAS here */
    microgear.init(KEY,SECRET,ALIAS);

    /* connect to NETPIE to a specific APPID */
    microgear.connect(APPID);  
    delay(2000);
    lcd.clear();
  lcd.print("Enter Password");

       
}

void loop() 
{
if (disable_flag == 0)
{
char key = keypad.getKey();

if (key)
{
   lcd.setCursor(key_count, 1);  
  lcd.print(key);
  key_count=key_count+1;
Serial.println(key);
if (pass_attempt_no <=5)
{
if(key == '*') 
{
input_password = ""; // reset the input password
Serial.println("Clearing Passowrd");
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("CLEARING PASSWORD");
  key_count=0;
  delay(1000);
  lcd.clear();
  lcd.print("Enter Password");
}
else if(key == 'D') 
{
Serial.println("Locking");
lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("LOCKED");
   myservo.write(90);
   lock_status = 0;
   key_count=0;
     delay(1000);
  lcd.clear();
  lcd.print("Enter Password");
  
}
else if(key == '#') 
{
if(input_password == password_1 || input_password == password_2 || input_password == password_3) {
Serial.println("password is correct");
lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Correct Password");
Serial.println(input_password);
Serial.println("Unlocking");
    myservo.write(180);
    lock_status = 1;
      lcd.setCursor(0,1);
  lcd.print("UNLOCKED");
  key_count=0;
   microgear.publish("/@push/owner","The Device has been unlocked");
} 
else 
{
Serial.println("password is incorrect");
Serial.println(input_password);
lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("WRONG PASSWORD");
  pass_attempt_no=pass_attempt_no+1;
  key_count=0;
      delay(1000);
    lcd.clear();
  lcd.print("Enter Password");
}
input_password = ""; // reset the input password
} 
else 
{
input_password += key; // append new character to input password string
}
}
else
{
  lcd.clear();
   lcd.setCursor(0,0);
  lcd.print("MAX Attempts");
  lcd.setCursor(0,1);
  lcd.print("Device Diabled");
  disable_flag = 1;
   microgear.publish("/@push/owner","The device has been disabled");
  }
}

}
 /* To check if the microgear is still connected */
    if (microgear.connected()) {
       // Serial.println("connected");
        /* Call this method regularly otherwise the connection may be lost */
        microgear.loop();
    }
        else {
        Serial.println("connection lost, reconnect...");
        if (timer >= 5000) {
            microgear.connect(APPID);
            timer = 0;
        }
        else timer += 100;
    }

   if(millis() - lastSend > 3000)
    {
        StatusSend(lock_status);
       // lock_status= !lock_status;
        lastSend=millis();
      }


    delay(100);
}

void StatusSend (bool lock_status) {           
    Serial.print("Lock Status: "); Serial.print(lock_status); 
     String datastring = "";
    if (lock_status == 0)
    {
     datastring = "DOOR LOCKED";
      }
      else
      {
        datastring = "DOOR OPEN";
        }
       lat_value=lat_value + 0.001;
       long_value = long_value + 0.002; 
      String latstring = (String)lat_value;
      String longstring = (String)long_value;
      Serial.print("Sending --> ");
      Serial.println(datastring);
      microgear.publish(DATATOPIC,datastring);    
       Serial.print("Sending --> ");
      Serial.println(datastring);
      microgear.publish(LatTOPIC,latstring);
      Serial.print("Sending --> ");
      Serial.println(datastring);
     microgear.publish(LongTOPIC,longstring);         
      }


      
