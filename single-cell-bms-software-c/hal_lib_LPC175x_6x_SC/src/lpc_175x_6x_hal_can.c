/*
 * lpc_175x_6x_hal_can.c
 *
 *  Created on: 09.08.2019
 *      Author: abl
 */

#include <lpc_175x_6x_hal_can.h>

/**
 * CAN buffer for transmitting.
 */
CAN_BUFFER_ID_T   TxBuf;
/**
 * CAN buffer for transmitting.
 */
CAN_MSG_T SendMsgBuf;





#if AF_LUT_USED
#if FULL_CAN_AF_USED
CAN_STD_ID_ENTRY_T FullCANSection[] = {
	{CAN_CTRL_NO, 0, 0x000},//STOP			Stop all functions and especially set the relays idle.
	{CAN_CTRL_NO, 0, 0x001},//MStatus		Contains the status of the multiplexer
	{CAN_CTRL_NO, 0, 0x002},//ReqCl1		Contains a request from client 1
	{CAN_CTRL_NO, 0, 0x003},//ReqCl2		Contains a request from client 2
	{CAN_CTRL_NO, 0, 0x004},//ReqCl3		Contains a request from client 3
	{CAN_CTRL_NO, 0, 0x005},//ReqCl4		Contains a request from client 4
};
#endif
CAN_STD_ID_ENTRY_T SFFSection[] = {
	{CAN_CTRL_NO, 0, 0x000},//STOP			Stop all functions and especially set the relays idle.
	{CAN_CTRL_NO, 0, 0x001},//MStatus		Contains the status of the multiplexer
	{CAN_CTRL_NO, 0, 0x002},//ReqCl1		Contains a request from client 1
	{CAN_CTRL_NO, 0, 0x003},//ReqCl2		Contains a request from client 2
	{CAN_CTRL_NO, 0, 0x004},//ReqCl3		Contains a request from client 3
	{CAN_CTRL_NO, 0, 0x005},//ReqCl4		Contains a request from client 4
};
CAN_STD_ID_RANGE_ENTRY_T SffGrpSection[] = {
};
CAN_EXT_ID_ENTRY_T EFFSection[] = {
	{CAN_CTRL_NO, 0x000},//STOP			Stop all functions and especially set the relays idle.
	{CAN_CTRL_NO, 0x001},//MStatus		Contains the status of the multiplexer
	{CAN_CTRL_NO, 0x002},//ReqCl1		Contains a request from client 1
	{CAN_CTRL_NO, 0x003},//ReqCl2		Contains a request from client 2
	{CAN_CTRL_NO, 0x004},//ReqCl3		Contains a request from client 3
	{CAN_CTRL_NO, 0x005},//ReqCl4		Contains a request from client 4
};
CAN_EXT_ID_RANGE_ENTRY_T EffGrpSection[] = {
};
CANAF_LUT_T AFSections = {
#if FULL_CAN_AF_USED
	FullCANSection, sizeof(FullCANSection) / sizeof(CAN_STD_ID_ENTRY_T),
#else
	NULL, 0,
#endif
	SFFSection, sizeof(SFFSection) / sizeof(CAN_STD_ID_ENTRY_T),
	SffGrpSection, sizeof(SffGrpSection) / sizeof(CAN_STD_ID_RANGE_ENTRY_T),
	EFFSection, sizeof(EFFSection) / sizeof(CAN_EXT_ID_ENTRY_T),
	EffGrpSection, sizeof(EffGrpSection) / sizeof(CAN_EXT_ID_RANGE_ENTRY_T),
};
#endif /*AF_LUT_USED*/



/**
 * Initialize the whole CAN communication.
 */
void init_can(void){
	/*
	 * Set the Pins of the Ports.
	 */
	Chip_GPIO_WriteDirBit(LPC_GPIO, CAN_SELECT_PORT, CAN_SELECT_PIN, true);
	Chip_GPIO_WritePortBit(LPC_GPIO, CAN_SELECT_PORT, CAN_SELECT_PIN, false);
#if CAN_USED == CAN1
	Chip_IOCON_PinMuxSet(LPC_IOCON,CAN_RD1_PORT,CAN_RD1_PIN,IOCON_MODE_INACT | IOCON_FUNC1);
	Chip_IOCON_PinMuxSet(LPC_IOCON,CAN_TD1_PORT,CAN_TD1_PIN,IOCON_MODE_INACT | IOCON_FUNC1);
#else
	Chip_IOCON_PinMuxSet(LPC_IOCON,CAN_RD2_PORT,CAN_RD2_PIN,IOCON_MODE_INACT | IOCON_FUNC2);
	Chip_IOCON_PinMuxSet(LPC_IOCON,CAN_TD2_PORT,CAN_TD2_PIN,IOCON_MODE_INACT | IOCON_FUNC2);
#endif

	/*
	 * Setup the filter, ram, speed and masks.
	 */
	Chip_CAN_Init(LPC_CAN, LPC_CANAF, LPC_CANAF_RAM);
	Chip_CAN_SetBitRate(LPC_CAN, 500000);
	Chip_CAN_EnableInt(LPC_CAN, CAN_IER_BITMASK);

#if AF_LUT_USED
	Chip_CAN_SetAFLUT(LPC_CANAF, LPC_CANAF_RAM, &AFSections);
#if FULL_CAN_AF_USED
	Chip_CAN_ConfigFullCANInt(LPC_CANAF, ENABLE);
	Chip_CAN_SetAFMode(LPC_CANAF, CAN_AF_FULL_MODE);
#else
	Chip_CAN_SetAFMode(LPC_CANAF, CAN_AF_NORMAL_MODE);
#endif /*FULL_CAN_AF_USED*/
#else
	Chip_CAN_SetAFMode(LPC_CANAF, CAN_AF_BYBASS_MODE);
#endif /*AF_LUT_USED*/
	NVIC_EnableIRQ(CAN_IRQn);


	/*
	 * Send a message, that signalizes, that CAN is ready.
	 */
//	send_can_message("hello",0x400,5);
}

/**
 * The CAN interrupt handler.
 * TODO: Handle errors
 */
void CAN_IRQHandler(void)
{
	uint32_t IntStatus;
	CAN_MSG_T RcvMsgBuf;
	IntStatus = Chip_CAN_GetIntStatus(LPC_CAN);

	checkCANErrorInfo(IntStatus);

	/* New Message came */
	if (IntStatus & CAN_ICR_RI) {
		Chip_CAN_Receive(LPC_CAN, &RcvMsgBuf);
		process_CAN_message(RcvMsgBuf);

	}
#if FULL_CAN_AF_USED
	uint16_t i = 0, FullCANEntryNum = 0;
	FullCANEntryNum = Chip_CAN_GetEntriesNum(LPC_CANAF, LPC_CANAF_RAM, CANAF_RAM_FULLCAN_SEC);
	if (FullCANEntryNum > 64) {
		FullCANEntryNum = 64;
	}
	for (i = 0; i < FullCANEntryNum; i++){
		if (Chip_CAN_GetFullCANIntStatus(LPC_CANAF, i)) {
			uint8_t SCC;
			Chip_CAN_FullCANReceive(LPC_CANAF, LPC_CANAF_RAM, i, &RcvMsgBuf, &SCC);
			process_CAN_message(RcvMsgBuf);
//			if (SCC == CAN_CTRL_NO) {
//			}
		}
	}
#endif /*FULL_CAN_AF_USED*/
}



/**
 * This function should be called to process the received message.\n
 * It differs between the IDs of the message.
 * @param message The message that should be processed.
 */
void process_CAN_message(CAN_MSG_T message){

	switch(message.ID){
	case 0x000:	//STOP			Stop all functions and especially set the relays idle.

		break;
	case 0x001: //MStatus		Contains the status of the multiplexer

		break;
	case 0x002: //ReqCl1		Contains a request from client 1

		break;
	case 0x003: //ReqCl2		Contains a request from client 2

		break;
	case 0x004: //ReqCl3		Contains a request from client 3

		break;
	case 0x005: //ReqCl4		Contains a request from client 4

		break;

	default:

		break;
	}


#ifdef __DAC
	process_CAN_message_DAC(message);
#endif

#ifdef __ADC
	process_CAN_message_ADC(message);
#endif


}


#ifdef __ADC
void process_CAN_message_ADC(CAN_MSG_T message){
	const float digScale = (5.0/65534.0);
	switch(message.ID){
		case 0x000:	//STOP			Stop all functions and especially set the relays idle.

			break;
		case 0x001: //MStatus		Contains the status of the multiplexer
			new_m_flag = 1;
			next_frequency = 	 (message.Data[1]<<8) + message.Data[0];
			next_amplitude_min = ((message.Data[3]<<8) + message.Data[2]) * digScale;
			next_amplitude_max = ((message.Data[5]<<8) + message.Data[4]) * digScale;
			next_periods = 		 (message.Data[7]<<8) + message.Data[6];
			break;
		case 0x002: //ReqCl1		Contains a request from client 1

			break;
		case 0x003: //ReqCl2		Contains a request from client 2

			break;
		case 0x004: //ReqCl3		Contains a request from client 3

			break;
		case 0x005: //ReqCl4		Contains a request from client 4

			break;

		default:

			break;
		}
}
#endif


#ifdef __DAC
void process_CAN_message_DAC(CAN_MSG_T message){
	const float digScale = (5.0/65534.0);
	switch(message.ID){
		case 0x000:	//STOP			Stop all functions and especially set the relays idle.
			emergency_flag = 1;
			break;
		case 0x005: //MStatus		Contains the status of the multiplexer
			next_f_flag = 1;
			new_m_flag = 1;
			next_frequency = 	 (message.Data[1]<<8) + message.Data[0];
			next_amplitude_min = ((message.Data[3]<<8) + message.Data[2]) * digScale;
			next_amplitude_max = ((message.Data[5]<<8) + message.Data[4]) * digScale;
			next_periods = 		 (message.Data[7]<<8) + message.Data[6];
			break;
		case 0x002: //ReqCl1		Contains a request from client 1
			new_m_flag = 1;
			next_f_flag = 1;
			next_frequency = 	 (message.Data[1]<<8) + message.Data[0];
			next_amplitude_min = ((message.Data[3]<<8) + message.Data[2]) * digScale;
			next_amplitude_max = ((message.Data[5]<<8) + message.Data[4]) * digScale;
			next_periods = 		 (message.Data[7]<<8) + message.Data[6];
			break;
		case 0x003: //ReqCl2		Contains a request from client 2

			break;
		case 0x004: //ReqCl3		Contains a request from client 3

			break;
		case 0x001: //ReqCl4		Contains a request from client 4

			break;

		default:

			break;
		}
}

#endif



/**
 * Sends a message with the given ID, containing the given data.
 * @param data Data to be send.
 * @param id ID that the message should have.
 * @param length Length of the data.
 */
void send_can_message(char *data, uint16_t id, uint8_t length){
	CAN_MSG_T SendMsgBuf;
	CAN_BUFFER_ID_T   TxBuf;
	SendMsgBuf.ID  = id;
	SendMsgBuf.DLC = length;
	SendMsgBuf.Type = 0;

	for(length--;length !=255;length--){
		SendMsgBuf.Data[length] = data[length];
	}

	do{
		TxBuf = Chip_CAN_GetFreeTxBuf(LPC_CAN);
	}while(TxBuf == CAN_BUFFER_LAST);

	Chip_CAN_Send(LPC_CAN, TxBuf, &SendMsgBuf);


}

/**
 * Sends the Multiplexer Status (MStatus)
 */
void send_multiplexer_status(void){
	char status[8] = "okay";

	uint8_t new_rotary_position = 8;




	status[4] = new_rotary_position;
	status[5] = 5;
	status[6] = 6;
	status[7] = 7;
	uint16_t status_id = 0x00000001;
	uint8_t length = 8;

	send_can_message(status, status_id, length);
}

/**
 * Function from the standard library.
 * @param Status Status of the current received message.
 */
void checkCANErrorInfo(uint32_t Status)
{
	if (Status & CAN_ICR_EI) {
		//    DEBUGOUT("Error Warning!\r\n");
	}
	if (Status & CAN_ICR_DOI) {
		//    DEBUGOUT("Data Overrun!\r\n");
	}
	if (Status & CAN_ICR_EPI) {
		//    DEBUGOUT("Error Passive!\r\n");
	}
	if (Status & CAN_ICR_ALI) {
		//    DEBUGOUT("Arbitration lost in the bit: %d(th)\r\n", CAN_ICR_ALCBIT_VAL(Status));
	}
	if (Status & CAN_ICR_BEI) {

		//    DEBUGOUT("Bus error !!!\r\n");

		if (Status & CAN_ICR_ERRDIR_RECEIVE) {
			//    DEBUGOUT("\t Error Direction: Transmitting\r\n");
		}
		else {
			//    DEBUGOUT("\t Error Direction: Receiving\r\n");
		}

		//    DEBUGOUT("\t Error Location: 0x%2x\r\n", CAN_ICR_ERRBIT_VAL(Status));
		//    DEBUGOUT("\t Error Type: 0x%1x\r\n", CAN_ICR_ERRC_VAL(Status));
	}
}
