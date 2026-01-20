#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include <math.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo launcherServo;

const int potPin = A0;
const int buttonPin = 2;
const int servoPin = 9;

const int minAngle = 0;
const int maxAngle = 90;

const float velocity = 5.0;   
const float g = 9.8;          

bool fired = false;

void setup() {
  launcherServo.attach(servoPin);
  pinMode(buttonPin, INPUT_PULLUP);

  lcd.init();
  lcd.backlight();

  launcherServo.write(minAngle);

  lcd.setCursor(0,0);
  lcd.print("Projectile");
  lcd.setCursor(0,1);
  lcd.print("Ready");
}

void loop() {
  int potValue = analogRead(potPin);
  int angle = map(potValue, 0, 1023, minAngle, maxAngle);

  float theta = angle * PI / 180.0;
  float range = 0.46 * sin(theta);


  lcd.setCursor(0,0);
  lcd.print("Angle:");
  lcd.print(angle);
  lcd.print((char)223);
  lcd.print("   ");

  lcd.setCursor(0,1);
  if (!fired) {
    lcd.print("Range:");
    lcd.print(range * 100, 2);
    lcd.print(" cm ");
  }

  if (digitalRead(buttonPin) == LOW && !fired) {
    fired = true; // mark as fired
    lcd.setCursor(0,1);
    lcd.print("Launching...    ");

    launcherServo.write(angle); 
    delay(400);   
    launcherServo.write(minAngle);
    delay(500);   
    lcd.setCursor(0,1);
    lcd.print("Ready           ");
  }

  if (digitalRead(buttonPin) == HIGH) {
    fired = false;
  }
}
