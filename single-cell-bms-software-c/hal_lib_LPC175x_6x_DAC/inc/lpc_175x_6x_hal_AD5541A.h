/*
 * lpc_175x_6x_hal_AD5541A.h
 *
 *  Created on: 23-Sep-2019
 *      Author: Nitty
 */

#ifndef LPC_175X_6X_HAL_AD5541A_H_
#define LPC_175X_6X_HAL_AD5541A_H_

#include "board.h"


extern uint8_t emergency_flag;

  //p0.15 - SCK to DAC SCLK
  //p0.16 - SSEL to DAC CS'
  //p0.18 - MOSI to DAC DIN
  //p1.19 - GPIO 11 to DAC LDAC

#define AD5541A_SCLK_PIN		SPI_mc_SCK_PIN
#define AD5541A_SCLK_PORT		SPI_mc_SCK_PORT
#define AD5541A_SCLK_FUNC		IOCON_FUNC2 //SSP0

#define AD5541A_CS_PIN			SPI_mc_SSEL_PIN
#define AD5541A_CS_PORT			SPI_mc_SSEL_PORT
#define AD5541A_CS_FUNC			IOCON_FUNC2 //SSP0

#define AD5541A_DIN_PIN			SPI_mc_MOSI_PIN
#define AD5541A_DIN_PORT		SPI_mc_MOSI_PORT
#define AD5541A_DIN_FUNC		IOCON_FUNC2 //SSP0

#define AD5541A_LDAC_PIN		GPIO_mc_11_PIN
#define AD5541A_LDAC_PORT		GPIO_mc_11_PORT
#define AD5541A_LDAC_FUNC		IOCON_FUNC0

/*!< Sinewave queue Structure         */
typedef struct  sinwaveQueue{
	uint32_t frequency;
	float ampMaximum;
	float ampMinimum;
	uint16_t totalPeriod;
	uint32_t sampFreq;
};

void DMA_init(void);
void AD5541A_init(void);
void AD5541A_deInit(void);
void TIMER0_init(uint32_t samplingFreq);
void sineQueueStore(uint16_t i, uint32_t freq, float ampMax, float ampMin, uint16_t period, uint32_t samplingFreq);
void sineQueueClear(uint16_t i);
void applySineWave(uint32_t freq, float ampMax, float ampMin, uint16_t period, uint32_t samplingFreq);
void createSinWave();
void createSineTable(float ampMax, float ampMin, float freq);
void zeroVolt(void);
void apply_fixed_voltage(float amplitude);

#endif /* LPC_175X_6X_HAL_AD5541A_H_ */
