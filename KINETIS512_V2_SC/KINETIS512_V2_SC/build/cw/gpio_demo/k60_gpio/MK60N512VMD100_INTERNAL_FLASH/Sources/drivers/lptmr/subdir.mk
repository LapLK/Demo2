################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"$(LPTMR1)/lptmr.c" \

C_SRCS += \
$(LPTMR_ESCAPED)/lptmr.c \

OBJS += \
./Sources/drivers/lptmr/lptmr.obj \

OBJS_QUOTED += \
"./Sources/drivers/lptmr/lptmr.obj" \

C_DEPS += \
./Sources/drivers/lptmr/lptmr.d \

C_DEPS_QUOTED += \
"./Sources/drivers/lptmr/lptmr.d" \

OBJS_OS_FORMAT += \
./Sources/drivers/lptmr/lptmr.obj \


# Each subdirectory must supply rules for building sources it contributes
Sources/drivers/lptmr/lptmr.obj: $(LPTMR1_ESCAPED)/lptmr.c
	@echo 'Building file: $<'
	@echo 'Executing target #9 $<'
	@echo 'Invoking: ARM Compiler'
	"$(ARM_ToolsDirEnv)/mwccarm" -gccinc @@"Sources/drivers/lptmr/lptmr.args" -o "Sources/drivers/lptmr/lptmr.obj" -c "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/drivers/lptmr/lptmr.d: $(LPTMR1_ESCAPED)/lptmr.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '


