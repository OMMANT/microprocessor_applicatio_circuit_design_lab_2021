//-------| src/led.c |-------//
#include "led.h"

static short * led;

void init_led(short * address) {
	led = address;
	*led = 0xFF;
	usleep(50000);
}

void led_write(int n){
	int temp = 0;
	// 0: 0xFF, 1: 0x7F, 2: 0x3F, 3: 0x1F, 4: 0xF, 5: 0x7, 6: 0x3, 7: 0x1, 8: 0x0
	for(int i = 0; i < n; i++){
		temp <<= 1;
		temp++;
	}
	for(int i = 0; i < 8 - n; i++){
		temp <<= 1;
	}
	*led = (0xFF - temp);
	usleep(50000);
}

