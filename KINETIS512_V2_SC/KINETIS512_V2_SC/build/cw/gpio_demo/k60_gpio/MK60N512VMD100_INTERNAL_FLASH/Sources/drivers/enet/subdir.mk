################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"$(ENET1)/enet.c" \
"$(ENET1)/eth_phy.c" \
"$(ENET1)/mii.c" \
"$(ENET1)/nbuf.c" \

C_SRCS += \
$(ENET_ESCAPED)/enet.c \
$(ENET1_ESCAPED)/eth_phy.c \
$(ENET1_ESCAPED)/mii.c \
$(ENET1_ESCAPED)/nbuf.c \

OBJS += \
./Sources/drivers/enet/enet.obj \
./Sources/drivers/enet/eth_phy.obj \
./Sources/drivers/enet/mii.obj \
./Sources/drivers/enet/nbuf.obj \

OBJS_QUOTED += \
"./Sources/drivers/enet/enet.obj" \
"./Sources/drivers/enet/eth_phy.obj" \
"./Sources/drivers/enet/mii.obj" \
"./Sources/drivers/enet/nbuf.obj" \

C_DEPS += \
./Sources/drivers/enet/enet.d \
./Sources/drivers/enet/eth_phy.d \
./Sources/drivers/enet/mii.d \
./Sources/drivers/enet/nbuf.d \

C_DEPS_QUOTED += \
"./Sources/drivers/enet/enet.d" \
"./Sources/drivers/enet/eth_phy.d" \
"./Sources/drivers/enet/mii.d" \
"./Sources/drivers/enet/nbuf.d" \

OBJS_OS_FORMAT += \
./Sources/drivers/enet/enet.obj \
./Sources/drivers/enet/eth_phy.obj \
./Sources/drivers/enet/mii.obj \
./Sources/drivers/enet/nbuf.obj \


# Each subdirectory must supply rules for building sources it contributes
Sources/drivers/enet/enet.obj: $(ENET1_ESCAPED)/enet.c
	@echo 'Building file: $<'
	@echo 'Executing target #11 $<'
	@echo 'Invoking: ARM Compiler'
	"$(ARM_ToolsDirEnv)/mwccarm" -gccinc @@"Sources/drivers/enet/enet.args" -o "Sources/drivers/enet/enet.obj" -c "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/drivers/enet/enet.d: $(ENET1_ESCAPED)/enet.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

Sources/drivers/enet/eth_phy.obj: $(ENET1_ESCAPED)/eth_phy.c
	@echo 'Building file: $<'
	@echo 'Executing target #12 $<'
	@echo 'Invoking: ARM Compiler'
	"$(ARM_ToolsDirEnv)/mwccarm" -gccinc @@"Sources/drivers/enet/eth_phy.args" -o "Sources/drivers/enet/eth_phy.obj" -c "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/drivers/enet/eth_phy.d: $(ENET1_ESCAPED)/eth_phy.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

Sources/drivers/enet/mii.obj: $(ENET1_ESCAPED)/mii.c
	@echo 'Building file: $<'
	@echo 'Executing target #13 $<'
	@echo 'Invoking: ARM Compiler'
	"$(ARM_ToolsDirEnv)/mwccarm" -gccinc @@"Sources/drivers/enet/mii.args" -o "Sources/drivers/enet/mii.obj" -c "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/drivers/enet/mii.d: $(ENET1_ESCAPED)/mii.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

Sources/drivers/enet/nbuf.obj: $(ENET1_ESCAPED)/nbuf.c
	@echo 'Building file: $<'
	@echo 'Executing target #14 $<'
	@echo 'Invoking: ARM Compiler'
	"$(ARM_ToolsDirEnv)/mwccarm" -gccinc @@"Sources/drivers/enet/nbuf.args" -o "Sources/drivers/enet/nbuf.obj" -c "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/drivers/enet/nbuf.d: $(ENET1_ESCAPED)/nbuf.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '


