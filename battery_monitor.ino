// NodeMCU (ESP8266) battery voltage monitor
// 16x2 I2C LCD (0x27) on D2 (SDA) / D1 (SCL), battery via voltage divider on A0
// Divider: R_TOP = 20k, R_BOTTOM = 10k

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int batteryPin = A0;

const float R_TOP = 20000.0;
const float R_BOTTOM = 10000.0;
const float A0_MAX_VOLTAGE = 1.0;

void setup() {
  Serial.begin(115200);

  Wire.begin(D2, D1);
  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("Battery Monitor");
}

void loop() {
  int adcValue = analogRead(A0);

  float adcVoltage =
      (adcValue / 1023.0) * A0_MAX_VOLTAGE;

  float batteryVoltage =
      adcVoltage * (R_TOP + R_BOTTOM) / R_BOTTOM;

  Serial.print("Battery Voltage: ");
  Serial.print(batteryVoltage, 2);
  Serial.println(" V");

  lcd.setCursor(0, 1);
  lcd.print("Voltage: ");
  lcd.print(batteryVoltage, 2);
  lcd.print(" V   ");

  delay(1000);
}
