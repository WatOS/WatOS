.PHONY: all clean

ARCHITECTURE	= i386

SRC_DIR			= src
OBJ_DIR			= $(SRC_DIR)/obj
ARCH			= $(SRC_DIR)/arch/$(ARCHITECTURE)
COMMON_DIR		= $(SRC_DIR)/common
DRIVERS_DIR		= $(SRC_DIR)/drivers
OUT_DIR			= out

CROSS_BIN		= cross/bin
CC				= $(CROSS_BIN)/i686-elf-gcc
CXX				= $(CROSS_BIN)/i686-elf-g++
AS				= $(CROSS_BIN)/i686-elf-as
QEMU			= qemu-system-i386

ASFLAGS			=
COMMONFREEFLAGS	= -O2 -Wall -Wextra -ffreestanding -I$(SRC_DIR)/drivers -I$(SRC_DIR)/common -I$(SRC_DIR)/arch/$(ARCHITECTURE)
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

OUTPUT_NAME		= $(OUT_DIR)/myos.bin

# --------

all: dirs console kernel test

dirs: obj_dir out_dir

obj_dir:
	@mkdir -p $(OBJ_DIR)
	@echo $(MKDIR_MSG) $(OBJ_DIR)

out_dir:
	@mkdir -p $(OUT_DIR)
	@echo $(MKDIR_MSG) $(OUT_DIR)

console:
	@$(CXX) -c $(DRIVERS_DIR)/Console.cpp -o $(OBJ_DIR)/Console.o $(CXXFREEFLAGS)
	@echo $(CXX_MSG) $(DRIVERS_DIR)/Console.cpp

kernel: console
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OUT_DIR)
	@$(AS) $(ARCH)/boot.s -o $(OBJ_DIR)/boot.o $(ASFLAGS)
	@echo $(AS_MSG) $(ARCH)/boot.s

	@$(CXX) -c $(COMMON_DIR)/Kernel.cpp -o $(OBJ_DIR)/Kernel.o $(CXXFREEFLAGS)
	@echo $(CXX_MSG) $(COMMON_DIR)/Kernel.cpp

	@$(CC) -T $(ARCH)/linker.ld -o $(OUTPUT_NAME) -ffreestanding -O2 -nostdlib $(OBJ_DIR)/boot.o $(OBJ_DIR)/Kernel.o $(OBJ_DIR)/Console.o  -lgcc
	@echo $(CC_MSG) $(OBJ_DIR)/boot.o $(OBJ_DIR)/Kernel.o

	@echo $(INFO_MSG) Finished. Kernel is at $(OUTPUT_NAME)

test:
	@grub-file --is-x86-multiboot $(OUTPUT_NAME) || (echo $(FAIL_MSG) grub-file $$?; exit 1)

clean:
	@rm -r $(OBJ_DIR)
	@echo $(RM_MSG) $(OBJ_DIR)/

	@rm -r $(OUT_DIR)
	@echo $(RM_MSG) $(OUT_DIR)/

qemu: all
	@$(QEMU) -kernel $(OUTPUT_NAME)
