# Makefile for WatOS.
# By Dmitry Kudriavtsev. Some rights reserved

.PHONY: all clean qemu dirs Makefile

# ------- #
# Objects #
# ------- #

OBJS	=  Kernel.o kstdlib.o Console.o boot.o cpuid.o SerialConsole.o

# --------- #
# Variables #
# --------- #

ARCHITECTURE	= i386

SYSROOT			= ../..
USR_DIR			= $(SYSROOT)/usr
#SRC_DIR			= $(SYSROOT)/usr/src
SRC_DIR			= .
OBJ_DIR			= $(SRC_DIR)/obj
ARCH			= $(SRC_DIR)/arch/$(ARCHITECTURE)
COMMON_DIR		= $(SRC_DIR)/common
DRIVERS_DIR		= $(SRC_DIR)/drivers
OUT_DIR			= $(SYSROOT)/boot

VPATH			= $(COMMON_DIR):$(ARCH):$(DRIVERS_DIR):$(subst ' ',':',$(wildcard $(DRIVERS_DIR)/*))

CROSS_BIN		= 
CC				= i686-elf-gcc
CXX				= i686-elf-g++
AS				= i686-elf-as
QEMU			= qemu-system-i386

ASFLAGS			=
COMMONFREEFLAGS	= -g -O0 -Wall -Wextra -pedantic -ffreestanding -I$(SRC_DIR) -I$(SRC_DIR)/drivers -I$(SRC_DIR)/common -I$(SRC_DIR)/arch/$(ARCHITECTURE) -Wno-pointer-arith -Wno-write-strings -fno-threadsafe-statics -march=i686 -mtune=znver1
CFREEFLAGS		= $(COMMONFREEFLAGS) -std=c17
CXXFREEFLAGS	= $(COMMONFREEFLAGS) -std=c++17 -fno-exceptions -fno-rtti

MKDIR_MSG		= " MKDIR	"
AS_MSG			= " AS	"
CC_MSG			= " CC	"
CXX_MSG			= " CXX	"
QEMU_MSG		= " QEMU	"
RM_MSG			= " RM	"
INFO_MSG		= " INFO	"
FAIL_MSG		= " FAIL	"
NYI_MSG			= " NYI 	"

OUTPUT_NAME		= $(OUT_DIR)/myos.bin

# ------------------------- #
# Compilation - Don't touch #
# ------------------------- #

OBJS_K	= $(patsubst %.o,$(OBJ_DIR)/%.o,$(OBJS))

all: dirs image test

dirs: $(OBJ_DIR)/ $(OUT_DIR)/

obj/%.o: %.cpp
	@echo $(CXX_MSG) $<
	@$(CXX) -c $< -o $@ $(CXXFREEFLAGS)

obj/%.o: %.c
	@echo $(CC_MSG) $<
	@$(CC) -c $< -o $@ $(CFREEFLAGS)

obj/%.o: %.s
	@echo $(AS_MSG) $<
	@$(AS) $< -o $@ $(ASFLAGS)

%/:
	@echo $(MKDIR_MSG) $@
	@mkdir -p $@

userspace:
	@echo $(NYI_MSG) userspace not yet implemented

image: $(OBJS_K)
	@echo $(CC_MSG) $(OBJ_DIR)/Kernel.o
	@$(CC) -T $(ARCH)/linker.ld -o $(OUTPUT_NAME) $(COMMONFREEFLAGS) -nostdlib $(OBJS_K) -lgcc

	@echo $(INFO_MSG) Finished. Kernel is at $(OUTPUT_NAME)

test: image
	@grub-file --is-x86-multiboot $(OUTPUT_NAME) || (echo $(FAIL_MSG) grub-file $$?; exit 1)

clean:
	@echo $(RM_MSG) $(OBJ_DIR)/
	@rm -rvf $(OBJ_DIR)

	@echo $(RM_MSG) $(OUT_DIR)/
	@rm -rvf $(OUT_DIR)

qemu: all
	@echo $(QEMU_MSG) $(OUTPUT_NAME)
	@$(QEMU) -kernel $(OUTPUT_NAME)
qemu-debug: all
	@echo $(QEMU_MSG) [DEBUG] $(OUTPUT_NAME)
	@$(QEMU) -s -S -kernel $(OUTPUT_NAME)
