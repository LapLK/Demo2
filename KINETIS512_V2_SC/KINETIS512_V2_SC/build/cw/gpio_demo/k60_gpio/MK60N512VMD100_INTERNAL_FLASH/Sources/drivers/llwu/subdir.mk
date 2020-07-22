################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"$(LLWU1)/llwu.c" \

C_SRCS += \
$(LLWU_ESCAPED)/llwu.c \

OBJS += \
./Sources/drivers/llwu/llwu.obj \

OBJS_QUOTED += \
"./Sources/drivers/llwu/llwu.obj" \

C_DEPS += \
./Sources/drivers/llwu/llwu.d \

C_DEPS_QUOTED += \
"./Sources/drivers/llwu/llwu.d" \

OBJS_OS_FORMAT += \
./Sources/drivers/llwu/llwu.obj \


# Each subdirectory must supply rules for building sources it contributes
Sources/drivers/llwu/llwu.obj: $(LLWU1_ESCAPED)/llwu.c
	@echo 'Building file: $<'
	@echo 'Executing target #10 $<'
	@echo 'Invoking: ARM Compiler'
	"$(ARM_ToolsDirEnv)/mwccarm" -gccinc @@"Sources/drivers/llwu/llwu.args" -o "Sources/drivers/llwu/llwu.obj" -c "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/drivers/llwu/llwu.d: $(LLWU1_ESCAPED)/llwu.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '


