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
all: libhal_lib_LPC175x_6x_DAC.a

# Tool invocations
libhal_lib_LPC175x_6x_DAC.a: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Archiver'
	arm-none-eabi-ar -r  "libhal_lib_LPC175x_6x_DAC.a" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(OBJS)$(ARCHIVES)$(C_DEPS) libhal_lib_LPC175x_6x_DAC.a
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "libhal_lib_LPC175x_6x_DAC.a" ; # arm-none-eabi-objdump -h -S "libhal_lib_LPC175x_6x_DAC.a" >"libhal_lib_LPC175x_6x_DAC.lss"
	-@echo ' '

.PHONY: all clean dependents post-build

-include ../makefile.targets
