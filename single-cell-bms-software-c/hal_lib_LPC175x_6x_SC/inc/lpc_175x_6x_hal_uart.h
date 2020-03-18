/*
 * lpc_175x_6x_hal_uart.h
 *
 *  Created on: 30.12.2019
 *      Author: abl
 */

#ifndef LPC_175X_6X_HAL_UART_H_
#define LPC_175X_6X_HAL_UART_H_

#include <board.h>
#include <string.h>
#include <lpc_175x_6x_hal_can.h>

#define UART_SELECTION 	LPC_UART3
#define IRQ_SELECTION 	UART3_IRQn
#define HANDLER_NAME 	UART3_IRQHandler



/* Transmit and receive ring buffer sizes */
#define UART_SRB_SIZE 128	/* Send */
#define UART_RRB_SIZE 128	/* Receive */



void lpc_175x_6x_hal_uart_init(uint16_t can_receive, uint16_t can_transmit);
void uart_send(void *data,uint16_t size);
void HANDLER_NAME(void);

#endif /* LPC_175X_6X_HAL_UART_H_ */
