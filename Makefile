TARGET = app

DEBUG = 1
# optimization
OPT = -O3 -g

# Build path
BUILD_DIR = build

# sdk
SDK_DIR   = ../sdk
SDK_BRANCH = master
ifeq ($(SDK_DIR), $(wildcard $(SDK_DIR)))
else
$(shell cd ../ && git clone -b $(SDK_BRANCH) git@github.com:leadercxn/sdk.git)
endif

# 版本脚本
$(shell python $(SDK_DIR)/scripts/preBuild.py)
VERSION = $(shell python $(SDK_DIR)/scripts/getVersion.py)_$(shell git rev-parse --short HEAD)

# 时间戳
TIMESTAMP = $(shell date +%Y%m%d%H%M)


# 系统平台
ifeq ($(OS),Windows_NT)
	PLATFORM="Windows"
else
	ifeq ($(shell uname),Darwin)
  		PLATFORM="MacOS"
 	else
  		PLATFORM="Unix-Like"
 	endif
endif

$(info PLATFORM: $(PLATFORM))


######################################
# source
######################################
# C sources
C_SOURCES =  				\
handler/letter_handler.c	\
src/main.c 					\
src/hk_peripheral.c 		\
src/hk32f0xx_it.c  			\
src/shell_cmds/test_cmd.c	\
core/system_hk32f0xx.c		\
$(SDK_DIR)/platform/hk/HK32F030/STD_LIB/src/hk32f0xx_gpio.c	\
$(SDK_DIR)/platform/hk/HK32F030/STD_LIB/src/hk32f0xx_misc.c	\
$(SDK_DIR)/platform/hk/HK32F030/STD_LIB/src/hk32f0xx_rcc.c	\
$(SDK_DIR)/platform/hk/HK32F030/STD_LIB/src/hk32f0xx_usart.c	\
$(SDK_DIR)/platform/hk/HK32F030/STD_LIB/src/hk32f0xx_tim.c	\
$(SDK_DIR)/components/trace/trace.c	\
$(SDK_DIR)/components/app_scheduler/app_scheduler.c	\
$(SDK_DIR)/components/app_timer/app_timer_list.c	\
$(SDK_DIR)/components/letter-shell/src/shell_cmd_list.c	\
$(SDK_DIR)/components/letter-shell/src/shell_companion.c	\
$(SDK_DIR)/components/letter-shell/src/shell_ext.c	\
$(SDK_DIR)/components/letter-shell/src/shell.c	\
$(SDK_DIR)/customized/hal/usart/retarget.c	\
$(SDK_DIR)/customized/hk_lib/f0/usart/hk_usart.c	\
$(SDK_DIR)/customized/hk_lib/f0/gpio/hk_gpio.c	\
$(SDK_DIR)/customized/hk_lib/f0/systick/hk_systick.c	\
$(SDK_DIR)/customized/hk_lib/f0/timer/hk_timer.c


# C includes
C_INCLUDES =  \
-Isrc \
-Ibsp \
-Icore \
-Ihandler \
-I$(SDK_DIR)/platform/hk/HK32F030/STD_LIB/inc \
-I$(SDK_DIR)/platform/hk/HK32F030/CMSIS/CM0/DeviceSupport \
-I$(SDK_DIR)/platform/hk/HK32F030/CMSIS/CM0/CoreSupport	\
-I$(SDK_DIR)/components/util	\
-I$(SDK_DIR)/components/lib_err	\
-I$(SDK_DIR)/components/letter-shell/src \
-I$(SDK_DIR)/customized/hal/gpio	\
-I$(SDK_DIR)/customized/hal/systick	\
-I$(SDK_DIR)/customized/hal/usart	\
-I$(SDK_DIR)/customized/hal/timer	\
-I$(SDK_DIR)/customized/hk_lib/f0/usart	\
-I$(SDK_DIR)/customized/hk_lib/f0/gpio	\
-I$(SDK_DIR)/customized/hk_lib/f0/systick	\
-I$(SDK_DIR)/customized/hk_lib/f0/timer	\
-I$(SDK_DIR)/components/trace	\
-I$(SDK_DIR)/components/queue	\
-I$(SDK_DIR)/components/app_scheduler	\
-I$(SDK_DIR)/components/app_timer

# ASM sources
ASM_SOURCES =  \
linker/startup_hk32f030x8_gcc.s

# macros for gcc
# AS defines
AS_DEFS = 

# C 宏
C_DEFS =  \
-DUSE_STDPERIPH_DRIVER \
-DHK32F030 \
-DBOARD_V001	\
-DTRACE_ENABLE	\
-DTRACE_LEVEL=5


#######################################
# binaries
#######################################
# The gcc compiler bin path can be either defined in make command via GCC_PATH variable (> make GCC_PATH=xxx)
# either it can be added to the PATH environment variable.

PREFIX = arm-none-eabi-
ifdef GCC_PATH
CC = $(GCC_PATH)/$(PREFIX)gcc
AS = $(GCC_PATH)/$(PREFIX)gcc -x assembler-with-cpp
CP = $(GCC_PATH)/$(PREFIX)objcopy
SZ = $(GCC_PATH)/$(PREFIX)size
else
CC = $(PREFIX)gcc
AS = $(PREFIX)gcc -x assembler-with-cpp
CP = $(PREFIX)objcopy
SZ = $(PREFIX)size
endif

HEX = $(CP) -O ihex
BIN = $(CP) -O binary -S

# CC = armcc
# AS = armasm
# LD = armlink
# AR = armar


# LOG Message
$(info VERSION: $(VERSION))
$(info sdk path: $(SDK_DIR))
$(info TIMESTAMP: $(TIMESTAMP))


#######################################
# CFLAGS
#######################################
# cpu
CPU = -mcpu=cortex-m0

# fpu
# NONE for Cortex-M0/M0+/M3

# float-abi


# mcu
MCU = $(CPU) -mthumb $(FPU) $(FLOAT-ABI)



# AS includes
AS_INCLUDES = 


# compile gcc flags
ASFLAGS = $(MCU) $(AS_DEFS) $(AS_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections

CFLAGS = $(MCU) $(C_DEFS) $(C_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections

ifeq ($(DEBUG), 1)
CFLAGS += -g -gdwarf-2
endif


# Generate dependency information
CFLAGS += -MMD -MP -MF"$(@:%.o=%.d)"


#######################################
# LDFLAGS
#######################################
# link script
LDSCRIPT = linker/STM32F030C8Tx_FLASH.ld

# libraries
LIBS = -lc -lm -lnosys 
LIBDIR = 
LDFLAGS = $(MCU) -specs=nano.specs -T$(LDSCRIPT) $(LIBDIR) $(LIBS) -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref -Wl,--gc-sections

# default action: build all
all: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/$(TARGET).bin


#######################################
# build the application
#######################################
# list of objects
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))
# list of ASM program objects
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(ASM_SOURCES:.s=.o)))
vpath %.s $(sort $(dir $(ASM_SOURCES)))

$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR) 
	$(CC) -c $(CFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) $< -o $@

$(BUILD_DIR)/%.o: %.s Makefile | $(BUILD_DIR)
	$(AS) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS) Makefile
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@
	$(SZ) $@

$(BUILD_DIR)/$(TARGET).hex: $(BUILD_DIR)/$(TARGET).elf | $(BUILD_DIR)
	$(HEX) $< $@
	
$(BUILD_DIR)/$(TARGET).bin: $(BUILD_DIR)/$(TARGET).elf | $(BUILD_DIR)
	$(BIN) $< $@	
	
$(BUILD_DIR):
	mkdir $@		

#######################################
# clean up
#######################################
clean:
	-rm -fR $(BUILD_DIR)

#######################################
# dependencies
#######################################
-include $(wildcard $(BUILD_DIR)/*.d)

SDK_CONFIG_FILE := bsp/config.h
CMSIS_CONFIG_TOOL := $(SDK_DIR)/scripts/cmsisconfig/CMSIS_Configuration_Wizard.jar

include cmd.mk

# *** EOF ***