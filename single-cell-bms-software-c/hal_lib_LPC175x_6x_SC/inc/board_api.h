/*
 * board_api.h
 *
 *  Created on: 09.08.2019
 *      Author: abl
 */

#ifndef BOARD_API_H_
#define BOARD_API_H_

#include "lpc_types.h"
#include <stdio.h>


/**
 * @brief	Setup and initialize hardware prior to call to main()
 * @return	None
 * @note	Board_SystemInit() is called prior to the application and sets up system
 * clocking, memory, and any resources needed prior to the application
 * starting.
 */
void Board_SystemInit(void);

/**
 * @brief	Setup pin multiplexer per board schematics
 * @return	None
 * @note	Board_SetupMuxing() should be called from SystemInit() prior to application
 * main() is called. So that the PINs are set in proper state.
 */
void Board_SetupMuxing(void);

/**
 * @brief	Setup system clocking
 * @return	None
 * @note	This sets up board clocking.
 */
void Board_SetupClocking(void);

/**
 * @brief	Set up and initialize all required blocks and functions related to the board hardware.
 * @return	None
 */
void Board_Init(void);

#endif /* BOARD_API_H_ */
