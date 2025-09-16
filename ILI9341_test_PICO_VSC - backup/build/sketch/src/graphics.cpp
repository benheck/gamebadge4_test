#line 1 "C:\\Users\\benja\\OneDrive\\Documents\\Github\\gamebadge4_test\\ILI9341_test_PICO_VSC\\src\\graphics.cpp"
#include <gameBadgePico4.h>
#include <Arduino.h>

#define TE_PIN  28       //Tear effect from LCD to Pico
#define tft_test 15
uint32_t scroll = 0;
volatile int te_triggered = 0;  // Interrupt flag

int catSpeed = 5; // Speed of the cat sprite
int catX = -50;
bool catDir = true;

void on_te_rising(uint gpio, uint32_t events) {
  if (gpio == TE_PIN && (events & GPIO_IRQ_EDGE_RISE)) {
    te_triggered++;
  }
}

void setupGame()
{
    gamebadge4init();

    loadPattern("nes_0.bmp", 0);
    loadPattern("condo_0.bmp", 1);
    loadPattern("faces.bmp", 2);

    for (int x = 0 ; x < 64 ; x += 2) {
        drawTile(x, 0, 0, 208);
        drawTile(x, 1, 0, 208);
    }

    for (int x = 1 ; x < 64 ; x += 2) {
        drawTile(x, 0, 0, 209);
        drawTile(x, 1, 0, 209);
    }

    for (int y = 2 ; y < 30 ; y++) {
        drawTile(0, y, 0, 1);
        drawTile(19, y, 0, 2);
        drawTile(39, y, 0, 3);

        drawTile(45, y, 0, 4);
        drawTile(50, y, 0, 5);
        drawTile(61, y, 0, 6);	
    }

    for (int yy = 0 ; yy < 16 ; yy++) {		
        for (int xx = 0 ; xx < 16 ; xx++) {		
            drawTile(xx + 2, yy + 3, 1, (yy << 4) + xx);				
        }		
    }

    for (int x = 0 ; x < 64 ; x += 2) {
        drawTile(x, 29, 0, 208);
    }
    for (int x = 1 ; x < 64 ; x += 2) {
        drawTile(x, 29, 0, 209);
    }

    gpio_init(TE_PIN);                    // Initialize the TE pin
    gpio_set_dir(TE_PIN, GPIO_IN);        // Set as input
    gpio_pull_down(TE_PIN);
    gpio_set_irq_enabled_with_callback(TE_PIN, GPIO_IRQ_EDGE_RISE, true, on_te_rising);  // Enable rising edge interrupt

    pinMode(tft_test, OUTPUT);
    digitalWrite(tft_test, LOW);
}

void mainGameLoop()
{
    //Do stuff beyond frame rate here

  while(te_triggered < 2) {
    tight_loop_contents();  // Low-power wait     
  }

  te_triggered = 0;

  sendDMAframeBuffer();   //Single DMA dump of FB

  digitalWrite(tft_test, HIGH);

  tilesToFrameBuffer();

  drawSprite(catX, 10, 2, 0, 0, 8, 8);
  drawSprite(310 - catX, 70, 2, 8, 0, 8, 8);
  drawSprite(catX, 130, 2, 0, 8, 8, 8);

  drawSprite(200 - catX, 50, 2, 0, 0, 8, 8);
  drawSprite(catX + 100, 120, 2, 8, 0, 8, 8);
  drawSprite(200 - catX, 170, 2, 0, 8, 8, 8);

  drawSprite(catX + 20, 30, 2, 0, 0, 8, 8);
  drawSprite(290 - catX, 100, 2, 8, 0, 8, 8);
  drawSprite(catX + 30, 150, 2, 0, 8, 8, 8);

  drawSprite(100 - catX, 10, 2, 0, 0, 8, 8);
  drawSprite(catX + 200, 110, 2, 8, 0, 8, 8);
  drawSprite(100 - catX, 190, 2, 0, 8, 8, 8);

  digitalWrite(tft_test, LOW);

  if (catDir == true) {

    catX += catSpeed;

    if (catX > 310) {
      catDir = false;
      Serial.println("Cat changed direction A");
    }

  }
  else {

    catX -= catSpeed;

    if (catX < -20) {
      catDir = true;
      Serial.println("Cat changed direction B");
    }

  }


}


