################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"$(RCM1)/rcm.c" \

C_SRCS += \
$(RCM_ESCAPED)/rcm.c \

OBJS += \
./Sources/drivers/rcm/rcm.obj \

OBJS_QUOTED += \
"./Sources/drivers/rcm/rcm.obj" \

C_DEPS += \
./Sources/drivers/rcm/rcm.d \

C_DEPS_QUOTED += \
"./Sources/drivers/rcm/rcm.d" \

OBJS_OS_FORMAT += \
./Sources/drivers/rcm/rcm.obj \


# Each subdirectory must supply rules for building sources it contributes
Sources/drivers/rcm/rcm.obj: $(RCM1_ESCAPED)/rcm.c
	@echo 'Building file: $<'
	@echo 'Executing target #6 $<'
	@echo 'Invoking: ARM Compiler'
	"$(ARM_ToolsDirEnv)/mwccarm" -gccinc @@"Sources/drivers/rcm/rcm.args" -o "Sources/drivers/rcm/rcm.obj" -c "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/drivers/rcm/rcm.d: $(RCM1_ESCAPED)/rcm.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '


