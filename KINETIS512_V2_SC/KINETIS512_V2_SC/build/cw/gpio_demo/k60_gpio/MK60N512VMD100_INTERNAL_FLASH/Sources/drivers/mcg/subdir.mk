################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"$(MCG1)/mcg.c" \

C_SRCS += \
$(MCG_ESCAPED)/mcg.c \

OBJS += \
./Sources/drivers/mcg/mcg.obj \

OBJS_QUOTED += \
"./Sources/drivers/mcg/mcg.obj" \

C_DEPS += \
./Sources/drivers/mcg/mcg.d \

C_DEPS_QUOTED += \
"./Sources/drivers/mcg/mcg.d" \

OBJS_OS_FORMAT += \
./Sources/drivers/mcg/mcg.obj \


# Each subdirectory must supply rules for building sources it contributes
Sources/drivers/mcg/mcg.obj: $(MCG1_ESCAPED)/mcg.c
	@echo 'Building file: $<'
	@echo 'Executing target #8 $<'
	@echo 'Invoking: ARM Compiler'
	"$(ARM_ToolsDirEnv)/mwccarm" -gccinc @@"Sources/drivers/mcg/mcg.args" -o "Sources/drivers/mcg/mcg.obj" -c "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/drivers/mcg/mcg.d: $(MCG1_ESCAPED)/mcg.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '


