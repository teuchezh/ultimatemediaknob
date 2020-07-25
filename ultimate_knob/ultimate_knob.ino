#define CLK 4
#define DT 5
#define SW 6
#include "HID-Project.h"
#include <GyverEncoder.h>
Encoder enc(CLK, DT, SW);

const int pinLed = LED_BUILTIN;
#include <GyverButton.h>
#define BTN_PIN 7
GButton lshift(BTN_PIN);

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT);
void setup()
{
  enc.setType(TYPE2);
  enc.setTickMode(AUTO);
  pinMode(pinLed, OUTPUT);
  Keyboard.begin();
  System.begin();
  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
}

void loop()
{
  lshift.tick();

  if (lshift.isHold())
  {
    prog2();
  }
  else
  {
    prog1();
    display.clearDisplay();
  }

  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
}

void prog1()
{
  Serial.println("Программа 1 выполняется");
  if (enc.isClick())
  {
    Consumer.write(MEDIA_PLAY_PAUSE);
    display.println("PLAY/PAUSE");
    display.display();
  }
  if (enc.isDouble())
  {
    Consumer.write(MEDIA_NEXT);
    display.println("NEXT");
    display.display();
  }
  if (enc.isHolded())
  {
    Consumer.write(MEDIA_VOL_MUTE);
    display.println("MUTE");
    display.display();
  }
  if (enc.isRight())
  {
    Consumer.write(MEDIA_VOL_UP);
    display.println("VOL UP");
    display.display();
  }
  if (enc.isLeft())
  {
    Consumer.write(MEDIA_VOL_DOWN);
    display.println("VOL DOWN");
    display.display();
  }
}

void prog2()
{
  Serial.println("Программа 2 выполняется");
}
