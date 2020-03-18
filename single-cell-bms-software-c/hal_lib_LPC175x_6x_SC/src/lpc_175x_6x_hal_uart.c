/*
 * lpc_175x_6x_hal_uart.c
 *
 *  Created on: 30.12.2019
 *      Author: abl
 */

#include <lpc_175x_6x_hal_uart.h>


/* Transmit and receive ring buffers */
RINGBUFF_T txring, rxring;

/* Transmit and receive buffers */
uint8_t rxbuff[UART_RRB_SIZE], txbuff[UART_SRB_SIZE];

const char uart_start_command[] = "next frequency:\r\n";
const char uart_finish_command[] = "impedance:\r\n";

uint16_t can_receive_id = 60;
uint16_t can_transmit_id = 120;


void lpc_175x_6x_hal_uart_init(uint16_t can_receive, uint16_t can_transmit){
	can_receive_id = can_receive;
	can_transmit_id = can_transmit;
	/* Setup UART for 115.2K8N1 */
	Chip_UART_Init(UART_SELECTION);
	Chip_UART_SetBaud(UART_SELECTION, 115200);
	Chip_UART_ConfigData(UART_SELECTION, (UART_LCR_WLEN8 | UART_LCR_SBS_1BIT | UART_LCR_PARITY_DIS));
	Chip_UART_SetupFIFOS(UART_SELECTION, (UART_FCR_FIFO_EN | UART_FCR_TRG_LEV2));
	Chip_UART_TXEnable(UART_SELECTION);

	/* Before using the ring buffers, initialize them using the ring
		   buffer init function */
	RingBuffer_Init(&rxring, rxbuff, 1, UART_RRB_SIZE);
	RingBuffer_Init(&txring, txbuff, 1, UART_SRB_SIZE);

	/* Reset and enable FIFOs, FIFO trigger level 2 (8 chars) */
	Chip_UART_SetupFIFOS(UART_SELECTION, (UART_FCR_FIFO_EN | UART_FCR_RX_RS |
							UART_FCR_TX_RS | UART_FCR_TRG_LEV2));

	/* Enable receive data and line status interrupt */
	Chip_UART_IntEnable(UART_SELECTION, (UART_IER_RBRINT | UART_IER_RLSINT));

	/* preemption = 1, sub-priority = 1 */
	NVIC_SetPriority(IRQ_SELECTION, 12);
	NVIC_EnableIRQ(IRQ_SELECTION);


}

void uart_send(void *data,uint16_t size){
	Chip_UART_SendRB(UART_SELECTION, &txring, data, size);
//	send_can_message((char *)data, can_transmit_id, size);
}


/**
 * @brief	UART 0 interrupt handler using ring buffers
 * @return	Nothing
 */

#define BUFSIZE 100
uint32_t UART3Status = 0;
uint32_t UART1Buffer[BUFSIZE] = {0};
uint32_t UART1Count = 0;
uint32_t UART1TxEmpty = 1;

void HANDLER_NAME(void){
//	Chip_UART_IRQRBHandler(UART_SELECTION, &rxring, &txring);


	uint8_t IIRValue, LSRValue;


	IIRValue = UART_SELECTION->IIR;
	IIRValue &= UART_IIR_INTID_MASK;
	if ( IIRValue == UART_IIR_INTID_RLS ){       /* Receive Line Status */
		LSRValue = UART_SELECTION->LSR;
	    /* Receive Line Status */
	    if ( LSRValue & (UART_LSR_OE|UART_LSR_PE|UART_LSR_FE|UART_LSR_RXFE|UART_LSR_BI) ){
	      /* There are errors or break interrupt */
	      /* Read LSR will clear the interrupt */
	      UART3Status = LSRValue;
	      uint8_t Dummy = 0;
	      Dummy = UART_SELECTION->RBR;        /* Dummy read on RX to clear
	                                interrupt, then bail out */
	      return;
	    }
		if ( LSRValue & UART_LSR_RDR ){    /* Receive Data Ready */
		  /* If no error on RLS, normal ready, save into the data buffer. */
		  /* Note: read RBR will clear the interrupt */
			/* Use default ring buffer handler. Override this with your own
			   code if you need more capability. */
			Chip_UART_IRQRBHandler(UART_SELECTION, &rxring, &txring);
			uint8_t local_buffer[8] = {0};
			uint8_t bytes = Chip_UART_ReadRB(UART_SELECTION, &rxring, &local_buffer, 8);
			while(bytes){
//				send_can_message((char *)local_buffer, can_receive_id, bytes);
				bytes = Chip_UART_ReadRB(UART_SELECTION, &rxring, &local_buffer, bytes);
			}
		}
	}
	else if ( IIRValue == UART_IIR_INTID_RDA )    /* Receive Data Available */
	{
		/* Use default ring buffer handler. Override this with your own
		   code if you need more capability. */
		uint8_t *ptr = (&rxring)->data;


		ptr += ((&rxring)->head & ((&rxring)->count - 1)) * (&rxring)->itemSz;
		send_can_message((char *)ptr, 555, 4);
		Chip_UART_IRQRBHandler(UART_SELECTION, &rxring, &txring);
		uint8_t local_buffer[8] = {0};
		uint8_t bytes = Chip_UART_ReadRB(UART_SELECTION, &rxring, &local_buffer, 8);
		while(bytes){
//			send_can_message((char *)local_buffer, can_receive_id, bytes);
			bytes = Chip_UART_ReadRB(UART_SELECTION, &rxring, &local_buffer, bytes);
		}
	}
	else if ( IIRValue == UART_IIR_INTID_CTI )    /* Character timeout indicator */
	{
		//change to normal interrupt behaviour!!!
		/* Character Time-out indicator */
		UART3Status |= 0x100;        /* Bit 9 as the CTI error */

	}
	else if ( IIRValue == UART_IIR_INTID_THRE )    /* THRE, transmit holding register empty */
	{
		/* THRE interrupt */
		LSRValue = UART_SELECTION->LSR;        /* Check status in the LSR to see if
								valid data in U0THR or not */
		if ( LSRValue & UART_LSR_THRE )
		{
			UART1TxEmpty = 1;
			Chip_UART_IRQRBHandler(UART_SELECTION, &rxring, &txring);
		}
		else
		{
			UART1TxEmpty = 0;
		}
	}
	else if(IIRValue == UART_IIR_INTID_MODEM){
		if (UART_SELECTION->IER & UART_IIR_INTID_MODEM) {
			Chip_UART_TXIntHandlerRB(UART_SELECTION, &txring);

			/* Disable transmit interrupt if the ring buffer is empty */
			if (RingBuffer_IsEmpty(&txring)) {
				Chip_UART_IntDisable(UART_SELECTION, UART_IER_THREINT);
			}
		}
	}
}
