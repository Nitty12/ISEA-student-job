################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: app_OEIS_DAC.axf

dependents:
	-cd E:/RWTH\ Aachen/Sem\ 3/ISEA/single-cell-bms-software-c/hal_lib_LPC175x_6x_DAC/Debug && $(MAKE) clean all
	-cd E:/RWTH\ Aachen/Sem\ 3/ISEA/single-cell-bms-software-c/hal_lib_LPC175x_6x_SC/Debug && $(MAKE) clean all
	-cd E:/RWTH\ Aachen/Sem\ 3/ISEA/single-cell-bms-software-c/lpc_chip_175x_6x/Debug && $(MAKE) clean all
	-cd E:/RWTH\ Aachen/Sem\ 3/ISEA/single-cell-bms-software-c/rtos_lib_LPC175x_6x/Debug && $(MAKE) clean all

# Tool invocations
app_OEIS_DAC.axf: $(OBJS) $(USER_OBJS) E:/RWTH\ Aachen/Sem\ 3/ISEA/single-cell-bms-software-c/hal_lib_LPC175x_6x_DAC/Debug/libhal_lib_LPC175x_6x_DAC.a E:/RWTH\ Aachen/Sem\ 3/ISEA/single-cell-bms-software-c/hal_lib_LPC175x_6x_SC/Debug/libhal_lib_LPC175x_6x_SC.a E:/RWTH\ Aachen/Sem\ 3/ISEA/single-cell-bms-software-c/lpc_chip_175x_6x/Debug/liblpc_chip_175x_6x.a E:/RWTH\ Aachen/Sem\ 3/ISEA/single-cell-bms-software-c/rtos_lib_LPC175x_6x/Debug/librtos_lib_LPC175x_6x.a
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -L"E:\RWTH Aachen\Sem 3\ISEA\single-cell-bms-software-c\rtos_lib_LPC175x_6x\Debug" -L"E:\RWTH Aachen\Sem 3\ISEA\single-cell-bms-software-c\hal_lib_LPC175x_6x_DAC\Debug" -L"E:\RWTH Aachen\Sem 3\ISEA\single-cell-bms-software-c\hal_lib_LPC175x_6x_SC\Debug" -L"E:\RWTH Aachen\Sem 3\ISEA\single-cell-bms-software-c\lpc_chip_175x_6x\Debug" -L"E:\RWTH Aachen\Sem 3\ISEA\single-cell-bms-software-c\CMSIS_DSPLIB_CM3\lib" -Xlinker -Map="app_OEIS_DAC.map" -Xlinker --gc-sections -Xlinker -print-memory-usage -mcpu=cortex-m3 -mthumb -T "app_OEIS_DAC_Debug.ld" -o "app_OEIS_DAC.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) app_OEIS_DAC.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "app_OEIS_DAC.axf"; # arm-none-eabi-objcopy -v -O binary "app_OEIS_DAC.axf" "app_OEIS_DAC.bin" ; # checksum -p LPC1769 -d "app_OEIS_DAC.bin";
	-@echo ' '

.PHONY: all clean dependents post-build
E:/RWTH\ Aachen/Sem\ 3/ISEA/single-cell-bms-software-c/hal_lib_LPC175x_6x_DAC/Debug/libhal_lib_LPC175x_6x_DAC.a:
E:/RWTH\ Aachen/Sem\ 3/ISEA/single-cell-bms-software-c/hal_lib_LPC175x_6x_SC/Debug/libhal_lib_LPC175x_6x_SC.a:
E:/RWTH\ Aachen/Sem\ 3/ISEA/single-cell-bms-software-c/lpc_chip_175x_6x/Debug/liblpc_chip_175x_6x.a:
E:/RWTH\ Aachen/Sem\ 3/ISEA/single-cell-bms-software-c/rtos_lib_LPC175x_6x/Debug/librtos_lib_LPC175x_6x.a:

-include ../makefile.targets
