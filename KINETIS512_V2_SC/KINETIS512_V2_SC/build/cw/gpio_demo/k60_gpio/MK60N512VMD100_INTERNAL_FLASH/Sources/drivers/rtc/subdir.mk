################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"$(RTC1)/rtc.c" \

C_SRCS += \
$(RTC_ESCAPED)/rtc.c \

OBJS += \
./Sources/drivers/rtc/rtc.obj \

OBJS_QUOTED += \
"./Sources/drivers/rtc/rtc.obj" \

C_DEPS += \
./Sources/drivers/rtc/rtc.d \

C_DEPS_QUOTED += \
"./Sources/drivers/rtc/rtc.d" \

OBJS_OS_FORMAT += \
./Sources/drivers/rtc/rtc.obj \


# Each subdirectory must supply rules for building sources it contributes
Sources/drivers/rtc/rtc.obj: $(RTC1_ESCAPED)/rtc.c
	@echo 'Building file: $<'
	@echo 'Executing target #5 $<'
	@echo 'Invoking: ARM Compiler'
	"$(ARM_ToolsDirEnv)/mwccarm" -gccinc @@"Sources/drivers/rtc/rtc.args" -o "Sources/drivers/rtc/rtc.obj" -c "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/drivers/rtc/rtc.d: $(RTC1_ESCAPED)/rtc.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '


