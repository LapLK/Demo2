################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"$(ADC17)/adc16.c" \

C_SRCS += \
$(ADC16_ESCAPED)/adc16.c \

OBJS += \
./Sources/drivers/adc16/adc16.obj \

OBJS_QUOTED += \
"./Sources/drivers/adc16/adc16.obj" \

C_DEPS += \
./Sources/drivers/adc16/adc16.d \

C_DEPS_QUOTED += \
"./Sources/drivers/adc16/adc16.d" \

OBJS_OS_FORMAT += \
./Sources/drivers/adc16/adc16.obj \


# Each subdirectory must supply rules for building sources it contributes
Sources/drivers/adc16/adc16.obj: $(ADC17_ESCAPED)/adc16.c
	@echo 'Building file: $<'
	@echo 'Executing target #15 $<'
	@echo 'Invoking: ARM Compiler'
	"$(ARM_ToolsDirEnv)/mwccarm" -gccinc @@"Sources/drivers/adc16/adc16.args" -o "Sources/drivers/adc16/adc16.obj" -c "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/drivers/adc16/adc16.d: $(ADC17_ESCAPED)/adc16.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '


