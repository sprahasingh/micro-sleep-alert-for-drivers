/*
  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)
 */

// include the library code:
#include <LiquidCrystal.h>
#include <Servo.h>

Servo myservo;

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int PIRpin=7;
const int buzzer=6;
const int ledPin=8;
int PIRval=0;

void setup() {
  pinMode(PIRpin, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(ledPin, OUTPUT);
  
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  // Print a message to the LCD.
  lcd.print("DRIVER DROWSINESS");
  lcd.setCursor(1, 1);
  lcd.print("DETECTOR BY 12B");
  delay(2000);
  
  Serial.begin(9600);
  myservo.attach(9);
  myservo.write(0);
}

void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  lcd.print(millis() / 1000);
  
  PIRval=digitalRead(7);
  Serial.println(PIRval);
   
  if(PIRval==1)
  {
    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.print("Driver Drowsy!");
    lcd.setCursor(0, 1);
  	digitalWrite(buzzer,HIGH);
    digitalWrite(ledPin,HIGH);
    myservo.write(90);
    delay(2000);
    myservo.write(0);
    delay(1000);
  }
   
  else{
    digitalWrite(ledPin, LOW);
    digitalWrite(buzzer, LOW);
    lcd.setCursor(0, 0);
    lcd.print("Driver is awake.");
  }
}
 