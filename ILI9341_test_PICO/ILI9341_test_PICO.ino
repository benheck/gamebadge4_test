/***********************************************************************************
  This program is a demo of clearing ILI9341 screen to display red,green,blue.
  modified from _9341uno.ino example program from LCD WIKI
  8bit parallel data port.  MCUFRIEND pin layout.  Screen size of 320x240 using coded values
**********************************************************************************/
#include <gameBadgePico4.h>
#include <Arduino.h>

#define TE_PIN  28       //Tear effect from LCD to Pico
#define tft_test 15
uint32_t scroll = 0;
volatile int te_triggered = 0;  // Interrupt flag


void on_te_rising(uint gpio, uint32_t events) {
  if (gpio == TE_PIN && (events & GPIO_IRQ_EDGE_RISE)) {
    te_triggered++;
  }
}

void setup_te_interrupt() {
  gpio_init(TE_PIN);                    // Initialize the TE pin
  gpio_set_dir(TE_PIN, GPIO_IN);        // Set as input
  gpio_pull_down(TE_PIN);               // Optional: Use pull-down resistor
  gpio_set_irq_enabled_with_callback(TE_PIN, GPIO_IRQ_EDGE_RISE, true, on_te_rising);  // Enable rising edge interrupt
}

void setup()
{
  Serial.begin(9600);
  gamebadge4init();
  setup_te_interrupt();
	pinMode(tft_test, OUTPUT);

}

void loop()
{
  while(te_triggered < 2) {
    tight_loop_contents();  // Low-power wait     
  }
  te_triggered = 0;

  sendDMAframeBuffer();   //Single DMA dump of FB

  digitalWrite(tft_test, HIGH);

  mapToFrameBuffer();

	// for (int y = 0 ; y < 16 ; y++) {	
	// 	for (int x = 0 ; x < 16 ; x++) {
	// 		drawTile(x << 3, y << 3, 0, (y << 4) | x);
	// 	}	
	// }

	// for (int y = 0 ; y < 16 ; y++) {	
	// 	for (int x = 0 ; x < 16 ; x++) {
	// 		drawTile(x << 3, y << 3, 1, (y << 4) | x);
	// 	}	
	// }

  // for (int y = 0 ; y < 30 ; y++) {	
	// 	for (int x = 0 ; x < 40 ; x++) {
	// 		drawTile(x << 3, y << 3, 0, (y << 4) | x);
	// 	}	
	// }

  digitalWrite(tft_test, LOW);



}
