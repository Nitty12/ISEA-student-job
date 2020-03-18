################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../portable/GCC/ARM_CM3/port.c 

OBJS += \
./portable/GCC/ARM_CM3/port.o 

C_DEPS += \
./portable/GCC/ARM_CM3/port.d 


# Each subdirectory must supply rules for building sources it contributes
portable/GCC/ARM_CM3/%.o: ../portable/GCC/ARM_CM3/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M3 -D__USE_LPCOPEN -D__USE_CMSIS_DSPLIB=CMSIS_DSPLIB_CM3 -D__LPC17XX__ -D__NEWLIB__ -I"E:\RWTH Aachen\Sem 3\ISEA\single-cell-bms-software-c\hal_lib_LPC175x_6x_SC\inc" -I"E:\RWTH Aachen\Sem 3\ISEA\single-cell-bms-software-c\rtos_lib_LPC175x_6x\inc" -I"E:\RWTH Aachen\Sem 3\ISEA\single-cell-bms-software-c\rtos_lib_LPC175x_6x\include" -I"E:\RWTH Aachen\Sem 3\ISEA\single-cell-bms-software-c\rtos_lib_LPC175x_6x\portable\GCC\ARM_CM3" -I"E:\RWTH Aachen\Sem 3\ISEA\single-cell-bms-software-c\lpc_chip_175x_6x\inc" -I"E:\RWTH Aachen\Sem 3\ISEA\single-cell-bms-software-c\CMSIS_DSPLIB_CM3\inc" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -D__NEWLIB__ -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


