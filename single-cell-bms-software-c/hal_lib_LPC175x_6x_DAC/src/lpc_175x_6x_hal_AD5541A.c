/*
 * lpc_175x_6x_hal_AD5541A.c
 *
 *  Created on: 23-Sep-2019
 *      Author: Nitty
 */


/*	Clock frequencies:
 	External main osc 16MHz,
	Fcco(main pllclk) = 512Mhz(2*16*16Mhz/1)
	CPU clock(cclk) = 128Mhz (512Mhz/4)       */

#include <lpc_175x_6x_hal_AD5541A.h>

#define LPC_SSP           LPC_SSP0
#define LPC_GPDMA_SSP_TX  GPDMA_CONN_SSP0_Tx
#define LPC_GPDMA_SSP_RX  GPDMA_CONN_SSP0_Rx
#define PI					3.14159265358979f
/* The maximum number of samples of the sine wave signal of 1 Hz
 * Eg. if the frequency is 250 Hz, there will be 64 (16000/250) samples per cycle*/
#define SAMPLESNUM			16000

static const uint32_t emergency_zero = 0;

/* To determine if the SPI communication will be via DMA or not
 * Max. sampling frequency of timer with DMA is found to be 70kHz
 * and without DMA as 60kHz*/
#define DAC_DMA 							0

#define BUFFER_SIZE                         (0x1) // transmission buffer size for 16 bit data
#define SSP_DATA_BITS                       (SSP_BITS_16)
#define SSP_DATA_BIT_NUM(databits)          (databits + 1)
#define SSP_DATA_BYTES(databits)            (((databits) > SSP_BITS_8) ? 2 : 1)
#define SSP_LO_BYTE_MSK(databits)           ((SSP_DATA_BYTES(databits) > 1) ? 0xFF : (0xFF >> \
																					  (8 - SSP_DATA_BIT_NUM(databits))))
#define SSP_HI_BYTE_MSK(databits)           ((SSP_DATA_BYTES(databits) > 1) ? (0xFF >> \
																			   (16 - SSP_DATA_BIT_NUM(databits))) : 0)
/* if an error happens, set errorStatus to true for outputting zero volts*/
static bool errorStatus = false;
/* for knowing if a sine wave is currently being output*/
static bool sinewaveStatus = false;
/* to know if a sine wave of given periods is done outputting*/
static bool sinFinished = true;

/* variable to store total ticks of timer needed for a sine wave of given periods*/
static uint32_t inputPeriodTicks = 0;
/* variable to store total number of periods needed for sine wave*/
static uint16_t inputPeriod = 0;
/* variable to store frequency of current wave*/
static uint16_t inputFreq = 0;

/* Array to store the calculated sine signal digital values to be sent to the DAC */
static uint16_t SineTable[SAMPLESNUM];

/* Array to store sine wave details received (if multiple request is obtained)*/
static struct  sinwaveQueue sinQueueArray[10];
/* variable to store index of the currently stored sine wave
 * initialized with value 99 to know the starting.*/
static int16_t sinQStoreIndex = 99;
/* variable to store index of the sine wave currently being output
 * initialized with value 99 to know the starting.*/
static int16_t sinQCurrentIndex = 99;


/* Transmission buffer */
static uint16_t Tx_Buf[BUFFER_SIZE];

/* Receive buffer */
static uint16_t Rx_Buf[BUFFER_SIZE];

static SSP_ConfigFormat ssp_format;
static Chip_SSP_DATA_SETUP_T xf_setup;
/* To know whether the transfer via normal SPI communication is success */
static volatile uint8_t  isXferCompleted = 0;
/* To store the DMA transfer and receive channel numbers */
static uint8_t dmaChSSPTx, dmaChSSPRx;
/* To know whether the transfer via DMA is success */
static volatile uint8_t isDmaTxfCompleted = 0;
static volatile uint8_t isDmaRxfCompleted = 0;

STATIC const PINMUX_GRP_T pinmuxing_dac[] = {
	{AD5541A_SCLK_PORT,		AD5541A_SCLK_PIN,		IOCON_MODE_INACT | AD5541A_SCLK_FUNC},
	{AD5541A_CS_PORT,		AD5541A_CS_PIN,			IOCON_MODE_INACT | AD5541A_CS_FUNC},
	{AD5541A_DIN_PORT,		AD5541A_DIN_PIN,		IOCON_MODE_INACT | AD5541A_DIN_FUNC},
	{AD5541A_LDAC_PORT,		AD5541A_LDAC_PIN,		IOCON_MODE_INACT | AD5541A_LDAC_FUNC},

};


/* Initialize buffer */
static void Buffer_Init(void)
{
	uint16_t i;
	uint8_t ch = 0;

	for (i = 0; i < BUFFER_SIZE; i++) {
		Tx_Buf[i] = ch++;
		Rx_Buf[i] = 0xAA;
	}
}

/* Verify buffer after transfer */
static uint8_t Buffer_Verify(void)
{
	uint16_t i;
	uint8_t *src_addr = (uint8_t *) &Tx_Buf[0];
	uint8_t *dest_addr = (uint8_t *) &Rx_Buf[0];

	for ( i = 0; i < BUFFER_SIZE; i++ ) {

		if (((*src_addr) & SSP_LO_BYTE_MSK(ssp_format.bits)) !=
			((*dest_addr) & SSP_LO_BYTE_MSK(ssp_format.bits))) {
			return 1;
		}
		src_addr++;
		dest_addr++;

		if (SSP_DATA_BYTES(ssp_format.bits) == 2) {
			if (((*src_addr) & SSP_HI_BYTE_MSK(ssp_format.bits)) !=
				((*dest_addr) & SSP_HI_BYTE_MSK(ssp_format.bits))) {
				return 1;
			}
			src_addr++;
			dest_addr++;
			i++;
		}
	}
	return 0;
}

/* Transfers the content of buffers to the DAC */
static void appSSPRun(void){

	/*Chip select' pin set to low for selecting DAC as slave
	 * LDAC' pin must be high while the data is transfered to DAC */
	Chip_GPIO_WritePortBit(LPC_GPIO, AD5541A_LDAC_PORT, AD5541A_LDAC_PIN, true);
	Chip_GPIO_WritePortBit(LPC_GPIO, AD5541A_CS_PORT, AD5541A_CS_PIN, false);

#if DAC_DMA
//DMA transfer
	/* in case the emergency flag is set, send 0 to the DAC*/
	if(emergency_flag == 1){
		/*write data from buffer to the data register of SSP*/
		isDmaTxfCompleted = isDmaRxfCompleted = 0;

		Chip_SSP_DMA_Enable(LPC_SSP);
		/* data Tx_Buf --> SSP */
		Chip_GPDMA_Transfer(LPC_GPDMA,
						dmaChSSPTx,
						&emergency_zero,
						LPC_GPDMA_SSP_TX,
						GPDMA_TRANSFERTYPE_M2P_CONTROLLER_DMA,
						BUFFER_SIZE);
		/* data SSP --> Rx_Buf */
		Chip_GPDMA_Transfer(LPC_GPDMA,
						dmaChSSPRx,
						LPC_GPDMA_SSP_RX,
						(uint32_t) &Rx_Buf[0],
						GPDMA_TRANSFERTYPE_P2M_CONTROLLER_DMA,
						BUFFER_SIZE);
	}
	else{
		/*write data from buffer to the data register of SSP*/
		isDmaTxfCompleted = isDmaRxfCompleted = 0;
		Chip_SSP_DMA_Enable(LPC_SSP);
		/* data Tx_Buf --> SSP */
		Chip_GPDMA_Transfer(LPC_GPDMA,
						dmaChSSPTx,
						(uint32_t) &Tx_Buf[0],
						LPC_GPDMA_SSP_TX,
						GPDMA_TRANSFERTYPE_M2P_CONTROLLER_DMA,
						BUFFER_SIZE);
		/* data SSP --> Rx_Buf */
		Chip_GPDMA_Transfer(LPC_GPDMA,
						dmaChSSPRx,
						LPC_GPDMA_SSP_RX,
						(uint32_t) &Rx_Buf[0],
						GPDMA_TRANSFERTYPE_P2M_CONTROLLER_DMA,
						BUFFER_SIZE);
	}

#else
/* normal SPI communication to DAC */
	xf_setup.length = BUFFER_SIZE;
	xf_setup.tx_data = Tx_Buf;
	xf_setup.rx_data = Rx_Buf;
	xf_setup.rx_cnt = xf_setup.tx_cnt = 0;

	Chip_SSP_RWFrames_Blocking(LPC_SSP, &xf_setup);

	if (Buffer_Verify() == 0) {
		isXferCompleted = 1;
	}
	else {
		isXferCompleted = 0;
	}
#endif

	/*LDAC' is set to low to write data from serial input register to DAC register when CS is high*/
	Chip_GPIO_WritePortBit(LPC_GPIO, AD5541A_LDAC_PORT, AD5541A_LDAC_PIN, false);
	Chip_GPIO_WritePortBit(LPC_GPIO, AD5541A_CS_PORT, AD5541A_CS_PIN, true);
}

void apply_fixed_voltage(float amplitude){
	/*Chip select' pin set to low for selecting DAC as slave
	 * LDAC' pin must be high while the data is transfered to DAC */
	Chip_GPIO_WritePortBit(LPC_GPIO, AD5541A_LDAC_PORT, AD5541A_LDAC_PIN, true);
	Chip_GPIO_WritePortBit(LPC_GPIO, AD5541A_CS_PORT, AD5541A_CS_PIN, false);

	isDmaTxfCompleted = isDmaRxfCompleted = 0;
	float voltage_float = (65534/5.0)*amplitude;
	uint16_t voltage = (uint16_t) voltage_float;

	Chip_SSP_DMA_Enable(LPC_SSP);
	/* data Tx_Buf --> SSP */
	Chip_GPDMA_Transfer(LPC_GPDMA,
					dmaChSSPTx,
					(uint32_t) &voltage,
					LPC_GPDMA_SSP_TX,
					GPDMA_TRANSFERTYPE_M2P_CONTROLLER_DMA,
					BUFFER_SIZE);
	/* data SSP --> Rx_Buf */
	Chip_GPDMA_Transfer(LPC_GPDMA,
					dmaChSSPRx,
					LPC_GPDMA_SSP_RX,
					(uint32_t) &Rx_Buf[0],
					GPDMA_TRANSFERTYPE_P2M_CONTROLLER_DMA,
					BUFFER_SIZE);

	/*LDAC' is set to low to write data from serial input register to DAC register when CS is high*/
	Chip_GPIO_WritePortBit(LPC_GPIO, AD5541A_LDAC_PORT, AD5541A_LDAC_PIN, false);
	Chip_GPIO_WritePortBit(LPC_GPIO, AD5541A_CS_PORT, AD5541A_CS_PIN, true);
}

/*initialization of the DAC*/
void AD5541A_init(void){
	Chip_IOCON_SetPinMuxing(LPC_IOCON, pinmuxing_dac, sizeof(pinmuxing_dac) / sizeof(PINMUX_GRP_T));
	/*Set LDAC pin as output pin*/
	Chip_GPIO_SetPinDIROutput(LPC_GPIO, AD5541A_LDAC_PORT, AD5541A_LDAC_PIN);
	/*Set CS' pin high so that it is not currently selected as slave*/
	Chip_GPIO_WritePortBit(LPC_GPIO, AD5541A_CS_PORT, AD5541A_CS_PIN, true);
	/* Initialize the SSP port
	 * default bit rate selected is 100000*/
	Chip_SSP_Init(LPC_SSP);
	/*Set ssp clock = cpu clock = 128MHz*/
	Chip_Clock_SetPCLKDiv(SYSCTL_PCLK_SSP0, SYSCTL_CLKDIV_1);
	/* Maximum SSP speed is 64MHz
	 * increase default bit rate to 3MHz*/
	Chip_SSP_SetBitRate(LPC_SSP, 3000000);
	/* Set SSP to SPI communication*/
	ssp_format.frameFormat = SSP_FRAMEFORMAT_SPI;
	ssp_format.bits = SSP_DATA_BITS;
	ssp_format.clockMode = SSP_CLOCK_MODE0;
	Chip_SSP_SetFormat(LPC_SSP, ssp_format.bits, ssp_format.frameFormat, ssp_format.clockMode);

	Buffer_Init();

	Chip_SSP_Enable(LPC_SSP);
	/*Set LPC_SSP port as master*/
	Chip_SSP_SetMaster(LPC_SSP, 1);

	/*initialize sin queue to zeros*/
	for(uint16_t i =0; i<sizeof(sinQueueArray)/sizeof(sinQueueArray[0]); i++){
		sineQueueClear(i);
	}

	/*initialize sin table to zeros*/
	for(uint16_t i =0; i< SAMPLESNUM; i++){
		SineTable[i] = 0;
	}
}

/* DeInitialize SSP peripheral */
void AD5541A_deInit(void){
	Chip_SSP_DeInit(LPC_SSP);
}

/* DMA interrupt handler */
void DMA_IRQHandler(void)
{
	if (Chip_GPDMA_Interrupt(LPC_GPDMA, dmaChSSPTx) == SUCCESS) {
		isDmaTxfCompleted = 1;
	}

	if (Chip_GPDMA_Interrupt(LPC_GPDMA, dmaChSSPRx) == SUCCESS) {
		isDmaRxfCompleted = 1;
	}
}

/*Initialize GPDMA controller*/
void DMA_init(void){
	Chip_GPDMA_Init(LPC_GPDMA);

	/* Setting GPDMA interrupt with priority 2 */
	NVIC_DisableIRQ(DMA_IRQn);
	NVIC_SetPriority(DMA_IRQn, 0x02);
	NVIC_EnableIRQ(DMA_IRQn);

	/* Getting free channels for DMA */
	dmaChSSPTx = Chip_GPDMA_GetFreeChannel(LPC_GPDMA, LPC_GPDMA_SSP_TX);
	dmaChSSPRx = Chip_GPDMA_GetFreeChannel(LPC_GPDMA, LPC_GPDMA_SSP_RX);

}

/* Timer0 interrupt handler */
void TIMER0_IRQHandler(void)
{
	/* The sin table contains digital values for 1 single period of the given frequency.
	 * After 1 period is done, the index is reset so that again the same wave is output.
	 * After the given periods is done outputting, checks for pending sin wave requests.
	 * If there is any request pending, asks to recalculate the sin table and start outputting,
	 * else sets the sin wave status to false so that 0 volts is output. */

	if (Chip_TIMER_MatchPending(LPC_TIMER0, 1)) {
		/* Clears the pending match interrupt */
		Chip_TIMER_ClearMatch(LPC_TIMER0, 1);

		if (sinewaveStatus){
			/* variable to iterate through the sin Table */
			static uint16_t index = 0;
			/* variable to count the current total ticks */
			static uint32_t totalTicks = 0;

			/* after given periods is done, total ticks = inputPeriodTicks*/
			if(totalTicks == inputPeriodTicks){

				/* to check if there are still more waves to be output from the queue */
				if(sinQCurrentIndex < sinQStoreIndex){
					sinFinished = true;
					/* Reset tick counts and index */
					totalTicks = 0;
					inputPeriodTicks = 0;
					index = 0;
					/* Create sine wave for the next request */
					sinQCurrentIndex++;
					createSinWave();
				}

				/* if there are no more sin waves to be output - output zero volts */
				else{
					sinFinished = true;
					/* Reset sin queue index */
					sinQStoreIndex = 99;
					sinQCurrentIndex = 99;
					/* Reset tick counts and index */
					totalTicks = 0;
					inputPeriodTicks = 0;
					index = 0;
					/* Reset global period and frequency variables */
					inputPeriod = 0;
					inputFreq = 0;
					sinewaveStatus = false;
				}
			}
			/* Reset the index after a period is done */
			if(totalTicks % (SAMPLESNUM/inputFreq) == 0){
				index = 0;
			}

			/* Store the current digital value in buffer and transfer to the DAC */
			Tx_Buf[0] = SineTable[index];
			appSSPRun();
			index++;
			totalTicks++;
		}

		/* Output 0 volts in case no pending sine wave request */
		else{
			Tx_Buf[0] = 0;
			appSSPRun();
		}

		}

}


/* Initialize Timer 0 with a given sampling frequency */
void TIMER0_init(uint32_t samplingFreq)
{
	/* when the timer counter matches the count provided in match register, tickMatNum
	 * an interrupt is generated */
	uint8_t tickMatNum = 1;
	/* Variable to store the timer frequency */
	uint32_t timerFreq;
	/* Variable to store the number of samples per second needed*/
	uint32_t Tickrate = samplingFreq;

	if (inputFreq!=0){
		/* Number of ticks needed for the specified number of full periods.
		 * There will be (SAMPLESNUM/inputFreq) number of digital values
		 * for the current wave for 1 full period*/
		inputPeriodTicks = inputPeriod*(SAMPLESNUM/inputFreq);
	}
	/* Enable timer 0 clock */
	Chip_TIMER_Init(LPC_TIMER0);

	/* Timer rate is peripheral clock rate as prescalar clock is the peripheral clock
	 * pclk = cpu clock/4 default
	 * change it to cpu clock = 128MHz*/
	Chip_Clock_SetPCLKDiv(SYSCTL_PCLK_TIMER0, SYSCTL_CLKDIV_1);
	timerFreq = Chip_Clock_GetPeripheralClockRate(SYSCTL_PCLK_TIMER0);

	/* Timer setup for match and interrupt */
	Chip_TIMER_Reset(LPC_TIMER0);

	Chip_TIMER_MatchEnableInt(LPC_TIMER0, tickMatNum);
	/* setting the count in match register for the required sampling rate
	 * eg. if timer frequency is 128MHz and required sampling rate is 32kHz,
	 *     then we store 4000(128MHz/32kHz) as count in the match register.
	 *     When the timer counter counts from 0 and reaches 4000 an interrupt is generated */
	Chip_TIMER_SetMatch(LPC_TIMER0, tickMatNum, (timerFreq / Tickrate));

	/* Reset timer counter when matched with counts in tickMatNum*/
	Chip_TIMER_ResetOnMatchEnable(LPC_TIMER0, tickMatNum);

	Chip_TIMER_Enable(LPC_TIMER0);

	/* Enable timer interrupt with priority 1*/
	NVIC_ClearPendingIRQ(TIMER0_IRQn);
	NVIC_SetPriority(TIMER0_IRQn, 0x01);
	NVIC_EnableIRQ(TIMER0_IRQn);

}

/* Outputs a sine wave with given frequency, minimum and maximum peak values for a given number of periods */
void applySineWave(uint32_t freq, float ampMax, float ampMin, uint16_t period, uint32_t samplingFreq){
	if(errorStatus){
		zeroVolt();
	}
	else{
		sinewaveStatus = true;
		/* check if its the first wave needed ('sinFinished' will be true in this case)*/
		if (sinQStoreIndex == 99){
			/* store details in a queue */
			sinQStoreIndex = 0;
			sineQueueStore(sinQStoreIndex, freq, ampMax, ampMin, period, samplingFreq);

		}
		/* If there are no pending waves, create the sin table for the requested wave and output*/
		if(sinFinished){
			sinQCurrentIndex = 0;
			createSinWave();
		}
		/* If there are pending waves, store the details of required waves in queue*/
		else{
			sinQStoreIndex++;
			sineQueueStore(sinQStoreIndex, freq, ampMax, ampMin, period, samplingFreq);
		}

	}
}

/* Create a sine look up table with amplitude minimum 'ampMin', maximum 'ampMax' and frequency 'freq'.
 * There will be SAMPLESNUM number of samples per cycle for 1 Hz wave,
 * and (SAMPLESNUM/freq) number of samples per cycle for waves with higher frequency.
 * Only digital values for 1 cycle is created . Rest will be zeros as initialized (in case of higher frequencies)*/
void createSineTable(float ampMax, float ampMin, float freq){
	/*converting amplitudes to 16 bit equivalent values*/
	float digAmpMax = (65534/5.0)*ampMax;
	float digAmpMin = (65534/5.0)*ampMin;
	for(uint16_t i =0; i<SAMPLESNUM/freq; i++){
		SineTable[i] = (uint16_t)(digAmpMin + (digAmpMax - digAmpMin)*0.5*(1 + arm_sin_f32(2*PI*(freq*i)/SAMPLESNUM)));
	}
}

void createSinWave(){
	createSineTable(sinQueueArray[sinQCurrentIndex].ampMaximum, sinQueueArray[sinQCurrentIndex].ampMinimum, sinQueueArray[sinQCurrentIndex].frequency);
	/* Enable Timer 0 used to output sine waves */
	Chip_TIMER_Init(LPC_TIMER0);
	/* Save the current required periods and frequency to the global variables */
	inputPeriod = sinQueueArray[sinQCurrentIndex].totalPeriod;
	inputFreq = sinQueueArray[sinQCurrentIndex].frequency;
	/* Initialize timer0 with requested sampling frequency */
	TIMER0_init(sinQueueArray[sinQCurrentIndex].sampFreq);
	/* To show that a sin wave is currently being output */
	sinFinished = false;
	/* Clear the details of the sin wave currently being output from the queue*/
	sineQueueClear(sinQCurrentIndex);
}

void sineQueueStore(uint16_t i, uint32_t freq, float ampMax, float ampMin, uint16_t period, uint32_t samplingFreq){
	sinQueueArray[i].frequency = freq;
	sinQueueArray[i].ampMaximum = ampMax;
	sinQueueArray[i].ampMinimum = ampMin;
	sinQueueArray[i].totalPeriod = period;
	sinQueueArray[i].sampFreq = samplingFreq;
}

void sineQueueClear(uint16_t i){
	sinQueueArray[i].frequency = 0;
	sinQueueArray[i].ampMaximum = 0.0;
	sinQueueArray[i].ampMinimum = 0.0;
	sinQueueArray[i].totalPeriod = 0;
	sinQueueArray[i].sampFreq = 0;
}

/* In case 'errorStatus' is true, outputs 0 volts with a sampling frequency of 40kHz */
void zeroVolt(){
	Chip_TIMER_Init(LPC_TIMER0);
	sinewaveStatus = false;
	TIMER0_init(40000);
}
