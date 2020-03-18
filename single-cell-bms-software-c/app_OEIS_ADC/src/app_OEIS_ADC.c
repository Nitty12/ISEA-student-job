/*
===============================================================================
 Name        : app_OEIS_ADC.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/



#if defined (__USE_LPCOPEN)
#if defined(NO_BOARD_LIB)
#include "chip.h"
#else
#include "board.h"
#endif
#endif

#include <cr_section_macros.h>

#include <app_OEIS_ADC.h>

#define FLOAT_FFT 1

void app_OIS_ADC_init(void){
 	DMA_init();
 	init_can();
 	ADS8568_init();
// 	lpc_175x_6x_hal_uart_init(15, 30);
}

//State-machine
enum {	status_emergency	=	0,
		status_idle			=	1,
		status_m_measure	=	2,
		status_m_calculate	=	3,
		status_m_next		=	4,
		status_m_last		=	5,
		status_finished		=	6
};
uint8_t status = status_idle;
uint8_t emergency_flag = 0;

uint8_t m_finished_flag = 0;
uint8_t new_m_flag = 0;
uint32_t next_frequency = 1000;
uint8_t next_periods = 3;
float next_amplitude_max = 5.0;
float next_amplitude_min = 0.0;

#define MAXFREQ				1000
#define MAXTIMEMS			2048
#define OFFSET_BEGIN		10
#define OFFSET_END			10



#if FLOAT_FFT == 0
/* Storage buffer */
int16_t Buffer[MAXFREQ*MAXTIMEMS/1000+OFFSET_BEGIN+OFFSET_END];
__DATA(RAM2) q15_t result[2*MAXFREQ*MAXTIMEMS/1000];
#else
/* Storage buffer */
float32_t Buffer[MAXFREQ*MAXTIMEMS/1000+OFFSET_BEGIN+OFFSET_END +100];
__DATA(RAM2) float32_t result[MAXFREQ*MAXTIMEMS/1000 +100];
#endif


int main(void) {

#if defined (__USE_LPCOPEN)
    // Read clock settings and update SystemCoreClock variable
	SystemCoreClockUpdate();
#if !defined(NO_BOARD_LIB)
    // Set up and initialize all required blocks and
    // functions related to the board hardware
    Board_Init();
#endif
#endif

    app_OIS_ADC_init();


    // Force the counter to be placed into memory
    uint32_t counter = 0;

#if FLOAT_FFT == 0
    // Q15 RFFT
    arm_rfft_instance_q15 S;
    arm_cfft_radix4_instance_q15 SR;
    arm_status init_status = arm_rfft_init_q15(&S, &SR, MAXFREQ*MAXTIMEMS/1000, 0,1);
    if(init_status != ARM_MATH_SUCCESS){
    	status = status_emergency;
    }
#else
    // F32 RFFT
    arm_rfft_instance_f32 S;
    arm_cfft_radix4_instance_f32 SR;
    arm_status init_status = arm_rfft_init_f32(&S, &SR, MAXFREQ*MAXTIMEMS/1000, 0,1);
    if(init_status != ARM_MATH_SUCCESS){
    	status = status_emergency;
    }

//    arm_rfft_fast_instance_f32 S;
//    arm_status init_status = arm_rfft_fast_init_f32(&S, MAXFREQ*MAXTIMEMS/1000);
//    if(init_status != ARM_MATH_SUCCESS){
//    	status = status_emergency;
//    }

#endif


	while(1){
		if(emergency_flag == 1){
			status = status_emergency;
		}

		switch(status){
		case status_emergency:
			if(emergency_flag == 0){
				//fist error
			}
			// always when in error
			emergency_flag = 1;
			break;
		case status_idle:
			if(new_m_flag == 1){
				status = status_m_next;
				new_m_flag = 0;
			}
			break;
		case status_m_measure:
			if(m_finished_flag == 1){
				status = status_m_calculate;
			}
			break;
		case status_m_calculate:
			;
			uint16_t index = 0;

#if FLOAT_FFT == 0
			char send_tmp[8];
			send_can_message((char *)(&counter), 201,4);
			for(index=OFFSET_BEGIN; index<MAXFREQ*MAXTIMEMS/1000+OFFSET_BEGIN; ){
				memcpy((void *)&send_tmp[0], (void *)&Buffer[index++],2);
				memcpy((void *)&send_tmp[2], (void *)&Buffer[index++],2);
				memcpy((void *)&send_tmp[4], (void *)&Buffer[index++],2);
				memcpy((void *)&send_tmp[6], (void *)&Buffer[index++],2);
				send_can_message((char *)(&send_tmp[0]), 0x100,8);
			}
			arm_rfft_q15(&S, (q15_t*)&Buffer[OFFSET_BEGIN], (q15_t*)&result[0]);
//			arm_rfft_f32(&S, (float32_t*)&Buffer[OFFSET_BEGIN], (float32_t*)&result[0]);
			for(index=0; index<MAXFREQ*MAXTIMEMS/1000;){
				memcpy((void *)&send_tmp[0], (void *)&result[index++],2);
				memcpy((void *)&send_tmp[2], (void *)&result[index++],2);
				memcpy((void *)&send_tmp[4], (void *)&result[index++],2);
				memcpy((void *)&send_tmp[6], (void *)&result[index++],2);
				send_can_message((char *)(&send_tmp[0]), 0x101,8);
			}
#else
			char send_tmp[8];
			send_can_message((char *)(&counter), 201,4);
			for(index=OFFSET_BEGIN; index<MAXFREQ*MAXTIMEMS/1000+OFFSET_BEGIN; ){
				memcpy((void *)&send_tmp[0], (void *)&Buffer[index++],4);
				memcpy((void *)&send_tmp[4], (void *)&Buffer[index++],4);
				send_can_message((char *)(&send_tmp[0]), 0x102,8);
				while(Chip_CAN_GetFreeTxBuf(LPC_CAN) != CAN_BUFFER_1);
			}
			arm_rfft_f32(&S, (float32_t*)&Buffer[OFFSET_BEGIN], (float32_t*)&result[0]);
//			arm_rfft_fast_f32(&S, (float32_t*)&Buffer[OFFSET_BEGIN], (float32_t*)&result[0],0);



			for(index=0; index<MAXFREQ*MAXTIMEMS/1000;){
				memcpy((void *)&send_tmp[0], (void *)&result[index++],4);
				memcpy((void *)&send_tmp[4], (void *)&result[index++],4);

				send_can_message((char *)(&send_tmp[0]), 0x103,8);
				while(Chip_CAN_GetFreeTxBuf(LPC_CAN) != CAN_BUFFER_1);
			}


#endif
			status = status_idle;
			break;
		case status_m_next:
			m_finished_flag = 0;
			send_can_message((char *)(&counter), 201,4);
			ADS8568_test(1000, 2048+OFFSET_BEGIN+OFFSET_END);
			status = status_m_measure;
			break;
		case status_m_last:

			break;
		case status_finished:

			break;
		default:
			status = status_emergency;
		}

		counter++;
	}

    return 0 ;
}
