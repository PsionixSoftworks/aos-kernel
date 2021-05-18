# Setup commands for building:
CP 							:= 	cp
RM 							:= 	rm -rf
MKDIR 						:= 	mkdir -pv

INCLUDE_PATH				= 	-Iinclude
DEFAULT_INCLUDE_PATH		= 	$(INCLUDE_PATH)
LINKER						= 	ld -m elf_i386 -T linker.ld
NASM						=	nasm -f elf32
ASM							= 	i686-elf-as
CC							= 	i686-elf-gcc -c
CCPP						=	i686-elf-g++ -c
CPP_FLAGS					= 	-ffreestanding -nostdlib -Wall -Wextra $(DEFAULT_INCLUDE_PATH)
C_FLAGS						= 	-std=gnu99 $(CPP_FLAGS)


# Set the basic paths and compilation:
BIN 						:= 	aos32
CFG 						:= 	grub.cfg
ISO_PATH 					:= 	iso
ISO_FILE					:= 	AdamantineOS.iso
ISO_OUTPUT_PATH				:= 	build/
ISO_OUTPUT					:= 	$(ISO_OUTPUT_PATH)/$(ISO_FILE)
BOOT_PATH					:= 	$(ISO_PATH)/boot
GRUB_PATH					:= 	$(BOOT_PATH)/grub

# Setup OS specific directories:
ADAMANTINE_PATH				:= 	adamantine
ASSEMB_PATH					:= 	asm
FS_PATH						:=	filesys
INIT_PATH					:= 	security
KERNEL_PATH					:= 	kernel
DRIVER_PATH					:= 	$(KERNEL_PATH)/drivers
MEMORY_PATH					:= 	$(KERNEL_PATH)/memory
SYSTEM_PATH					:= 	$(KERNEL_PATH)/system
X86_PATH					:=	$(KERNEL_PATH)/x86
STDLIB_PATH					:= 	stdlib
MAIN_PATH					:= 	main
SECURITY_PATH				:=	security
TOOL_PATH					:= 	tool
USER_PATH					:= 	user
MATH_PATH					:= 	math
STRING_PATH					:= 	string

ASM_FILES_IN				:=	$(ASSEMB_PATH)/boot/boot.S \
								$(ASSEMB_PATH)/descriptors.S \
								$(ASSEMB_PATH)/interrupt.asm \
								$(ASSEMB_PATH)/cpuid.asm \
								$(ASSEMB_PATH)/math.asm
C_FILES_IN					:=	$(KERNEL_PATH)/adamantine.c	\
								$(KERNEL_PATH)/cpu.c \
								$(KERNEL_PATH)/mutex.c \
								$(KERNEL_PATH)/assert.c \
								$(KERNEL_PATH)/message-dispatcher.c \
								$(SYSTEM_PATH)/cursor.c \
								$(DRIVER_PATH)/keyboard.c \
								$(DRIVER_PATH)/vga.c \
								$(MEMORY_PATH)/mem-util.c		\
								$(SYSTEM_PATH)/io.c	\
								$(KERNEL_PATH)/irq.c \
								$(KERNEL_PATH)/isr.c \
								$(KERNEL_PATH)/pic.c \
								$(KERNEL_PATH)/pit.c \
								$(SYSTEM_PATH)/system.c	\
								$(SYSTEM_PATH)/terminal.c \
								$(X86_PATH)/descriptor-tables.c	\
								$(MEMORY_PATH)/paging.c	\
								$(MATH_PATH)/math-util.c \
								$(STDLIB_PATH)/itoa.c \
								$(STDLIB_PATH)/free.c \
								$(STDLIB_PATH)/malloc.c \
								$(STDLIB_PATH)/memchr.c \
								$(STDLIB_PATH)/memcmp.c \
								$(STDLIB_PATH)/memcpy.c \
								$(STDLIB_PATH)/memmove.c \
								$(STDLIB_PATH)/memset.c \
								$(STRING_PATH)/str-backspace.c \
								$(STRING_PATH)/strcat.c \
								$(STRING_PATH)/strcmp.c \
								$(STRING_PATH)/strcpy.c \
								$(STRING_PATH)/strlen.c \
								$(STRING_PATH)/strsplit.c \
								$(STRING_PATH)/to-lower.c \
								$(STRING_PATH)/to-upper.c \
								$(STRING_PATH)/strcspn.c \
								$(STRING_PATH)/strspn.c \
								$(STRING_PATH)/strtok.c \
								$(STRING_PATH)/strchr.c 

# Put all input files here separated by a '\':
OUTPUT_FILES 				:= 	boot.o			\
								descriptors.o	\
								interrupt.o		\
								math.o \
								adamantine.o	\
								cpuid.o			\
								cpu.o			\
								mutex.o			\
								assert.o \
								cursor.o \
								keyboard.o		\
								vga.o \
								mem-util.o		\
								math-util.o		\
								io.o			\
								irq.o			\
								isr.o			\
								pic.o			\
								pit.o			\
								system.o		\
								terminal.o		\
								descriptor-tables.o \
								paging.o		\
								itoa.o			\
								free.o \
								malloc.o \
								memchr.o \
								memcmp.o \
								memcpy.o \
								memmove.o \
								memset.o \
								str-backspace.o \
								strcat.o \
								strcmp.o \
								strcpy.o \
								strlen.o \
								strsplit.o \
								to-lower.o \
								to-upper.o \
								strcspn.o \
								strspn.o \
								strtok.o \
								strchr.o \
								message-dispatcher.o

# AOS_OUTPUT					:= 	$(AOS_DIR)/Adamantine.o	\
# 								$(AOS_DIR)/Registry.o	

# Compile all of the files into the iso:
.PHONY: all
all: bootloader kernel linker iso
	@echo Make has completed compilation of AdamantineOS Kernel.

# Compile the bootloader files:
bootloader: $(ASM_FILES_IN)
	$(NASM) $(ASSEMB_PATH)/boot/boot.asm -o boot.o
	$(ASM) $(ASSEMB_PATH)/descriptors.S			-o descriptors.o
	$(NASM) $(ASSEMB_PATH)/interrupt.asm			-o interrupt.o
	$(NASM)	$(ASSEMB_PATH)/cpuid.asm				-o cpuid.o
	$(NASM) $(ASSEMB_PATH)/math.asm -o math.o

# Compile the kernel files:
kernel: $(C_FILES_IN)
	$(CC) $(KERNEL_PATH)/adamantine.c -o adamantine.o $(C_FLAGS)
	$(CC) $(DRIVER_PATH)/keyboard.c -o keyboard.o $(C_FLAGS)
	$(CC) $(DRIVER_PATH)/vga.c -o vga.o $(C_FLAGS)
	$(CC) $(KERNEL_PATH)/cpu.c -o cpu.o $(C_FLAGS)
	$(CC) $(KERNEL_PATH)/mutex.c -o mutex.o $(C_FLAGS)
	$(CC) $(KERNEL_PATH)/irq.c -o irq.o $(C_FLAGS)
	$(CC) $(KERNEL_PATH)/isr.c -o isr.o $(C_FLAGS)
	$(CC) $(KERNEL_PATH)/pic.c -o pic.o $(C_FLAGS)
	$(CC) $(KERNEL_PATH)/pit.c -o pit.o $(C_FLAGS)
	$(CC) $(KERNEL_PATH)/assert.c -o assert.o $(C_FLAGS)
	$(CC) $(KERNEL_PATH)/message-dispatcher.c -o message-dispatcher.o $(C_FLAGS)
	$(CC) $(MATH_PATH)/math-util.c -o math-util.o $(C_FLAGS)
	$(CC) $(MEMORY_PATH)/mem-util.c -o mem-util.o $(C_FLAGS)
	$(CC) $(SYSTEM_PATH)/io.c -o io.o $(C_FLAGS)
	$(CC) $(SYSTEM_PATH)/system.c -o system.o $(C_FLAGS)
	$(CC) $(SYSTEM_PATH)/terminal.c -o terminal.o $(C_FLAGS)
	$(CC) $(SYSTEM_PATH)/cursor.c -o cursor.o $(C_FLAGS)
	$(CC) $(X86_PATH)/descriptor-tables.c -o descriptor-tables.o $(C_FLAGS)
	$(CC) $(MEMORY_PATH)/paging.c -o paging.o $(C_FLAGS)
	$(CC) $(STDLIB_PATH)/itoa.c -o itoa.o $(C_FLAGS)
	$(CC) $(STDLIB_PATH)/free.c -o free.o $(C_FLAGS)
	$(CC) $(STDLIB_PATH)/malloc.c -o malloc.o $(C_FLAGS)
	$(CC) $(STDLIB_PATH)/memchr.c -o memchr.o $(C_FLAGS)
	$(CC) $(STDLIB_PATH)/memcmp.c -o memcmp.o $(C_FLAGS)
	$(CC) $(STDLIB_PATH)/memcpy.c -o memcpy.o $(C_FLAGS)
	$(CC) $(STDLIB_PATH)/memmove.c -o memmove.o $(C_FLAGS)
	$(CC) $(STDLIB_PATH)/memset.c -o memset.o $(C_FLAGS)
	$(CC) $(STRING_PATH)/str-backspace.c -o str-backspace.o $(C_FLAGS)
	$(CC) $(STRING_PATH)/strcat.c -o strcat.o $(C_FLAGS)
	$(CC) $(STRING_PATH)/strcmp.c -o strcmp.o $(C_FLAGS)
	$(CC) $(STRING_PATH)/strcpy.c -o strcpy.o $(C_FLAGS)
	$(CC) $(STRING_PATH)/strlen.c -o strlen.o $(C_FLAGS)
	$(CC) $(STRING_PATH)/strsplit.c -o strsplit.o $(C_FLAGS)
	$(CC) $(STRING_PATH)/to-lower.c -o to-lower.o $(C_FLAGS)
	$(CC) $(STRING_PATH)/to-upper.c -o to-upper.o $(C_FLAGS)
	$(CC) $(STRING_PATH)/strcspn.c -o strcspn.o $(C_FLAGS)
	$(CC) $(STRING_PATH)/strspn.c -o strspn.o $(C_FLAGS)
	$(CC) $(STRING_PATH)/strtok.c -o strtok.o $(C_FLAGS)
	$(CC) $(STRING_PATH)/strchr.c -o strchr.o $(C_FLAGS)
	 
# Link all input files into one file:
linker: linker.ld $(OUTPUT_FILES)
	$(LINKER) -o $(BIN) $(OUTPUT_FILES)

# Build the Kernel iso:
iso: kernel
	$(MKDIR) $(GRUB_PATH)
	$(CP) $(BIN) $(BOOT_PATH)
	$(CP) $(CFG) $(GRUB_PATH)
	grub-file --is-x86-multiboot $(BOOT_PATH)/$(BIN)
	grub-mkrescue -o $(ISO_FILE) $(ISO_PATH)
	$(MKDIR) $(ISO_OUTPUT_PATH)
	$(CP) $(ISO_FILE) $(ISO_OUTPUT)
	qemu-system-i386 -machine ubuntu -drive format=raw,file=$(ISO_FILE)
	$(RM) *.o $(BIN) *iso/ *.iso

# This might need to get updated...
.PHONY: clean
clean:
	$(RM) *.o $(BIN) *iso/ *.iso
