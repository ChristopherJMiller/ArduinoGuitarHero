/*
   Arduino Guitar Hero
   A Part of the Guitar Hero Arduino Project at chrismiller.xyz
*/

#include <UnoJoy.h>
#include <Wire.h>
#include <ArduinoGuitarHero.h>

ArduinoGuitarHero guitar = ArduinoGuitarHero();

void setup()
{
  Serial.begin(115200);
  guitar.init();
  setupUnoJoy();
}

dataForController_t getControllerData(void) 
{
  guitar.update();

  dataForController_t controllerData = getBlankDataForController();
  controllerData.triangleOn = guitar.BG == 1;
  controllerData.circleOn = guitar.BR == 1;
  controllerData.squareOn = guitar.BY == 1;
  controllerData.crossOn = guitar.BB == 1;
  controllerData.l2On = guitar.BO == 1;

  controllerData.dpadUpOn = guitar.STRUM == 1;
  controllerData.dpadDownOn = guitar.STRUM == -1;

  controllerData.selectOn = guitar.BMinus == 1;
  controllerData.startOn = guitar.BPlus == 1;

  //Use analog stick bindings for the controller joystick
  controllerData.leftStickX = map(guitar.sX, 0, 63, 0, 255); // 0 -> 63
  controllerData.leftStickY = map(guitar.sY, 0, 63, 0, 255);

  controllerData.rightStickX = map(guitar.WB, -16, 16, 0, 255); // -16 -> 16 (about 12 on a real guitar, 16 is absolute maximum guitar controller can report)
  //Serial.println(controllerData.leftStickX);
  return controllerData;
}

void loop()
{
  dataForController_t controllerData = getControllerData();
  setControllerData(controllerData);
}
