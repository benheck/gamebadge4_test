//WHATEVER THIS GAME IS
#include <Arduino.h>
#include "src/graphics.h"

void setup()
{
  Serial.begin(11500);
  setupGame();                     // Initialize graphics
}

void loop()
{
  mainGameLoop();
}

