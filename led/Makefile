# define project name as PROJ_NAME var.
PROJ_NAME = Led

# add a path for building tools
TOOLS_DIR = /usr/bin

# select necessary tools to build this project.
# tool arm-none-eabi-gcc     -> ARM cross compiler for C & C++
# tool arm-none-eabi-objcopy -> copy and translate object files
# tool arm-none-eabi-gdb     -> GNU debugger for ARM
# tool arm-none-eabi-as      -> the portable GNU assembler

CC      = $(TOOLS_DIR)/arm-none-eabi-gcc
OBJCOPY = $(TOOLS_DIR)/arm-none-eabi-objcopy
GDB     = $(TOOLS_DIR)/arm-none-eabi-gdb
AS      = $(TOOLS_DIR)/arm-none-eabi-as

# include each file in INC_DIRS path.
INCLUDE = $(addprefix -I,$(INC_DIRS))

# define below words for using stm32 standard peripheral library.
DEFS  = -D USE_STDPERIPH_DRIVER \
	-D STM32F40_41xxx

# Options for arm-none-eabi-gcc
# option -mcpu=cortex-m4   -> specify the name of the target processor 
# option -mthumb           -> select between generating code that execute in ARM and Thumb states
# option -mthumb-interwork -> generate code that supports calling between the ARM and Thumb instruction sets
# option -mlittle-endian   -> generate little-endian code
# option -mfloat-abi=hard  -> use FPU-specific calling conventions 
# option -mfpu=fpv4-sp-d16 -> specifies what floating-point hardware(or hardware emulation)

AFLAGS  = -mcpu=cortex-m4   \
	  -mthumb           \
	  -mthumb-interwork \
	  -mlittle-endian   \
	  -mfloat-abi=hard  \
	  -mfpu=fpv4-sp-d16 

# Options for arm-none-eabi-gcc 
# option -ggdb                        -> produce debugging information for use by GDB
# option -O0                          -> Reduce compilation time amd make debugging produce that expected results
# option -Wall -Wextra                -> enable all warnings and enable some extra warning flags 
# option --specs=nosys.sepcs          -> use static library libnosys.a

CFLAGS  = -ggdb               \
	  -O0                 \
	  -Wall -Wextra       \
	  --specs=nosys.specs \
          $(AFLAGS)

#Options for arm-none-eabi-as
#option -Wl,-T -> add a linker script to tell link what to do.
LFLAGS  = -Wl,-T,./links/stm32_flash.ld

# add some libraries to build for whole project
INC_DIRS  = ./user/inc                              \
	    ./lib/STM32F4xx_StdPeriph_Driver/inc    \
	    ./lib/CMSIS/Include                     \
	    ./lib/CMSIS/Device/ST/STM32F4xx/Include 

# add source files for this project
ST_DIR=./lib/STM32F4xx_StdPeriph_Driver/src
SRCS = 	$(ST_DIR)/stm32f4xx_rcc.c       \
	$(ST_DIR)/stm32f4xx_gpio.c      \
	./user/src/system_stm32f4xx.c   \
	./user/src/stm32f4xx_it.c       \
	./user/src/delay.c

# here major program is
SRCS += ./user/src/main.c

# add a path that point to startup file 
STARTUP = ./lib/CMSIS/Device/ST/STM32F4xx/Source/Templates/TrueSTUDIO/startup_stm32f40_41xxx.s

# mark each file as object file name format 
STARTUP_OBJS  = $(STARTUP:.s=.o)
SRCS_OBJS = $(SRCS:.c=.o)

# add output directories for building
TEMP_DIR = ./temp
OUT_DIR  = ./out

# Magic for stm32f4...

.PHONY: clean flash 

all: $(PROJ_NAME).bin

%.o : %.c
	@echo "[Compiling... File Name is $^]"
	@mkdir -p ./temp
	$(CC) $(CFLAGS) $(INCLUDE) $(DEFS) -c $< -o $(TEMP_DIR)/$(notdir $@) 

%.o : %.s
	@echo "[Assembling... File Name is $^]"
	@mkdir -p ./temp 
	$(AS) $(AFLAGS) $< -o $(TEMP_DIR)/$(notdir $@) 

$(PROJ_NAME).elf: $(SRCS_OBJS) $(STARTUP_OBJS)
	@echo "[Linking... File Name is $^]"
	@echo "[Generating... File Name is $(OUT_DIR)/$(PROJ_NAME).map]"
	@mkdir -p ./out
	$(CC) $(CFLAGS) $(LFLAGS) $(foreach file, $(notdir $^), $(TEMP_DIR)/$(file)) -o $(OUT_DIR)/$@ -Wl,-Map=$(OUT_DIR)/$(PROJ_NAME).map

$(PROJ_NAME).bin: $(PROJ_NAME).elf
	$(OBJCOPY) -O binary $(OUT_DIR)/$< $(OUT_DIR)/$@
	@echo "[Generating... File Name is $(OUT_DIR)/$@]"
	@echo "[Ready to flash to the device!]"

clean:
	rm -rf $(OUT_DIR)/* $(TEMP_DIR)/*

flash:
	st-flash write $(OUT_DIR)/$(PROJ_NAME).bin 0x8000000
