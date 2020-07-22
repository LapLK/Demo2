################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"$(CPU)/arm_cm4.c" \
"$(CPU)/start.c" \
"$(CPU)/sysinit.c" \
"$(CPU)/vectors.c" \

C_SRCS += \
$(CPU_ESCAPED)/arm_cm4.c \
$(CPU_ESCAPED)/start.c \
$(CPU_ESCAPED)/sysinit.c \
$(CPU_ESCAPED)/vectors.c \

S_SRCS += \
$(CPU_ESCAPED)/cw_crt0.s \

S_SRCS_QUOTED += \
"$(CPU)/cw_crt0.s" \

S_DEPS_QUOTED += \
"./Sources/cpu/cw_crt0.d" \

OBJS += \
./Sources/cpu/arm_cm4.obj \
./Sources/cpu/cw_crt0.obj \
./Sources/cpu/start.obj \
./Sources/cpu/sysinit.obj \
./Sources/cpu/vectors.obj \

S_DEPS += \
./Sources/cpu/cw_crt0.d \

OBJS_QUOTED += \
"./Sources/cpu/arm_cm4.obj" \
"./Sources/cpu/cw_crt0.obj" \
"./Sources/cpu/start.obj" \
"./Sources/cpu/sysinit.obj" \
"./Sources/cpu/vectors.obj" \

C_DEPS += \
./Sources/cpu/arm_cm4.d \
./Sources/cpu/start.d \
./Sources/cpu/sysinit.d \
./Sources/cpu/vectors.d \

C_DEPS_QUOTED += \
"./Sources/cpu/arm_cm4.d" \
"./Sources/cpu/start.d" \
"./Sources/cpu/sysinit.d" \
"./Sources/cpu/vectors.d" \

OBJS_OS_FORMAT += \
./Sources/cpu/arm_cm4.obj \
./Sources/cpu/cw_crt0.obj \
./Sources/cpu/start.obj \
./Sources/cpu/sysinit.obj \
./Sources/cpu/vectors.obj \


# Each subdirectory must supply rules for building sources it contributes
Sources/cpu/arm_cm4.obj: $(CPU_ESCAPED)/arm_cm4.c
	@echo 'Building file: $<'
	@echo 'Executing target #16 $<'
	@echo 'Invoking: ARM Compiler'
	"$(ARM_ToolsDirEnv)/mwccarm" -gccinc @@"Sources/cpu/arm_cm4.args" -o "Sources/cpu/arm_cm4.obj" -c "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/cpu/arm_cm4.d: $(CPU_ESCAPED)/arm_cm4.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

Sources/cpu/cw_crt0.obj: $(CPU_ESCAPED)/cw_crt0.s
	@echo 'Building file: $<'
	@echo 'Executing target #17 $<'
	@echo 'Invoking: ARM Assembler'
	"$(ARM_ToolsDirEnv)/mwasmarm" @@"Sources/cpu/cw_crt0.args" -o "Sources/cpu/cw_crt0.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/cpu/cw_crt0.d: $(CPU_ESCAPED)/cw_crt0.s
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

Sources/cpu/start.obj: $(CPU_ESCAPED)/start.c
	@echo 'Building file: $<'
	@echo 'Executing target #18 $<'
	@echo 'Invoking: ARM Compiler'
	"$(ARM_ToolsDirEnv)/mwccarm" -gccinc @@"Sources/cpu/start.args" -o "Sources/cpu/start.obj" -c "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/cpu/start.d: $(CPU_ESCAPED)/start.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

Sources/cpu/sysinit.obj: $(CPU_ESCAPED)/sysinit.c
	@echo 'Building file: $<'
	@echo 'Executing target #19 $<'
	@echo 'Invoking: ARM Compiler'
	"$(ARM_ToolsDirEnv)/mwccarm" -gccinc @@"Sources/cpu/sysinit.args" -o "Sources/cpu/sysinit.obj" -c "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/cpu/sysinit.d: $(CPU_ESCAPED)/sysinit.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

Sources/cpu/vectors.obj: $(CPU_ESCAPED)/vectors.c
	@echo 'Building file: $<'
	@echo 'Executing target #20 $<'
	@echo 'Invoking: ARM Compiler'
	"$(ARM_ToolsDirEnv)/mwccarm" -gccinc @@"Sources/cpu/vectors.args" -o "Sources/cpu/vectors.obj" -c "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/cpu/vectors.d: $(CPU_ESCAPED)/vectors.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '


