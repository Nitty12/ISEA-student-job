/*
 * board.c
 *
 *  Created on: 09.08.2019
 *      Author: abl
 */


#include "board.h"


const uint32_t OscRateIn = 16000000;
//const uint32_t OscRateIn = 12000000;

const uint32_t RTCOscRateIn = 0;


void Board_Init(void){
	// System Clock
	Chip_SetupXtalClocking();
	SystemCoreClockUpdate();

	// GPIO
	Chip_GPIO_Init(LPC_GPIO);
	Chip_IOCON_Init(LPC_IOCON);


}


/**
 * Setup the chip clocking.
 */
void board_system_init(void){
	Chip_SetupXtalClocking();
}
