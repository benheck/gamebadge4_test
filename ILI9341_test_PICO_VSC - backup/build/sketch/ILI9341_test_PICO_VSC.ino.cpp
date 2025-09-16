#line 1 "C:\\Users\\benja\\OneDrive\\Documents\\Github\\gamebadge4_test\\ILI9341_test_PICO_VSC\\ILI9341_test_PICO_VSC.ino"
//WHATEVER THIS GAME IS
#include <Arduino.h>
#include "src/graphics.h"

#line 5 "C:\\Users\\benja\\OneDrive\\Documents\\Github\\gamebadge4_test\\ILI9341_test_PICO_VSC\\ILI9341_test_PICO_VSC.ino"
void setup();
#line 11 "C:\\Users\\benja\\OneDrive\\Documents\\Github\\gamebadge4_test\\ILI9341_test_PICO_VSC\\ILI9341_test_PICO_VSC.ino"
void loop();
#line 5 "C:\\Users\\benja\\OneDrive\\Documents\\Github\\gamebadge4_test\\ILI9341_test_PICO_VSC\\ILI9341_test_PICO_VSC.ino"
void setup()
{
  Serial.begin(11500);
  setupGame();                     // Initialize graphics
}

void loop()
{
  mainGameLoop();
}


