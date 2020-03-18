/*
 * lpc_175x_6x_hal_ADS8568.h
 *
 *  Created on: 09.08.2019
 *      Author: abl
 */

#ifndef LPC_175X_6X_HAL_ADS8568_H_
#define LPC_175X_6X_HAL_ADS8568_H_

#include "board.h"

#include <lpc_175x_6x_hal_can.h>

#define ADS8568_SCLK_PIN		SPI_mc_SCK_PIN
#define ADS8568_SCLK_PORT		SPI_mc_SCK_PORT
#define ADS8568_SCLK_FUNC		IOCON_FUNC2
#define ADS8568_SDO_A_PIN		SPI_mc_MISO_PIN
#define ADS8568_SDO_A_PORT		SPI_mc_MISO_PORT
#define ADS8568_SDO_A_FUNC		IOCON_FUNC2
#define ADS8568_SDO_B_PIN		GPIO_mc_1_PIN
#define ADS8568_SDO_B_PORT		GPIO_mc_1_PORT
#define ADS8568_SDO_B_FUNC		IOCON_FUNC0
#define ADS8568_SDO_C_PIN		GPIO_mc_2_PIN
#define ADS8568_SDO_C_PORT		GPIO_mc_2_PORT
#define ADS8568_SDO_C_FUNC		IOCON_FUNC0
#define ADS8568_SDO_D_PIN		GPIO_mc_3_PIN
#define ADS8568_SDO_D_PORT		GPIO_mc_3_PORT
#define ADS8568_SDO_D_FUNC		IOCON_FUNC0
#define ADS8568_CS_PIN			SPI_mc_SSEL_PIN
#define ADS8568_CS_PORT			SPI_mc_SSEL_PORT
#define ADS8568_CS_FUNC			IOCON_FUNC2 //IOCON_FUNC3
#define ADS8568_ASLEEP_PIN		GPIO_mc_4_PIN
#define ADS8568_ASLEEP_PORT		GPIO_mc_4_PORT
#define ADS8568_ASLEEP_FUNC		IOCON_FUNC0
#define ADS8568_BUSY_PIN		GPIO_mc_5_PIN
#define ADS8568_BUSY_PORT		GPIO_mc_5_PORT
#define ADS8568_BUSY_FUNC		IOCON_FUNC0
#define ADS8568_STBY_PIN		GPIO_mc_6_PIN
#define ADS8568_STBY_PORT		GPIO_mc_6_PORT
#define ADS8568_STBY_FUNC		IOCON_FUNC0
#define ADS8568_RESET_PIN		GPIO_mc_7_PIN
#define ADS8568_RESET_PORT		GPIO_mc_7_PORT
#define ADS8568_RESET_FUNC		IOCON_FUNC0
#define ADS8568_CONVST_PIN		GPIO_mc_8_PIN
#define ADS8568_CONVST_PORT		GPIO_mc_8_PORT
#define ADS8568_CONVST_FUNC		IOCON_FUNC0


extern uint8_t m_finished_flag;

void ADS8568_init(void);
void ADS8568_test(uint32_t freq, uint32_t timeMS);
void DMA_init(void);
void startConv(void);
void TIMER0_init(uint8_t tickMatNum, uint32_t timeMS);
void TIMER1_init(uint8_t tickMatNum, uint32_t freq);


#endif /* LPC_175X_6X_HAL_ADS8568_H_ */
