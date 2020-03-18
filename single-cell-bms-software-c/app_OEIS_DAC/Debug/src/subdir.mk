################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/app_OEIS_DAC.c \
../src/cr_startup_lpc175x_6x.c \
../src/crp.c \
../src/sysinit.c 

OBJS += \
./src/app_OEIS_DAC.o \
./src/cr_startup_lpc175x_6x.o \
./src/crp.o \
./src/sysinit.o 

C_DEPS += \
./src/app_OEIS_DAC.d \
./src/cr_startup_lpc175x_6x.d \
./src/crp.d \
./src/sysinit.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M3 -D__USE_LPCOPEN -D__USE_CMSIS_DSPLIB=CMSIS_DSPLIB_CM3 -D__LPC17XX__ -D__NEWLIB__ -I"E:\RWTH Aachen\Sem 3\ISEA\single-cell-bms-software-c\rtos_lib_LPC175x_6x" -I"E:\RWTH Aachen\Sem 3\ISEA\single-cell-bms-software-c\lpc_chip_175x_6x" -I"E:\RWTH Aachen\Sem 3\ISEA\single-cell-bms-software-c\hal_lib_LPC175x_6x_SC" -I"E:\RWTH Aachen\Sem 3\ISEA\single-cell-bms-software-c\hal_lib_LPC175x_6x_DAC" -I"E:\RWTH Aachen\Sem 3\ISEA\single-cell-bms-software-c\hal_lib_LPC175x_6x_DAC\inc" -I"E:\RWTH Aachen\Sem 3\ISEA\single-cell-bms-software-c\hal_lib_LPC175x_6x_SC\inc" -I"E:\RWTH Aachen\Sem 3\ISEA\single-cell-bms-software-c\app_OEIS_DAC\inc" -I"E:\RWTH Aachen\Sem 3\ISEA\single-cell-bms-software-c\lpc_chip_175x_6x\inc" -I"E:\RWTH Aachen\Sem 3\ISEA\single-cell-bms-software-c\CMSIS_DSPLIB_CM3\inc" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -D__NEWLIB__ -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


