/*
 * lpc_175x_6x_hal_ADS8568.c
 *
 *  Created on: 09.08.2019
 *      Author: abl
 */


#include <lpc_175x_6x_hal_ADS8568.h>


#define FLOAT_FFT 1

#define LPC_SSP           LPC_SSP0
#define LPC_GPDMA_SSP_TX  GPDMA_CONN_SSP0_Tx
#define LPC_GPDMA_SSP_RX  GPDMA_CONN_SSP0_Rx
#define PI					3.14159265358979f
#define MAXFREQ				3000
#define MAXTIMEMS			3000



#define BUFFER_SIZE                         (0x8) // buffer for 8 channel 16 bit data
#define SSP_DATA_BITS                       (SSP_BITS_16)
#define SSP_DATA_BIT_NUM(databits)          (databits + 1)
#define SSP_DATA_BYTES(databits)            (((databits) > SSP_BITS_8) ? 2 : 1)
#define SSP_LO_BYTE_MSK(databits)           ((SSP_DATA_BYTES(databits) > 1) ? 0xFF : (0xFF >> \
																					  (8 - SSP_DATA_BIT_NUM(databits))))
#define SSP_HI_BYTE_MSK(databits)           ((SSP_DATA_BYTES(databits) > 1) ? (0xFF >> \
																			   (16 - SSP_DATA_BIT_NUM(databits))) : 0)



/* Tx buffer */
uint16_t Tx_Buf[BUFFER_SIZE];

/* Rx buffer */
int16_t Rx_Buf[BUFFER_SIZE];


#if FLOAT_FFT == 0
/* Storage buffer */
extern int16_t Buffer[MAXFREQ*MAXTIMEMS/1000];
#else
extern float32_t Buffer[MAXFREQ*MAXTIMEMS/1000];
#endif


static SSP_ConfigFormat ssp_format;
static volatile uint8_t  isXferCompleted = 0;
static uint8_t dmaChSSPTx, dmaChSSPRx;
static volatile uint8_t isDmaTxfCompleted = 0;
static volatile uint8_t isDmaRxfCompleted = 0;

//index for storage array
static int32_t idx = -1;


STATIC const PINMUX_GRP_T pinmuxing_adc[] = {
	{ADS8568_SCLK_PORT,		ADS8568_SCLK_PIN,		IOCON_MODE_INACT | ADS8568_SCLK_FUNC},
	{ADS8568_SDO_A_PORT,	ADS8568_SDO_A_PIN,		IOCON_MODE_INACT | ADS8568_SDO_A_FUNC},
	{ADS8568_SDO_B_PORT,	ADS8568_SDO_B_PIN,		IOCON_MODE_INACT | ADS8568_SDO_B_FUNC},
	{ADS8568_SDO_C_PORT,	ADS8568_SDO_C_PIN,		IOCON_MODE_INACT | ADS8568_SDO_C_FUNC},
	{ADS8568_SDO_D_PORT,	ADS8568_SDO_D_PIN,		IOCON_MODE_INACT | ADS8568_SDO_D_FUNC},
	{ADS8568_CS_PORT,		ADS8568_CS_PIN,			IOCON_MODE_INACT | ADS8568_CS_FUNC},
	{ADS8568_ASLEEP_PORT,	ADS8568_ASLEEP_PIN,		IOCON_MODE_INACT | ADS8568_ASLEEP_FUNC},
	{ADS8568_BUSY_PORT,		ADS8568_BUSY_PIN,		IOCON_MODE_INACT | ADS8568_BUSY_FUNC},
	{ADS8568_STBY_PORT,		ADS8568_STBY_PIN,		IOCON_MODE_INACT | ADS8568_STBY_FUNC},
	{ADS8568_RESET_PORT,	ADS8568_RESET_PIN,		IOCON_MODE_INACT | ADS8568_RESET_FUNC},
	{ADS8568_CONVST_PORT,	ADS8568_CONVST_PIN,		IOCON_MODE_INACT | ADS8568_CONVST_FUNC},

};

void trigger_meas(void){
	Chip_GPIO_SetPinState(LPC_GPIO, ADS8568_CONVST_PORT, ADS8568_CONVST_PIN, true);
	Chip_GPIO_SetPinState(LPC_GPIO, ADS8568_CONVST_PORT, ADS8568_CONVST_PIN, false);
}

void wait_for_busy(void){
	while(Chip_GPIO_GetPinState(LPC_GPIO, ADS8568_BUSY_PORT, ADS8568_BUSY_PIN));
}

/* Assert SSEL pin */
void Board_SPI_AssertSSEL(void)
{
	Chip_GPIO_WritePortBit(LPC_GPIO, 0, 16, false);
}

/* De-Assert SSEL pin */
void Board_SPI_DeassertSSEL(void)
{
	Chip_GPIO_WritePortBit(LPC_GPIO, 0, 16, true);
}


static void Buffer_Init(void)
{
	uint16_t i;
	uint8_t ch = 0;

	for (i = 0; i < BUFFER_SIZE; i++) {
		Tx_Buf[i] = 0;
		Rx_Buf[i] = ch++;
	}
}


void ADS8568_init(void){
	Chip_IOCON_SetPinMuxing(LPC_IOCON, pinmuxing_adc, sizeof(pinmuxing_adc) / sizeof(PINMUX_GRP_T));
	Chip_GPIO_SetPinDIROutput(LPC_GPIO, ADS8568_CONVST_PORT, ADS8568_CONVST_PIN);
//	Chip_GPIO_SetPinDIROutput(LPC_GPIO, ADS8568_CS_PORT, ADS8568_CS_PIN);
	Chip_GPIO_SetPinDIROutput(LPC_GPIO, ADS8568_ASLEEP_PORT, ADS8568_ASLEEP_PIN);
	Chip_GPIO_SetPinDIROutput(LPC_GPIO, ADS8568_STBY_PORT, ADS8568_STBY_PIN);
	Chip_GPIO_SetPinDIROutput(LPC_GPIO, ADS8568_RESET_PORT, ADS8568_RESET_PIN);

	Chip_GPIO_SetPinDIRInput(LPC_GPIO, ADS8568_BUSY_PORT, ADS8568_BUSY_PIN);
//	Chip_GPIO_SetPinDIRInput(LPC_GPIO, ADS8568_SDO_A_PORT, ADS8568_SDO_A_PIN);
	Chip_GPIO_SetPinDIRInput(LPC_GPIO, ADS8568_SDO_B_PORT, ADS8568_SDO_B_PIN);
	Chip_GPIO_SetPinDIRInput(LPC_GPIO, ADS8568_SDO_C_PORT, ADS8568_SDO_C_PIN);
	Chip_GPIO_SetPinDIRInput(LPC_GPIO, ADS8568_SDO_D_PORT, ADS8568_SDO_D_PIN);

	Chip_GPIO_WritePortBit(LPC_GPIO, ADS8568_CONVST_PORT, ADS8568_CONVST_PIN, false);
	Chip_GPIO_WritePortBit(LPC_GPIO, ADS8568_ASLEEP_PORT, ADS8568_ASLEEP_PIN, false);
	Chip_GPIO_WritePortBit(LPC_GPIO, ADS8568_STBY_PORT, ADS8568_STBY_PIN, true);
	Chip_GPIO_WritePortBit(LPC_GPIO, ADS8568_RESET_PORT, ADS8568_RESET_PIN, false);


//	Chip_GPIO_WritePortBit(LPC_GPIO, ADS8568_CS_PORT, ADS8568_CS_PIN, true);



	Chip_SSP_Init(LPC_SSP);// bitrate = 100000
	Chip_Clock_SetPCLKDiv(SYSCTL_PCLK_SSP0, SYSCTL_CLKDIV_1);//ssp clock = cpu clock/4 = 32MHz
	//Maximum SSP speed is PCLK(ssp clock)/2
	Chip_SSP_SetBitRate(LPC_SSP, 30000000);//increase bit rate to 1000000
	/* SSP initialization */
	ssp_format.frameFormat = SSP_FRAMEFORMAT_SPI;
	ssp_format.bits = SSP_DATA_BITS;
	ssp_format.clockMode = SSP_CLOCK_MODE0;
	Chip_SSP_SetFormat(LPC_SSP, ssp_format.bits, ssp_format.frameFormat, ssp_format.clockMode);

	Buffer_Init();

	Chip_SSP_Enable(LPC_SSP);

	Chip_SSP_SetMaster(LPC_SSP, 1); //Master selection

}

static void appSSPRun(void){
	// Receive data
	isDmaRxfCompleted = 0;
	Chip_GPDMA_Transfer(LPC_GPDMA, dmaChSSPRx,
										LPC_GPDMA_SSP_RX,
										(uint32_t) &Rx_Buf[0],
										GPDMA_TRANSFERTYPE_P2M_CONTROLLER_DMA,
										0x8);
	//Transmit data from ADC
	/* data Tx_Buf --> SSP */
	Chip_GPDMA_Transfer(LPC_GPDMA, dmaChSSPTx,
					(uint32_t) &Tx_Buf[0],
					LPC_GPDMA_SSP_TX,
					GPDMA_TRANSFERTYPE_M2P_CONTROLLER_DMA,
					0x8);
//	while(isDmaRxfCompleted != 1);
//	Chip_GPIO_WritePortBit(LPC_GPIO, ADS8568_CS_PORT, ADS8568_CS_PIN, true);

}


void DMA_init(void){
	/* Initialize GPDMA controller */
	Chip_GPDMA_Init(LPC_GPDMA);

	//Setting GPDMA interrupt
	NVIC_DisableIRQ(DMA_IRQn);
	//priority 2
	NVIC_SetPriority(DMA_IRQn, 0x02);

	NVIC_EnableIRQ(DMA_IRQn);

	dmaChSSPTx = Chip_GPDMA_GetFreeChannel(LPC_GPDMA, LPC_GPDMA_SSP_TX);
	dmaChSSPRx = Chip_GPDMA_GetFreeChannel(LPC_GPDMA, LPC_GPDMA_SSP_RX);

	Chip_SSP_DMA_Enable(LPC_SSP);
}


void DMA_IRQHandler(void)
{
	if (Chip_GPDMA_Interrupt(LPC_GPDMA, dmaChSSPTx) == SUCCESS) {
		isDmaTxfCompleted = 1;
	}

	if (Chip_GPDMA_Interrupt(LPC_GPDMA, dmaChSSPRx) == SUCCESS) {
		isDmaRxfCompleted += 1;
		if(idx>-1){
#if FLOAT_FFT == 0
			Buffer[idx] = Rx_Buf[0];
#else
			Buffer[idx] = Rx_Buf[0];
#endif
		}
		idx ++;
	}
}

void TIMER0_IRQHandler(void)
{
	if (Chip_TIMER_MatchPending(LPC_TIMER0, 1)) {

		Chip_TIMER_ClearMatch(LPC_TIMER0, 1);

		//stop sampling
		Chip_TIMER_Disable(LPC_TIMER1);
		Chip_TIMER_Disable(LPC_TIMER0);
		m_finished_flag = 1;
		Chip_TIMER_ClearMatch(LPC_TIMER0, 1);
		Chip_TIMER_ClearMatch(LPC_TIMER1, 1);
		}
}

void TIMER1_IRQHandler(void)
{
	if (Chip_TIMER_MatchPending(LPC_TIMER1, 1)) {
		Chip_TIMER_ClearMatch(LPC_TIMER1, 1);
		trigger_meas();
		startConv();
	}
}

/*Enable Timer 0 */
void TIMER0_init(uint8_t tickMatNum, uint32_t timeMS)
{
	uint32_t T0freq;
	uint32_t matVal;
	Chip_TIMER_DeInit(LPC_TIMER0);
	/* Enable timer 0 clock */
	Chip_TIMER_Init(LPC_TIMER0);
	/* Timer rate is peripheral clock rate as prescalar clock is the peripheral clock
	 * pclk = cpu clock/4 default
	 * change it to cpu clock = 128MHz*/
	Chip_Clock_SetPCLKDiv(SYSCTL_PCLK_TIMER0, SYSCTL_CLKDIV_1);
	T0freq = Chip_Clock_GetPeripheralClockRate(SYSCTL_PCLK_TIMER0);
	matVal = T0freq/1000 * timeMS;
	/* Timer setup for match and interrupt */
	Chip_TIMER_Reset(LPC_TIMER0);
	Chip_TIMER_MatchEnableInt(LPC_TIMER0, tickMatNum);
	Chip_TIMER_SetMatch(LPC_TIMER0, tickMatNum, matVal);

	//reset timer counter when matched with tickMatNum
	Chip_TIMER_ResetOnMatchEnable(LPC_TIMER0, tickMatNum);
	Chip_TIMER_Enable(LPC_TIMER0);

	/* Enable timer interrupt */
	NVIC_ClearPendingIRQ(TIMER0_IRQn);
	//priority 3
	NVIC_SetPriority(TIMER0_IRQn, 0x05);
	NVIC_EnableIRQ(TIMER0_IRQn);

//	Chip_TIMER_ClearMatch(LPC_TIMER0, 1);

}

/*Enable Timer 1 */
void TIMER1_init(uint8_t tickMatNum, uint32_t freq)
{
	uint32_t timerFreq;
	uint32_t Tickrate = freq;
	Chip_TIMER_DeInit(LPC_TIMER1);
	/* Enable timer 1 clock */
	Chip_TIMER_Init(LPC_TIMER1);
	/* Timer rate is peripheral clock rate as prescalar clock is the peripheral clock
	 * pclk = cpu clock/4 default
	 * change it to cpu clock = 128MHz*/
	Chip_Clock_SetPCLKDiv(SYSCTL_PCLK_TIMER1, SYSCTL_CLKDIV_1);
	timerFreq = Chip_Clock_GetPeripheralClockRate(SYSCTL_PCLK_TIMER1);

	/* Timer setup for match and interrupt */
	Chip_TIMER_Reset(LPC_TIMER1);
	Chip_TIMER_MatchEnableInt(LPC_TIMER1, tickMatNum);
	Chip_TIMER_SetMatch(LPC_TIMER1, tickMatNum, (timerFreq / Tickrate));

	//reset timer counter when matched with tickMatNum
	Chip_TIMER_ResetOnMatchEnable(LPC_TIMER1, tickMatNum);
	Chip_TIMER_Enable(LPC_TIMER1);

	/* Enable timer interrupt */
	NVIC_ClearPendingIRQ(TIMER1_IRQn);
	//priority 1
	NVIC_SetPriority(TIMER1_IRQn, 0x03);
	NVIC_EnableIRQ(TIMER1_IRQn);

//	Chip_TIMER_ClearMatch(LPC_TIMER1, 1);

}

void startConv(){


	//Receive the data
	appSSPRun();
	//send CAN message

	// send every value in a separated can message
//	send_can_message((char *)(&Rx_Buf[0]), 600,2);
//	send_can_message((char *)(&Rx_Buf[1]), 601,2);
//	send_can_message((char *)(&Rx_Buf[2]), 602,2);
//	send_can_message((char *)(&Rx_Buf[3]), 603,2);
//	send_can_message((char *)(&Rx_Buf[4]), 604,2);
//	send_can_message((char *)(&Rx_Buf[5]), 605,2);
//	send_can_message((char *)(&Rx_Buf[6]), 606,2);
//	send_can_message((char *)(&Rx_Buf[7]), 607,2);

	// OR combine all into 2 messages
//	send_can_message((char *)(&Rx_Buf[0]), 600,8);
//	send_can_message((char *)(&Rx_Buf[4]), 601,8);


}

void ADS8568_test(uint32_t freq, uint32_t timeMS){
	idx = 0;
	TIMER0_init(1, timeMS);
	TIMER1_init(1, freq);
//	startConv();
//	for(uint16_t i = 0; i<BUFFER_SIZE; i++){
//		//Rx_Buf[i] = 10+i;
//		send_can_message((char *)(&Rx_Buf[i]), 200+i,2);
//	}
}
