#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);  // LCD pins

int mq3Pin = A0;  // Analog pin for MQ-3
int mq4Pin = A1;  // Analog pin for MQ-4
int ledPin = 8;   // Digital pin for LED
int thresholdMQ3 = 150;
int thresholdMQ4 = 200;

void setup() {
  lcd.begin(16, 2);  // Initialize the LCD
  Serial.begin(9600);  // Initialize serial communication

  pinMode(ledPin, OUTPUT);  // LED pin as an output
}

void loop() {
  int mq3Value = analogRead(mq3Pin);
  int mq4Value = analogRead(mq4Pin);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("CO: " + String(mq3Value));
  lcd.setCursor(0, 1);
  lcd.print("CH4: " + String(mq4Value));

  if (mq3Value > thresholdMQ3) {
    digitalWrite(ledPin, HIGH); // Turn on LED
  } else {
    digitalWrite(ledPin, LOW);  // Turn off LED
  }

  if (mq4Value > thresholdMQ4) {
    digitalWrite(ledPin, HIGH); // Turn on LED
  } else {
    digitalWrite(ledPin, LOW);  // Turn off LED
  }

  // Send data to MIT App Inventor via Bluetooth
  Serial.print("CO:");
  Serial.print(mq3Value);
  Serial.print(",CH4:");
  Serial.println(mq4Value);

  delay(1000);  // Delay to avoid spamming the data
}