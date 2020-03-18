function InitFcn

inputsize = 2048;
assignin('base','inputsize',inputsize)

%Transmitting
assignin('base','CAN_ID_Start_M',5)
assignin('base','CAN_ID_Next_F',1)

%Receiving
assignin('base','CAN_ID_RAW_A0',600)
assignin('base','CAN_ID_RAW_A1',601)
assignin('base','CAN_ID_RAW_B0',602)
assignin('base','CAN_ID_RAW_B1',603)
assignin('base','CAN_ID_RAW_C0',604)
assignin('base','CAN_ID_RAW_C1',605)
assignin('base','CAN_ID_RAW_D0',606)
assignin('base','CAN_ID_RAW_D1',607)


%FFT
assignin('base','CAN_ID_Timedata',hex2dec('100'))
assignin('base','CAN_ID_Frequencydata',hex2dec('101'))
assignin('base','CAN_ID_Timedata_float',hex2dec('102'))
assignin('base','CAN_ID_Frequencydata_float',hex2dec('103'))


assignin('base','Timedata',zeros(inputsize,1))
assignin('base','Timedata_counter_inc',4)
assignin('base','Frequencydata',zeros(inputsize,1))
assignin('base','Frequencydata_counter',1)
assignin('base','Frequencydata_counter_inc',4)