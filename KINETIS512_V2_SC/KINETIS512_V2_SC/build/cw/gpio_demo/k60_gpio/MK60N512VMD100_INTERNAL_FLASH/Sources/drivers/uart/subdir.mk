################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"$(UART1)/uart.c" \

C_SRCS += \
$(UART_ESCAPED)/uart.c \

OBJS += \
./Sources/drivers/uart/uart.obj \

OBJS_QUOTED += \
"./Sources/drivers/uart/uart.obj" \

C_DEPS += \
./Sources/drivers/uart/uart.d \

C_DEPS_QUOTED += \
"./Sources/drivers/uart/uart.d" \

OBJS_OS_FORMAT += \
./Sources/drivers/uart/uart.obj \


# Each subdirectory must supply rules for building sources it contributes
Sources/drivers/uart/uart.obj: $(UART1_ESCAPED)/uart.c
	@echo 'Building file: $<'
	@echo 'Executing target #3 $<'
	@echo 'Invoking: ARM Compiler'
	"$(ARM_ToolsDirEnv)/mwccarm" -gccinc @@"Sources/drivers/uart/uart.args" -o "Sources/drivers/uart/uart.obj" -c "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/drivers/uart/uart.d: $(UART1_ESCAPED)/uart.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '


