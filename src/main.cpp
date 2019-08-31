#include <Arduino.h>
#include <TroykaMQ.h>
#include <Wire.h>

#define PIN_MQ2  A1
#define PIN_MQ3  A2
#define PIN_MQ135  A0
#define PIN_MQ8 A3
#define PIN_MQ4 A4
#define PIN_MQ6 A5
#define PIN_MQ7 A6

MQ3 mq3(PIN_MQ3);
MQ2 mq2(PIN_MQ2);
MQ135 mq135(PIN_MQ135);
MQ8 mq8(PIN_MQ8);
MQ4 mq4(PIN_MQ4);
MQ6 mq6(PIN_MQ6);
MQ7 mq7(PIN_MQ7);

String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

void setup()
{
  Serial.begin(9600);

  mq2.calibrate();
  mq3.calibrate();
  mq135.calibrate();
  mq8.calibrate();
  mq4.calibrate();
  mq6.calibrate();
  mq7.calibrate();

  /*Serial.print("Ro mq2 = ");
  Serial.println(mq2.getRo());
  Serial.print("Ro mq3 = ");
  Serial.println(mq3.getRo());*/
}

void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}

void sendData() {
  float mq2_ratio = mq2.readRatio();
  unsigned long mq2_lpg = mq2.readLPG();
  unsigned long mq2_methane = mq2.readMethane();
  unsigned long mq2_smoke = mq2.readSmoke();
  unsigned long mq2_hydrogen = mq2.readHydrogen();
  float mq3_ratio = mq3.readRatio();
  unsigned long mq3_alcohol_mgl = mq3.readAlcoholMgL();
  unsigned long mq3_alcohol_ppm = mq3.readAlcoholPpm();
  float mq135_ratio = mq135.readRatio();
  unsigned long mq135_co2 = mq135.readCO2();
  float mq8_ratio = mq8.readRatio();
  unsigned mq8_hydrogen = mq8.readHydrogen();
  float mq4_ratio = mq4.readRatio();
  unsigned long mq4_methane = mq4.readMethane();
  float mq6_ratio = mq6.readRatio();
  unsigned long mq6_lpg = mq6.readLPG();
  float mq7_ratio = mq7.readRatio();
  unsigned long mq7_co = mq7.readCarbonMonoxide();

  //Serial.print("Ratio: ");
  //Serial.print(mq2_ratio);
  //Serial.print("\tLPG: ");
  Serial.print(mq2_lpg);
  Serial.print(",");
  //Serial.print("\tMethane: ");
  Serial.print(mq2_methane);
  Serial.print(",");
  //Serial.print("\tSmoke: ");
  Serial.print(mq2_smoke);
  Serial.print(",");
  //Serial.print("\tHydrogen: ");
  Serial.print(mq2_hydrogen);
  Serial.print(",");
  //Serial.print("Ratio: ");
  //Serial.print(mq3_ratio);
  //Serial.print(" Alcohol: ");
  Serial.print(mq3_alcohol_mgl);
  Serial.print(",");
  Serial.print(mq3_alcohol_ppm);
  Serial.print(",");
  Serial.print(mq135_co2);
  Serial.print(",");
  Serial.print(mq8_hydrogen);
  Serial.print(",");
  Serial.print(mq4_methane);
  Serial.print(",");
  Serial.print(mq6_lpg);
  Serial.print(",");
  Serial.println(mq7_co);

  /*if (uvIndex > f_uvIndex_max)
   f_uvIndex_max = uvIndex;
  Serial.print(" UV ix max : ");
  Serial.println(f_uvIndex_max);*/
}

void loop()
{

  if (stringComplete) {
    sendData();
  //Serial.println(inputString);
  // clear the string:
  inputString = "";
  stringComplete = false;
}

  delay(5000);
}
