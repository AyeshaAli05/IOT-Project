#include <Keypad.h>
const int ROW_NUM = 4; //four rows
const int COLUMN_NUM = 4; //three columns
char keys[ROW_NUM][COLUMN_NUM] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte pin_rows[ROW_NUM] = {13, 12, 14, 27,26}; //connect to the row pinouts of the keypad
byte pin_column[COLUMN_NUM] = {25,26,33,35}; //connect to the column pinouts of the keypad
Keypad keypad = Keypad( makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM );
const String password_1 = "1234"; // change your password here
const String password_2 = "5642"; // change your password here
const String password_3 = "4545"; // change your password here
String input_password;
void setup()
{
  Serial.begin(9600);
  pinMode(2,OUTPUT);
  input_password.reserve(32); // maximum input characters is 33, change if needed
}
void loop()
{ 
char key = keypad.getKey();
if (key)
{
Serial.println(key);
if(key == '*') 
{
input_password = ""; // reset the input password  
}
else if(key == '#') 
{
if(input_password == password_1 || input_password == password_2 || input_password == password_3) {
Serial.println("password is correct");
digitalWrite(2,HIGH);
delay(2000);
digitalWrite(2,LOW);
} 
else 
{
Serial.println("password is incorrect");
}
input_password = ""; // reset the input password
} 
else 
{
input_password += key; // append new character to input password string
}
}
}
