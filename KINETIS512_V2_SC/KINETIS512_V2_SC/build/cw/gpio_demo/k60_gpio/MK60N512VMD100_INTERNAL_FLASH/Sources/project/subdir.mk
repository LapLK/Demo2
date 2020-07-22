################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"$(GPIO_DEMO1)/gpio_demo.c" \

C_SRCS += \
$(GPIO_DEMO_ESCAPED)/gpio_demo.c \

OBJS += \
./Sources/project/gpio_demo.obj \

OBJS_QUOTED += \
"./Sources/project/gpio_demo.obj" \

C_DEPS += \
./Sources/project/gpio_demo.d \

C_DEPS_QUOTED += \
"./Sources/project/gpio_demo.d" \

OBJS_OS_FORMAT += \
./Sources/project/gpio_demo.obj \


# Each subdirectory must supply rules for building sources it contributes
Sources/project/gpio_demo.obj: $(GPIO_DEMO1_ESCAPED)/gpio_demo.c
	@echo 'Building file: $<'
	@echo 'Executing target #1 $<'
	@echo 'Invoking: ARM Compiler'
	"$(ARM_ToolsDirEnv)/mwccarm" -gccinc @@"Sources/project/gpio_demo.args" -o "Sources/project/gpio_demo.obj" -c "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/project/gpio_demo.d: $(GPIO_DEMO1_ESCAPED)/gpio_demo.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '


