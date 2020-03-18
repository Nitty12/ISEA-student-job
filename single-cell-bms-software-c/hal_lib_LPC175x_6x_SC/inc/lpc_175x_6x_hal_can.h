/*
 * lpc_175x_6x_hal_can.h
 *
 *  Created on: 09.08.2019
 *      Author: abl
 */

#ifndef LPC_175X_6X_HAL_CAN_H_
#define LPC_175X_6X_HAL_CAN_H_

#include "board.h"

#ifndef __CAN_17XX_40XX_H_
#include "can_17xx_40xx.h"
#endif

#ifndef __IOCON_17XX_40XX_H_
#include "iocon_17xx_40xx.h"
#endif

#define __DAC

#ifdef __DAC
extern uint8_t next_f_flag;
extern uint8_t emergency_flag;
extern uint8_t new_m_flag;
extern uint32_t next_frequency;
extern uint8_t next_periods;
extern float next_amplitude_max;
extern float next_amplitude_min;


#endif
#ifdef __ADC
extern uint8_t new_m_flag;
extern uint32_t next_frequency;
extern uint8_t next_periods;
extern float next_amplitude_max;
extern float next_amplitude_min;
#endif

/*
 * CAN functions
 */
void init_can(void);
void CAN_IRQHandler(void);
void process_cl_req(CAN_MSG_T message);
void send_can_message(char *data, uint16_t id, uint8_t length);
void send_multiplexer_status(void);
void checkCANErrorInfo(uint32_t Status);


void process_CAN_message(CAN_MSG_T message);

#ifdef __DAC
void process_CAN_message_DAC(CAN_MSG_T message);
#endif

#ifdef __ADC
void process_CAN_message_ADC(CAN_MSG_T message);
#endif


#endif /* LPC_175X_6X_HAL_CAN_H_ */
