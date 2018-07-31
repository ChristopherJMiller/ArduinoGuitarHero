/*
 * ArduinoGuitarHero - Wii Guitar Hero Controller Library for Arduino
 *
 * Based off the wonderful ArduinoNunchuck Library by Gabriel Bianconi, http://www.gabrielbianconi.com/
 * Under Copyright (c) 2014, Gabriel Bianconi All rights reserved.
 */

#include <Arduino.h>
#include <Wire.h>
#include "ArduinoGuitarHero.h"

#define ADDRESS 0x52

void ArduinoGuitarHero::init()
{
  Wire.begin();

  ArduinoGuitarHero::_sendByte(0x55, 0xF0);
  ArduinoGuitarHero::_sendByte(0x00, 0xFB);

  ArduinoGuitarHero::update();
}

void ArduinoGuitarHero::update()
{
  int count = 0;
  int values[6];

  Wire.requestFrom(ADDRESS, 6);

  while(Wire.available())
  {
    values[count] = Wire.read();
    count++;
  }

  ArduinoGuitarHero::sX = values[0] - 192;
  ArduinoGuitarHero::sY = values[1] - 192;
  ArduinoGuitarHero::TB = values[2];
  ArduinoGuitarHero::WB = values[3] - 239;
  ArduinoGuitarHero::STRUM = (values[4] & 64) == 0 ? -1 : (values[5] & 1) == 0 ? 1 : 0;
  ArduinoGuitarHero::BPlus = (values[4] & 4) == 0 ? 1 : 0;
  ArduinoGuitarHero::BMinus = (values[4] & 16) == 0 ? 1 : 0;

  ArduinoGuitarHero::BG = (values[5] & 16) == 0 ? 1 : 0;
  ArduinoGuitarHero::BR = (values[5] & 64) == 0 ? 1 : 0;
  ArduinoGuitarHero::BY = (values[5] & 8) == 0 ? 1 : 0;
  ArduinoGuitarHero::BB = (values[5] & 32) == 0 ? 1 : 0;
  ArduinoGuitarHero::BO = (values[5] & 128) == 0 ? 1 : 0;

  ArduinoGuitarHero::_sendByte(0x00, 0x00);
}

void ArduinoGuitarHero::_sendByte(byte data, byte location)
{
  Wire.beginTransmission(ADDRESS);
  Wire.write(location);
  Wire.write(data);

  Wire.endTransmission();

  delay(10);
}
