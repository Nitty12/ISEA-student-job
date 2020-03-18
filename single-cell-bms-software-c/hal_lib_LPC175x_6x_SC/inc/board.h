/*
 * board.h
 *
 *  Created on: 09.08.2019
 *      Author: abl
 */

#ifndef BOARD_H_
#define BOARD_H_

#include "chip.h"

// Board name
#define BOARD_ISEA_SINGLE_CELL_BMS

// GPIO Port and Pin definitions
#define GPIO_mc_1_PIN				29
#define GPIO_mc_1_PORT				1
#define GPIO_mc_2_PIN				28
#define GPIO_mc_2_PORT				1
#define GPIO_mc_3_PIN				27
#define GPIO_mc_3_PORT				1
#define GPIO_mc_4_PIN				26
#define GPIO_mc_4_PORT				1
#define GPIO_mc_5_PIN				25
#define GPIO_mc_5_PORT				1
#define GPIO_mc_6_PIN				24
#define GPIO_mc_6_PORT				1
#define GPIO_mc_7_PIN				23
#define GPIO_mc_7_PORT				1
#define GPIO_mc_8_PIN				22
#define GPIO_mc_8_PORT				1
#define GPIO_mc_9_PIN				21
#define GPIO_mc_9_PORT				1
#define GPIO_mc_10_PIN				20
#define GPIO_mc_10_PORT				1
#define GPIO_mc_11_PIN				19
#define GPIO_mc_11_PORT				1

// SPI Port and Pin definitions
#define SPI_mc_SCK_PIN				15
#define SPI_mc_SCK_PORT				0
#define SPI_mc_SSEL_PIN				16
#define SPI_mc_SSEL_PORT			0
#define SPI_mc_MISO_PIN				17
#define SPI_mc_MISO_PORT			0
#define SPI_mc_MOSI_PIN				18
#define SPI_mc_MOSI_PORT			0

// UART Port and Pin definitions
#define UART3_TX_PIN				28
#define UART3_TX_PORT				4
#define UART3_TX_IOCON				IOCON_FUNC3
#define UART3_RX_PIN				29
#define UART3_RX_PORT				4
#define UART3_RX_IOCON				IOCON_FUNC3


/**
 * CAN connection that is used.\n
 * Currently CAN1 is applied.
 */
#define CAN1 1
#define CAN2 2

#define CAN_USED CAN1

#if CAN_USED == CAN1
#define LPC_CAN             (LPC_CAN1)
#define CAN_CTRL_NO			0
#else
#define LPC_CAN             (LPC_CAN2)
#define CAN_CTRL_NO			1
#endif


/*
 * CAN pin and ports. CAN1 is actually applied in hardware.
 */
#define CAN_SELECT_PORT		0
#define CAN_SELECT_PIN		10
#if CAN_USED == CAN1
#define CAN_RD1_PORT		0
#define CAN_RD1_PIN			0
#define CAN_TD1_PORT		0
#define CAN_TD1_PIN			1
#else
#define CAN_RD2_PORT		0
#define CAN_RD2_PIN			4
#define CAN_TD2_PORT		0
#define CAN_TD2_PIN			5
#endif


/**
 * Use the Acceptance Filter - Look Up Table ?
 */
#define AF_LUT_USED         1


/**
 * Use the FULL-CAN mode?
 */
#if AF_LUT_USED
#define FULL_CAN_AF_USED    1
#endif




/* Pin muxing configuration */
STATIC const PINMUX_GRP_T pinmuxing[] = {
												// Altium	- 	µC datasheet

	// CAN		-	CAN1
	{0,  0,   IOCON_MODE_INACT | IOCON_FUNC1},	// CAN_RX	-	RD1
	{0,  1,   IOCON_MODE_INACT | IOCON_FUNC1},	// CAN_TX	-	TD1
	{0, 10,   IOCON_MODE_INACT | IOCON_FUNC0},	// CAN_S 	- 	P0[10]

	// ADC_µC	-	ADC
	{0, 23,   IOCON_MODE_INACT | IOCON_FUNC1},	// AD0-0 	- 	AD0[0]
	{0, 24,   IOCON_MODE_INACT | IOCON_FUNC1},	// AD0-1 	- 	AD0[1]
	{0, 25,   IOCON_MODE_INACT | IOCON_FUNC1},	// AD0-2 	- 	AD0[2]
	{1, 30,   IOCON_MODE_INACT | IOCON_FUNC2},	// AD0-4 	- 	AD0[4]
	{1, 31,   IOCON_MODE_INACT | IOCON_FUNC2},	// AD0-5 	- 	AD0[5]
	{0,  3,   IOCON_MODE_INACT | IOCON_FUNC2},	// AD0-6 	- 	AD0[6]

	// DAC_µC	-	PWM/DAC
	{0, 26,   IOCON_MODE_INACT | IOCON_FUNC2},	// DAC_µC	-	AOUT
	{1, 18,   IOCON_MODE_INACT | IOCON_FUNC2},	// DAC_µC	-	PWM1[1]

	// SPI_µC	-	SSP0
	{0, 15,   IOCON_MODE_INACT | IOCON_FUNC2},	// SCK 		- 	SCK0
	{0, 16,   IOCON_MODE_INACT | IOCON_FUNC2},	// SSEL		- 	SSEL0
	{0, 17,   IOCON_MODE_INACT | IOCON_FUNC2},	// MISO		- 	MISO0
	{0, 18,   IOCON_MODE_INACT | IOCON_FUNC2},	// MOSI		- 	MOSI0

	// GPIO_µC	-	P1[X]
	{1, 29,   IOCON_MODE_INACT | IOCON_FUNC0},	// GPIO-1	-	P1[29]
	{1, 28,   IOCON_MODE_INACT | IOCON_FUNC0},	// GPIO-2	-	P1[28]
	{1, 27,   IOCON_MODE_INACT | IOCON_FUNC0},	// GPIO-3	-	P1[27]
	{1, 26,   IOCON_MODE_INACT | IOCON_FUNC0},	// GPIO-4	-	P1[26]
	{1, 25,   IOCON_MODE_INACT | IOCON_FUNC0},	// GPIO-5	-	P1[25]
	{1, 24,   IOCON_MODE_INACT | IOCON_FUNC0},	// GPIO-6	-	P1[24]
	{1, 23,   IOCON_MODE_INACT | IOCON_FUNC0},	// GPIO-7	-	P1[23]
	{1, 22,   IOCON_MODE_INACT | IOCON_FUNC0},	// GPIO-8	-	P1[22]
	{1, 21,   IOCON_MODE_INACT | IOCON_FUNC0},	// GPIO-9	-	P1[21]
	{1, 20,   IOCON_MODE_INACT | IOCON_FUNC0},	// GPIO-10	-	P1[20]
	{1, 19,   IOCON_MODE_INACT | IOCON_FUNC0},	// GPIO-11	-	P1[19]


	// UART3
	{UART3_TX_PORT, UART3_TX_PIN,   IOCON_MODE_INACT | UART3_TX_IOCON},
	{UART3_RX_PORT, UART3_RX_PIN,   IOCON_MODE_INACT | UART3_RX_IOCON}

	// Emergency-	NMI
//	{2, 10,   IOCON_MODE_INACT | IOCON_FUNC2},	// Emergency-	NMI


};





 void Board_Init(void);
 void board_system_init(void);


#include "board_api.h"
#include "arm_math.h"

#endif /* BOARD_H_ */
