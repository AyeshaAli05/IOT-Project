 #include <ESP32Servo.h>
 #include <Keypad.h>
 
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
const String password_1 = "1234"; // change your password here
const String password_2 = "5642"; // change your password here
const String password_3 = "4545"; // change your password here
String input_password;

Servo myservo;  // create servo object to control a servo
// 16 servo objects can be created on the ESP32
 
int pos = 0;    // variable to store the servo position
// Recommended PWM GPIO pins on the ESP32 include 2,4,12-19,21-23,25-27,32-33 
int servoPin = 15;
 
void setup() {
  // Allow allocation of all timers
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);
  myservo.setPeriodHertz(50);    // standard 50 hz servo
  myservo.attach(servoPin, 500, 2400); // attaches the servo on pin 18 to the servo object
   input_password.reserve(32); // maximum input characters is 33, change if needed
   Serial.begin(115200);
}
 
void loop() {

  char key = keypad.getKey();
if (key)
{
Serial.println(key);
if(key == '*') 
{
input_password = ""; // reset the input password
Serial.println("Clearing Passowrd");
}
else if(key == 'D') 
{
Serial.println("Locking");
   myservo.write(0);
  
}
else if(key == '#') 
{
if(input_password == password_1 || input_password == password_2 || input_password == password_3) {
Serial.println("password is correct");
Serial.println(input_password);
Serial.println("Unlocking");
    myservo.write(180);
} 
else 
{
Serial.println("password is incorrect");
Serial.println(input_password);
}
input_password = ""; // reset the input password
} 
else 
{
input_password += key; // append new character to input password string
}
}
 
}
