################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"$(COMMON1)/alloc.c" \
"$(COMMON1)/assert.c" \
"$(COMMON1)/io.c" \
"$(COMMON1)/memtest.c" \
"$(COMMON1)/printf.c" \
"$(COMMON1)/queue.c" \
"$(COMMON1)/startup.c" \
"$(COMMON1)/stdlib.c" \
"$(COMMON1)/uif.c" \

C_SRCS += \
$(COMMON_ESCAPED)/alloc.c \
$(COMMON1_ESCAPED)/assert.c \
$(COMMON1_ESCAPED)/io.c \
$(COMMON1_ESCAPED)/memtest.c \
$(COMMON1_ESCAPED)/printf.c \
$(COMMON1_ESCAPED)/queue.c \
$(COMMON1_ESCAPED)/startup.c \
$(COMMON1_ESCAPED)/stdlib.c \
$(COMMON1_ESCAPED)/uif.c \

OBJS += \
./Sources/common/alloc.obj \
./Sources/common/assert.obj \
./Sources/common/io.obj \
./Sources/common/memtest.obj \
./Sources/common/printf.obj \
./Sources/common/queue.obj \
./Sources/common/startup.obj \
./Sources/common/stdlib.obj \
./Sources/common/uif.obj \

OBJS_QUOTED += \
"./Sources/common/alloc.obj" \
"./Sources/common/assert.obj" \
"./Sources/common/io.obj" \
"./Sources/common/memtest.obj" \
"./Sources/common/printf.obj" \
"./Sources/common/queue.obj" \
"./Sources/common/startup.obj" \
"./Sources/common/stdlib.obj" \
"./Sources/common/uif.obj" \

C_DEPS += \
./Sources/common/alloc.d \
./Sources/common/assert.d \
./Sources/common/io.d \
./Sources/common/memtest.d \
./Sources/common/printf.d \
./Sources/common/queue.d \
./Sources/common/startup.d \
./Sources/common/stdlib.d \
./Sources/common/uif.d \

C_DEPS_QUOTED += \
"./Sources/common/alloc.d" \
"./Sources/common/assert.d" \
"./Sources/common/io.d" \
"./Sources/common/memtest.d" \
"./Sources/common/printf.d" \
"./Sources/common/queue.d" \
"./Sources/common/startup.d" \
"./Sources/common/stdlib.d" \
"./Sources/common/uif.d" \

OBJS_OS_FORMAT += \
./Sources/common/alloc.obj \
./Sources/common/assert.obj \
./Sources/common/io.obj \
./Sources/common/memtest.obj \
./Sources/common/printf.obj \
./Sources/common/queue.obj \
./Sources/common/startup.obj \
./Sources/common/stdlib.obj \
./Sources/common/uif.obj \


# Each subdirectory must supply rules for building sources it contributes
Sources/common/alloc.obj: $(COMMON1_ESCAPED)/alloc.c
	@echo 'Building file: $<'
	@echo 'Executing target #21 $<'
	@echo 'Invoking: ARM Compiler'
	"$(ARM_ToolsDirEnv)/mwccarm" -gccinc @@"Sources/common/alloc.args" -o "Sources/common/alloc.obj" -c "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/common/alloc.d: $(COMMON1_ESCAPED)/alloc.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

Sources/common/assert.obj: $(COMMON1_ESCAPED)/assert.c
	@echo 'Building file: $<'
	@echo 'Executing target #22 $<'
	@echo 'Invoking: ARM Compiler'
	"$(ARM_ToolsDirEnv)/mwccarm" -gccinc @@"Sources/common/assert.args" -o "Sources/common/assert.obj" -c "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/common/assert.d: $(COMMON1_ESCAPED)/assert.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

Sources/common/io.obj: $(COMMON1_ESCAPED)/io.c
	@echo 'Building file: $<'
	@echo 'Executing target #23 $<'
	@echo 'Invoking: ARM Compiler'
	"$(ARM_ToolsDirEnv)/mwccarm" -gccinc @@"Sources/common/io.args" -o "Sources/common/io.obj" -c "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/common/io.d: $(COMMON1_ESCAPED)/io.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

Sources/common/memtest.obj: $(COMMON1_ESCAPED)/memtest.c
	@echo 'Building file: $<'
	@echo 'Executing target #24 $<'
	@echo 'Invoking: ARM Compiler'
	"$(ARM_ToolsDirEnv)/mwccarm" -gccinc @@"Sources/common/memtest.args" -o "Sources/common/memtest.obj" -c "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/common/memtest.d: $(COMMON1_ESCAPED)/memtest.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

Sources/common/printf.obj: $(COMMON1_ESCAPED)/printf.c
	@echo 'Building file: $<'
	@echo 'Executing target #25 $<'
	@echo 'Invoking: ARM Compiler'
	"$(ARM_ToolsDirEnv)/mwccarm" -gccinc @@"Sources/common/printf.args" -o "Sources/common/printf.obj" -c "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/common/printf.d: $(COMMON1_ESCAPED)/printf.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

Sources/common/queue.obj: $(COMMON1_ESCAPED)/queue.c
	@echo 'Building file: $<'
	@echo 'Executing target #26 $<'
	@echo 'Invoking: ARM Compiler'
	"$(ARM_ToolsDirEnv)/mwccarm" -gccinc @@"Sources/common/queue.args" -o "Sources/common/queue.obj" -c "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/common/queue.d: $(COMMON1_ESCAPED)/queue.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

Sources/common/startup.obj: $(COMMON1_ESCAPED)/startup.c
	@echo 'Building file: $<'
	@echo 'Executing target #27 $<'
	@echo 'Invoking: ARM Compiler'
	"$(ARM_ToolsDirEnv)/mwccarm" -gccinc @@"Sources/common/startup.args" -o "Sources/common/startup.obj" -c "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/common/startup.d: $(COMMON1_ESCAPED)/startup.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

Sources/common/stdlib.obj: $(COMMON1_ESCAPED)/stdlib.c
	@echo 'Building file: $<'
	@echo 'Executing target #28 $<'
	@echo 'Invoking: ARM Compiler'
	"$(ARM_ToolsDirEnv)/mwccarm" -gccinc @@"Sources/common/stdlib.args" -o "Sources/common/stdlib.obj" -c "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/common/stdlib.d: $(COMMON1_ESCAPED)/stdlib.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

Sources/common/uif.obj: $(COMMON1_ESCAPED)/uif.c
	@echo 'Building file: $<'
	@echo 'Executing target #29 $<'
	@echo 'Invoking: ARM Compiler'
	"$(ARM_ToolsDirEnv)/mwccarm" -gccinc @@"Sources/common/uif.args" -o "Sources/common/uif.obj" -c "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/common/uif.d: $(COMMON1_ESCAPED)/uif.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '


