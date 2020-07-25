#define CLK 2
#define DT 3
#define SW 4
#include "HID-Project.h"
#include <GyverEncoder.h>
Encoder enc(CLK, DT, SW);

const int pinLed = LED_BUILTIN;
#include <GyverButton.h>
#define BTN_PIN 5
GButton lshift(BTN_PIN);

void setup()
{
  enc.setType(TYPE2);
  enc.setTickMode(AUTO);
  pinMode(pinLed, OUTPUT);
  //pinMode(lshift, INPUT_PULLUP);
  Keyboard.begin();
  System.begin();
  Serial.begin(9600);
}

void loop()
{
  lshift.tick();
  
  if (lshift.isHold())
  {
    myFunc();
    Serial.print("Основная функция выполняется");
  }
}

void myFunc()
{
  if (enc.isClick())
  {
    digitalWrite(pinLed, HIGH);
    Consumer.write(MEDIA_PLAY_PAUSE);
    digitalWrite(pinLed, LOW);
  }
  if (enc.isDouble())
  {
    digitalWrite(pinLed, HIGH);
    Consumer.write(MEDIA_NEXT);
    digitalWrite(pinLed, LOW);
  }
  if (enc.isHolded())
  {
    digitalWrite(pinLed, HIGH);
    Consumer.write(MEDIA_VOL_MUTE);
    digitalWrite(pinLed, LOW);
  }
  if (enc.isRight())
  {
    digitalWrite(pinLed, HIGH);
    Consumer.write(MEDIA_VOL_UP);
    digitalWrite(pinLed, LOW);
  }
  if (enc.isLeft())
  {
    digitalWrite(pinLed, HIGH);
    Consumer.write(MEDIA_VOL_DOWN);
    digitalWrite(pinLed, LOW);
  }
}
