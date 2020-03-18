################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/board.c \
../src/board_sysinit.c \
../src/lpc_175x_6x_hal_adc.c \
../src/lpc_175x_6x_hal_can.c \
../src/lpc_175x_6x_hal_uart.c 

OBJS += \
./src/board.o \
./src/board_sysinit.o \
./src/lpc_175x_6x_hal_adc.o \
./src/lpc_175x_6x_hal_can.o \
./src/lpc_175x_6x_hal_uart.o 

C_DEPS += \
./src/board.d \
./src/board_sysinit.d \
./src/lpc_175x_6x_hal_adc.d \
./src/lpc_175x_6x_hal_can.d \
./src/lpc_175x_6x_hal_uart.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -D__REDLIB__ -DCORE_M3 -D__USE_LPCOPEN -D__USE_CMSIS_DSPLIB=CMSIS_DSPLIB_CM3 -D__LPC17XX__ -I"E:\RWTH Aachen\Sem 3\ISEA\single-cell-bms-software-c\hal_lib_LPC175x_6x_SC\inc" -I"E:\RWTH Aachen\Sem 3\ISEA\single-cell-bms-software-c\lpc_chip_175x_6x\inc" -I"E:\RWTH Aachen\Sem 3\ISEA\single-cell-bms-software-c\CMSIS_DSPLIB_CM3\inc" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


