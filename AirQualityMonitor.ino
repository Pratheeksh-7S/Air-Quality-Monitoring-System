/*
  Air Quality Monitoring System
  Components: Arduino Uno, MQ135 Gas Sensor, 16x2 LCD (direct-wired), Buzzer
  Description: Reads air quality (PPM) from MQ135, displays it on LCD,
               and triggers a buzzer alert if pollution crosses a safe threshold.
*/

#include <LiquidCrystal.h>

// LCD pins: RS, E, D4, D5, D6, D7
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

const int mq135Pin = A0;     // MQ135 analog output pin
const int buzzerPin = 8;     // Buzzer digital pin
const int threshold = 300;   // Safe air quality threshold (adjust after calibration)

void setup() {
  Serial.begin(9600);
  pinMode(buzzerPin, OUTPUT);

  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Air Quality Mon.");
  delay(2000);
  lcd.clear();
}

void loop() {
  int sensorValue = analogRead(mq135Pin);   // Raw ADC value (0-1023)
  int airQuality = map(sensorValue, 0, 1023, 0, 500); // Map to approx PPM scale

  Serial.print("Air Quality (PPM): ");
  Serial.println(airQuality);

  lcd.setCursor(0, 0);
  lcd.print("Air Quality:");
  lcd.setCursor(0, 1);
  lcd.print(airQuality);
  lcd.print(" PPM      "); // extra spaces to clear old digits

  if (airQuality > threshold) {
    digitalWrite(buzzerPin, HIGH);
    lcd.setCursor(10, 1);
    lcd.print("BAD!");
  } else {
    digitalWrite(buzzerPin, LOW);
  }

  delay(1000); // Update every second
}
