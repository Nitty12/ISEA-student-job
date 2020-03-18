/*
===============================================================================
 Name        : app_OEIS_DAC.c
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

#include <app_OEIS_DAC.h>



void app_OIS_DAC_init(void){
	DMA_init();
	init_can();
	AD5541A_init();
//	lpc_175x_6x_hal_uart_init(45,60);
}


//State-machine
enum {	status_emergency	=	0,
		status_idle			=	1,
		status_m_start		=	2,
		status_m_next		=	3,
		status_m_wait		=	4,
		status_m_last		=	5,
		status_finished		=	6
};

uint8_t status = status_idle;

uint8_t next_f_flag = 0;
uint8_t new_m_flag = 0;
uint8_t emergency_flag = 0;
uint32_t next_frequency = 1;
uint8_t next_periods = 3;
uint32_t next_sampFrequency = 20000;
float next_amplitude_max = 5.0f;
float next_amplitude_min = 0.0f;

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
    app_OIS_DAC_init();

//
//	uint32_t frequencies[35] = {1, 25, 33, 57, 64, 67, 73, 89, 97, 105, 130, 137, 160, 169, 220, 233, 258, 281, 319, 329, 361, 386, 418, 449, 459, 513, 555, 592, 640, 683, 721, 768, 845, 938, 995};
//	uint8_t act_freq = 0;
//	uint8_t last_freq = 34;
//	uint16_t act_freq_can_id = 0x6;
//	uint8_t periods = 3;
//  uint32_t sampFreq = 20000;
//	uint8_t measurement_mode = 1;
//	float amplitude_max = 5.0f;
//	float amplitude_min = 0.0f;
//
//
//	uint32_t counter = 0;
//
//	while(1){
//		if(emergency_flag == 1){
//			status = status_emergency;
//		}
//
//		switch(status){
//		case status_emergency:
//			if(emergency_flag == 0){
//				zeroVolt();
//			}
//			emergency_flag = 1;
//			break;
//		case status_idle:
//			// if CAN message arrived with measure now start the measurement
//			if(new_m_flag == 1){
//				status = status_m_start;
//				act_freq = 0;
//				new_m_flag = 0;
//			}
//			break;
//		case status_m_start:
//			next_f_flag = 0;
//			if(measurement_mode == 0){
//				send_can_message((char *)(&frequencies[act_freq]), act_freq_can_id, 4);
//				applySineWave(frequencies[act_freq], amplitude_max, amplitude_min, periods, sampFreq);
//			}
//			else if(measurement_mode == 1){
//				char data[8];
//				data [0] = next_frequency & 0xFF;
//				data [1] = (next_frequency >> 8) & 0xFF;
//				uint16_t amp_tmp = (uint16_t)((65534/5.0)*next_amplitude_min);
//				data [2] = amp_tmp & 0xFF;
//				data [3] = (amp_tmp >> 8) & 0xFF;
//				amp_tmp = (uint16_t)((65534/5.0)*next_amplitude_max);
//				data [4] = amp_tmp & 0xFF;
//				data [5] = (amp_tmp >> 8) & 0xFF;
//				data [6] = next_periods & 0xFF;
//				data [7] = (next_periods >> 8) & 0xFF;
//				send_can_message((char *)(&data[0]), act_freq_can_id, 8);
//				applySineWave(next_frequency, next_amplitude_max, next_amplitude_min, next_periods, next_sampFrequency);
////				apply_fixed_voltage(next_amplitude_max);
//				act_freq = 0;
//			}
//
//			if(act_freq == last_freq ){
//				status = status_m_last;
//			}
//			else{
//				status = status_m_wait;
//			}
//
//			break;
//		case status_m_wait:
//			if(next_f_flag == 1){
//				status = status_m_next;
//			}
//			break;
//		case status_m_next:
//			act_freq ++;
//			status = status_m_start;
//			break;
//		case status_m_last:
//			if(next_f_flag == 1){
//				status = status_finished;
//			}
//			break;
//		case status_finished:
//			status = status_idle;
//			break;
//		default:
//			status = status_emergency;
//		}
//
//
//		counter++;
//	}

    applySineWave(7, 2.0, 0.0, 2, 40000);
    applySineWave(45, 2.0, 0.0, 4, 50000);
    applySineWave(80, 2.0, 0.0, 6, 30000);
    applySineWave(190, 2.0, 0.0, 8, 20000);
    applySineWave(250, 2.0, 0.0, 10, 40000);
    applySineWave(300, 2.0, 0.0, 12, 30000);

    while(1){

    }
	return 0;
}


