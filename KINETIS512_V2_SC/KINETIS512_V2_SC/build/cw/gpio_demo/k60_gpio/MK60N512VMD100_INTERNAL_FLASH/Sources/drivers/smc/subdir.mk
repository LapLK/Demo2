################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"$(SMC1)/smc.c" \

C_SRCS += \
$(SMC_ESCAPED)/smc.c \

OBJS += \
./Sources/drivers/smc/smc.obj \

OBJS_QUOTED += \
"./Sources/drivers/smc/smc.obj" \

C_DEPS += \
./Sources/drivers/smc/smc.d \

C_DEPS_QUOTED += \
"./Sources/drivers/smc/smc.d" \

OBJS_OS_FORMAT += \
./Sources/drivers/smc/smc.obj \


# Each subdirectory must supply rules for building sources it contributes
Sources/drivers/smc/smc.obj: $(SMC1_ESCAPED)/smc.c
	@echo 'Building file: $<'
	@echo 'Executing target #4 $<'
	@echo 'Invoking: ARM Compiler'
	"$(ARM_ToolsDirEnv)/mwccarm" -gccinc @@"Sources/drivers/smc/smc.args" -o "Sources/drivers/smc/smc.obj" -c "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/drivers/smc/smc.d: $(SMC1_ESCAPED)/smc.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '


