/*
 * lpc_175x_6x_hal_adc.c
 *
 *  Created on: 09.08.2019
 *      Author: abl
 */


#include <lpc_175x_6x_hal_adc.h>



#define _ADC_CHANNLE_VOLTAGE ADC_CH0
#define _ADC_CHANNLE_CURRENT ADC_CH1
#define _LPC_ADC_ID LPC_ADC
#define _LPC_ADC_IRQ ADC_IRQn
#define _GPDMA_CONN_ADC GPDMA_CONN_ADC

static ADC_CLOCK_SETUP_T ADCSetup;
uint32_t _bitRate = ADC_MAX_SAMPLE_RATE;
static volatile uint8_t Burst_Mode_Flag = 1, Interrupt_Continue_Flag;
static volatile uint8_t ADC_Interrupt_Done_Flag, channelTC, dmaChannelNum;
uint32_t DMAbuffer[2];

void ADC_Init() {


	Chip_ADC_Init(_LPC_ADC_ID, &ADCSetup);
	Chip_ADC_EnableChannel(_LPC_ADC_ID, _ADC_CHANNLE_VOLTAGE, ENABLE);
	Chip_ADC_EnableChannel(_LPC_ADC_ID, _ADC_CHANNLE_CURRENT, ENABLE);

	// set/change bitrate
	ADCSetup.burstMode = Burst_Mode_Flag;
	Chip_ADC_SetSampleRate(_LPC_ADC_ID, &ADCSetup, _bitRate);

}

/* Print ADC value and delay */
static void App_print_ADC_value(uint16_t data)
{
	send_can_message((char *) ( &data), 10, 2);

}

/* Print ADC value and delay */
static void App_print_ADC_mc_current(uint16_t data)
{
	send_can_message((char *) ( &data), 10, 2);
}

/* Print ADC value and delay */
static void App_print_ADC_mc_voltage(uint16_t data)
{
	send_can_message((char *) ( &data), 11, 2);
}


/* DMA routine for ADC example */
void App_DMA_Test(void)
{
	uint16_t dataADC;

	/* Initialize GPDMA controller */
	Chip_GPDMA_Init(LPC_GPDMA);
	/* Setting GPDMA interrupt */
	NVIC_DisableIRQ(DMA_IRQn);
	NVIC_SetPriority(DMA_IRQn, ((0x01 << 3) | 0x01));
	NVIC_EnableIRQ(DMA_IRQn);
	/* Setting ADC interrupt, ADC Interrupt must be disable in DMA mode */
	NVIC_DisableIRQ(_LPC_ADC_IRQ);
	Chip_ADC_Int_SetChannelCmd(_LPC_ADC_ID, _ADC_CHANNLE_VOLTAGE, ENABLE);
	Chip_ADC_Int_SetChannelCmd(_LPC_ADC_ID, _ADC_CHANNLE_CURRENT, ENABLE);
	/* Get the free channel for DMA transfer */
	dmaChannelNum = Chip_GPDMA_GetFreeChannel(LPC_GPDMA, _GPDMA_CONN_ADC);
	/* Enable burst mode if any, the AD converter does repeated conversions
	   at the rate selected by the CLKS field in burst mode automatically */
	if (Burst_Mode_Flag) {
		Chip_ADC_SetBurstCmd(_LPC_ADC_ID, ENABLE);
	}
	/* Get  adc value until get 'x' character */
//	while (1) {
		/* Start A/D conversion if not using burst mode */
		if (!Burst_Mode_Flag) {
			Chip_ADC_SetStartMode(_LPC_ADC_ID, ADC_START_NOW, ADC_TRIGGERMODE_RISING);
		}
		channelTC = 0;
		Chip_GPDMA_Transfer(LPC_GPDMA, dmaChannelNum,
						  _GPDMA_CONN_ADC,
						  (uint32_t) &DMAbuffer[0],
						  GPDMA_TRANSFERTYPE_P2M_CONTROLLER_DMA,
						  2);

		/* Waiting for reading ADC value completed */
		while (channelTC == 0) {}

		/* Get the ADC value fron Data register*/
		dataADC = ((((DMAbuffer[0]) ) & 0xFFFF)); //ADC_DR_RESULT(DMAbuffer);  // >> 16
		App_print_ADC_mc_current(dataADC);
		dataADC = ((((DMAbuffer[1]) ) & 0xFFFF));
		App_print_ADC_mc_voltage(dataADC);
//	}
	/* Disable interrupts, release DMA channel */
	Chip_GPDMA_Stop(LPC_GPDMA, dmaChannelNum);
	NVIC_DisableIRQ(DMA_IRQn);
	/* Disable burst mode if any */
	if (Burst_Mode_Flag) {
		Chip_ADC_SetBurstCmd(_LPC_ADC_ID, DISABLE);
	}
}


///**
// * @brief	DMA interrupt handler sub-routine
// * @return	Nothing
// */
//void DMA_IRQHandler(void)
//{
//	if (Chip_GPDMA_Interrupt(LPC_GPDMA, dmaChannelNum) == SUCCESS) {
//		channelTC++;
//	}
//	else {
//		/* Process error here */
//	}
//}
