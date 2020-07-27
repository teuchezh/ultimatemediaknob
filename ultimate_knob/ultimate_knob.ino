/////////////////////////////////////////////////////////
#define CLK 4
#define DT 5
#define SW 6
#include "HID-Project.h"
#include <GyverEncoder.h>
Encoder enc(CLK, DT, SW);
////////////////////////////////////////////////////////
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT);
///////////////////////////////////////////////////////
#include "GyverTimer.h"
GTimer hiTimer(MS);
///////////////////////////////////////////////////////
const int pinLed = LED_BUILTIN;
#include <GyverButton.h>
#define BTN_PIN 7
GButton lshift(BTN_PIN);
///////////////////////////////////////////////////////
void setup()
{
  enc.setType(TYPE2);
  enc.setTickMode(AUTO);
  Keyboard.begin();
  System.begin();
  Serial.begin(9600);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextColor(WHITE);
  display.clearDisplay();

  hiTimer.setTimeout(3000);
  hello();
}

void loop()
{
  display.setCursor(0, 0);
  display.setTextSize(2);

  lshift.tick();
  if (lshift.isHold())
  {
    prog2();
  }
  else
  {
    prog1();
  }
}

void hello()
{
  hiTimer.start();
  display.println("Ultimate Knob");
  display.display();

  if (hiTimer.isReady())
  {
    display.clearDisplay();
    Serial.println("Таймер сработал");
  }
}

void prog1()
{
  display.clearDisplay();
  Serial.println("Программа 1 выполняется");
  if (enc.isClick())
  {
    Consumer.write(MEDIA_PLAY_PAUSE);
    display.println("PLAY/PAUSE");
    display.display();
  }
  else if (enc.isDouble())
  {
    Consumer.write(MEDIA_NEXT);
    display.println("NEXT");
    display.display();
  }
  else if (enc.isHolded())
  {
    Consumer.write(MEDIA_VOL_MUTE);
    display.println("MUTE");
    display.display();
  }
  else if (enc.isRight())
  {
    Consumer.write(MEDIA_VOL_UP);
    display.println("VOL UP");
    display.display();
  }
  else if (enc.isLeft())
  {
    Consumer.write(MEDIA_VOL_DOWN);
    display.println("VOL DOWN");
    display.display();
  }
  else
  {
  }
}

void prog2()
{
  display.clearDisplay();
  Serial.println("Программа 2 выполняется");
  if (enc.isDouble())
  {
    Keyboard.press(KEY_LEFT_ALT);
    Keyboard.press(KEY_TAB);
    Keyboard.release(KEY_TAB);
    display.println("ALT+TAB");
    display.display();
  }
  else if (enc.isRight())
  {
    Keyboard.press(KEY_RIGHT_ARROW);
    Keyboard.release(KEY_RIGHT_ARROW);
    display.println("RIGHT ARROW");
    display.display();
  }
  else if (enc.isLeft())
  {
    Keyboard.press(KEY_LEFT_ARROW);
    Keyboard.release(KEY_LEFT_ARROW);
    display.println("LEFT ARROW");
    display.display();
  }
  else if (enc.isClick())
  {
    Keyboard.releaseAll();
    display.println("RELEASE ALL");
    display.display();
  }
}