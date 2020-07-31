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
#define SW1_PIN 7
#define SW2_PIN 8
#define SW3_PIN 9
GButton lshift(SW1_PIN);
GButton rshift(SW2_PIN);
GButton ctrl(SW3_PIN);
#define MODES 4 // количество режимов (от 0 до указанного)
byte mode = 0;
///////////////////////////////////////////////////////
void setup()
{
  enc.setType(TYPE2);
  enc.setTickMode(AUTO);
  ctrl.setTickMode(AUTO);
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
  ctrl.tick();
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(2);

  if (ctrl.isPress())
  {
    if (++mode >= MODES)
      mode = 0;
  }
  switch (mode)
  {
  case 0:
    prog0();
    break;
  case 1:
    prog1();
    break;
  case 2:
    prog2();
    break;
  case 3:
    prog3();
    break;
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

void prog0() //layot for media control; раскладка для управления медиа;
{
  display.clearDisplay();
  Serial.println("*Layout 1 is works*");

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
}

void prog1() //layout for window switch; раскладка для переключения окон;
{
  display.clearDisplay();
  Serial.println("*Layout 2 is works*");

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

void prog2() //layout for.. hmm, i don't know, maybe use in browser for page scroll;
{
  Serial.println("*Layout 3 is works*");
  display.clearDisplay();

  if (enc.isClick())
  {
    Keyboard.press(KEY_ENTER);
    Keyboard.release(KEY_ENTER);
    display.println("ENTER");
    display.display();
  }
  else if (enc.isLeft())
  {
    Keyboard.press(KEY_UP_ARROW);
    Keyboard.release(KEY_UP_ARROW);
    display.println("ARROW UP");
    display.display();
  }
  else if (enc.isRight())
  {
    Keyboard.press(KEY_DOWN_ARROW);
    Keyboard.release(KEY_DOWN_ARROW);
    display.println("ARROW DOWN");
    display.display();
  }
  //need code for release all leys? NEED DEBUG
}

void prog3() //layout for tab switch in browser; раскладка для переключения между вкладками в браузере;
{
  Serial.println("*Layout 4 is works*");
  display.clearDisplay();

  if (enc.isLeft())
  {
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press(KEY_PAGE_DOWN);
    Keyboard.releaseAll();
    display.println("Previous Tab");
    display.display();
  }
  else if (enc.isRight())
  {
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press(KEY_PAGE_UP);
    Keyboard.releaseAll();
    display.println("Next Tab");
    display.display();
  }
  else if (enc.isDouble())
  {
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press(KEY_LEFT_SHIFT);
    Keyboard.press(KEY_T);
    Keyboard.releaseAll();
    display.println("Open Closed Tab");
    display.display();
  }
  else if (enc.isHolded())
  {
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press(KEY_W);
    Keyboard.releaseAll();
    display.println("Close Tab");
    display.display();
  }
}