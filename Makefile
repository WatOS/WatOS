# Makefile for WatOS.
# By Dmitry Kudriavtsev. Some rights reserved

# Variables

.PHONY: all clean qemu dirs

ARCHITECTURE	= i386

SYSROOT			= sysroot
USR_DIR			= $(SYSROOT)/usr
SRC_DIR			= $(SYSROOT)/usr/src
OBJ_DIR			= $(SRC_DIR)/obj
ARCH			= $(SRC_DIR)/arch/$(ARCHITECTURE)
COMMON_DIR		= $(SRC_DIR)/common
DRIVERS_DIR		= $(SRC_DIR)/drivers
OUT_DIR			= $(SYSROOT)/boot

VPATH			= $(COMMON_DIR):$(ARCH):$(DRIVERS_DIR)

CROSS_BIN		= cross/bin
CC				= $(CROSS_BIN)/i686-elf-gcc
CXX				= $(CROSS_BIN)/i686-elf-g++
AS				= $(CROSS_BIN)/i686-elf-as
QEMU			= qemu-system-i386

ASFLAGS			=
COMMONFREEFLAGS	= -O2 -Wall -Wextra -ffreestanding -I$(SRC_DIR)/drivers -I$(SRC_DIR)/common -I$(SRC_DIR)/arch/$(ARCHITECTURE) -Wno-pointer-arith
CFREEFLAGS		= $(COMMONFREEFLAGS) -std=gnu99
CXXFREEFLAGS	= $(COMMONFREEFLAGS) -std=c++14 -fno-exceptions -fno-rtti

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

# ----------- #
# Compilation #
# ----------- #

OBJS	= Kernel.cpp kstdlib.cpp Console.cpp
OBJS_K	= $(OBJ_DIR)/Kernel.o $(OBJ_DIR)/kstdlib.o $(OBJ_DIR)/Console.o

all: dirs image userspace test

dirs: $(OBJ_DIR)/ $(OUT_DIR)/

%.cpp:
	@echo $(CXX_MSG) $@
	$(CXX) -c $@ -o $(OBJ_DIR)/$(@:.cpp=.o) $(DEPS) $(CXXFREEFLAGS)

%.s:
	@echo $(AS_MSG) $@
	$(AS) $@ -o $(OBJ_DIR)/$(@:.s=.o) $(ASFLAGS)

%/:
	@echo $(MKDIR_MSG) $@
	@mkdir -p $@

userspace:
	@echo $(NYI_MSG) userspace not yet implemented

image: $(OBJS)
	@echo $(CC_MSG) $(OBJ_DIR)/boot.o $(OBJ_DIR)/Kernel.o
	@$(CC) -T $(ARCH)/linker.ld -o $(OUTPUT_NAME) -ffreestanding -O2 -nostdlib $(OBJ_DIR)/boot.o $(OBJS_K) -lgcc

	@echo $(INFO_MSG) Finished. Kernel is at $(OUTPUT_NAME)

test:
	@grub-file --is-x86-multiboot $(OUTPUT_NAME) || (echo $(FAIL_MSG) grub-file $$?; exit 1)

clean:
	@touch $(OBJS)

	@echo $(RM_MSG) $(OBJ_DIR)/
	@rm -rvf $(OBJ_DIR)

	@echo $(RM_MSG) $(OUT_DIR)/
	@rm -rvf $(OUT_DIR)

qemu: all
	@echo $(QEMU_MSG) $(OUTPUT_NAME)
	@$(QEMU) -kernel $(OUTPUT_NAME)
