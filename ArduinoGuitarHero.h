/*
 * ArduinoGuitarHero - Wii Guitar Hero Controller Library for Arduino
 *
 * Based off the wonderful ArduinoNunchuck Library by Gabriel Bianconi, http://www.gabrielbianconi.com/
 * Under Copyright (c) 2014, Gabriel Bianconi All rights reserved.
 */

#ifndef ArduinoGuitarHero_H
#define ArduinoGuitarHero_H

#include <Arduino.h>

class ArduinoGuitarHero
{
  public:
    int sX;
    int sY;
    int TB;
    int WB;
    int STRUM;
    int BPlus;
    int BMinus;

    int BG;
    int BR;
    int BY;
    int BB;
    int BO;

    void init();
    void update();

  private:
    void _sendByte(byte data, byte location);
};

#endif
