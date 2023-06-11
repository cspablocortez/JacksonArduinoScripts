/*
 * Created by ArduinoGetStarted.com
 *
 * This example code is in the public domain
 *
 * Tutorial page: https://arduinogetstarted.com/tutorials/arduino-keypad
 */

#include <Keypad.h>
#include <Servo.h>
#include <LiquidCrystal_I2C.h>

const int ROW_NUM = 4; //four rows
const int COLUMN_NUM = 4; //four columns
Servo myservo;  // create servo object to control a servo

bool is_unlocked = false;

LiquidCrystal_I2C lcd(0x27,16,2);  /*I2C scanned address defined + I2C screen size*/

char keys[ROW_NUM][COLUMN_NUM] = {
  {'1','2','3', 'A'},
  {'4','5','6', 'B'},
  {'7','8','9', 'C'},
  {'*','0','#', 'D'}
};

byte pin_rows[ROW_NUM] = {5, 6, 7, 8}; //connect to the row pinouts of the keypad
byte pin_column[COLUMN_NUM] = {9, 10, 11, 12}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM );

const String password = "1234"; // change your password here
String input_password;
String fake_pass = "";

int pos = 0;    // variable to store the servo position


void setup(){
  Serial.begin(9600);
  input_password.reserve(32); // maximum input characters is 33, change if needed
  myservo.attach(2);
  lcd.init();  /*LCD display initialized*/
  lcd.clear();     /*Clear LCD Display*/
  lcd.backlight();      /*Turn ON LCD Backlight*/

}
void loop(){
  char key = keypad.getKey();

  if (key){
    if(key == 'A' && is_unlocked){
       for (pos = 0; pos <= 90; pos += 1) { // goes from 0 degrees to 180 degrees
          // in steps of 1 degree
          myservo.write(pos);              // tell servo to go to position in variable 'pos'
          delay(15);                       // waits 15ms for the servo to reach the position
        }
        lcd.clear();
        is_unlocked = false;
    } else{
    if(key == '*') {
      input_password = ""; // clear input password
      fake_pass = "";
    } else if(key == '#') {
      if(password == input_password) {
        is_unlocked = true;
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("hellow master");
        input_password = ""; // clear input password
        fake_pass = "";
        for (pos = 0; pos >= -90; pos -= 1) { // goes from 0 degrees to 180 degrees
          // in steps of 1 degree
          myservo.write(pos);              // tell servo to go to position in variable 'pos'
          delay(15);                       // waits 15ms for the servo to reach the position
        }
        
        // DO YOUR WORK HERE
        
      } else {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("you suk, try");
        lcd.setCursor(0,1);
        lcd.print("again ya lil poo");
        delay(5000);
        lcd.clear();
      

      input_password = ""; // clear input password
      fake_pass = "";
      }
    } else {
      input_password += key; // append new character to input password string
      fake_pass += "*";
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(fake_pass);
    }
  }
  }
}