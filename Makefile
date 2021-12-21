# Setup commands for building:
CP 							:= 	cp
RM 							:= 	rm -rf
MKDIR 						:= 	mkdir -pv

INCLUDE_PATH				= 	-Iinclude
LINKER						= 	ld -m elf_i386 -T linker.ld
NASM						=	nasm -f elf32
ASM							= 	i686-elf-as
CC							= 	i686-elf-gcc -c
CCPP						=	i686-elf-g++ -c
CPP_FLAGS					= 	-ffreestanding -nostdlib -Wall -Wextra $(INCLUDE_PATH)
C_FLAGS						= 	-std=gnu99 $(CPP_FLAGS)


# Set the basic paths and compilation:
BIN 						:= 	aos32
CFG 						:= 	grub.cfg
ISO_PATH 					:= 	iso
ISO_FILE					:= 	aos-kernel.iso
ISO_OUTPUT_PATH				:= 	build/
ISO_OUTPUT					:= 	$(ISO_OUTPUT_PATH)/$(ISO_FILE)
BOOT_PATH					:= 	$(ISO_PATH)/boot
GRUB_PATH					:= 	$(BOOT_PATH)/grub

# Setup OS specific directories:
ADAMANTINE_PATH		:= 	adamantine
ASSEMB_PATH			:= 	asm
INIT_PATH			:=	init
KERNEL_PATH			:= 	kernel
DRIVER_PATH			:= 	drivers
MEMORY_PATH			:= 	memory
SYSTEM_PATH			:= 	system
STDLIB_PATH			:= 	stdlib
STDIO_PATH			:= 	stdio
MATH_PATH			:= 	math
STRING_PATH			:= 	string
SYSTEM_PATH			:= 	system

ASM_FILES_IN		:=	$(ASSEMB_PATH)/boot/boot.asm \
						$(ASSEMB_PATH)/interrupt.asm \
						$(ASSEMB_PATH)/cpuid.asm 
C_FILES_IN			:=	$(INIT_PATH)/main.c \
						$(DRIVER_PATH)/vga.c \
						$(DRIVER_PATH)/i8042.c \
						$(DRIVER_PATH)/tty.c \
						$(DRIVER_PATH)/device.c \
						$(DRIVER_PATH)/driver.c \
						$(KERNEL_PATH)/i386/gdt.c \
						$(KERNEL_PATH)/i386/ldt.c \
						$(KERNEL_PATH)/i386/idt.c \
						$(KERNEL_PATH)/pit.c \
						$(MEMORY_PATH)/mem-util.c \
						$(MEMORY_PATH)/ordered-array.c \
						$(MEMORY_PATH)/paging.c \
						$(KERNEL_PATH)/cpu.c \
						$(DRIVER_PATH)/keyboard.c \
						$(KERNEL_PATH)/mutex.c \
						$(KERNEL_PATH)/assert.c \
						$(KERNEL_PATH)/task.c \
						$(KERNEL_PATH)/irq.c \
						$(KERNEL_PATH)/isr.c \
						$(KERNEL_PATH)/pic.c \
						$(STDLIB_PATH)/itoa.c \
						$(STDLIB_PATH)/free.c \
						$(STDLIB_PATH)/malloc.c \
						$(STDLIB_PATH)/memchr.c \
						$(STDLIB_PATH)/memcmp.c \
						$(STDLIB_PATH)/memcpy.c \
						$(STDLIB_PATH)/memmove.c \
						$(STDLIB_PATH)/memset.c \
						$(STDIO_PATH)/getchar.c \
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
						$(STRING_PATH)/strchr.c \
						$(STRING_PATH)/append.c \
						$(KERNEL_PATH)/procmgr.c \
						$(SYSTEM_PATH)/portio.c
# Put all input files here separated by a '\':
OUTPUT_FILES 		:= 	boot.o	\
						cpuid.o \
						interrupt.o \
						math.o \
						main.o \
						i8042.o \
						tty.o \
						device.o \
						driver.o \
						cpu.o \
						mutex.o \
						assert.o \
						task.o \
						keyboard.o \
						vga.o \
						mem-util.o \
						math-util.o \
						irq.o \
						isr.o \
						pic.o \
						pit.o \
						gdt.o \
						ldt.o \
						idt.o \
						paging.o \
						ordered-array.o \
						itoa.o \
						free.o \
						malloc.o \
						memchr.o \
						memcmp.o \
						memcpy.o \
						memmove.o \
						memset.o \
						getchar.o \
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
						append.o \
						procmgr.o \
						portio.o

# Compile all of the files into the iso:
.PHONY: all
all: bootloader kernel linker iso
	@echo Make has completed compilation of aos-kernel.

# Compile the bootloader files:
bootloader: $(ASM_FILES_IN)
	$(NASM) $(ASSEMB_PATH)/boot/boot.asm -o boot.o
	$(NASM) $(ASSEMB_PATH)/interrupt.asm -o interrupt.o
	$(NASM)	$(ASSEMB_PATH)/cpuid.asm -o cpuid.o
	$(NASM) $(ASSEMB_PATH)/math.asm -o math.o

# Compile the kernel files:
kernel: $(C_FILES_IN)
	$(CC) $(INIT_PATH)/main.c -o main.o $(C_FLAGS)
	$(CC) $(DRIVER_PATH)/tty.c -o tty.o $(C_FLAGS)
	$(CC) $(DRIVER_PATH)/keyboard.c -o keyboard.o $(C_FLAGS)
	$(CC) $(DRIVER_PATH)/vga.c -o vga.o $(C_FLAGS)
	$(CC) $(DRIVER_PATH)/i8042.c -o i8042.o $(C_FLAGS)
	$(CC) $(DRIVER_PATH)/device.c -o device.o $(C_FLAGS)
	$(CC) $(DRIVER_PATH)/driver.c -o driver.o $(C_FLAGS)
	$(CC) $(KERNEL_PATH)/cpu.c -o cpu.o $(C_FLAGS)
	$(CC) $(KERNEL_PATH)/mutex.c -o mutex.o $(C_FLAGS)
	$(CC) $(KERNEL_PATH)/irq.c -o irq.o $(C_FLAGS)
	$(CC) $(KERNEL_PATH)/isr.c -o isr.o $(C_FLAGS)
	$(CC) $(KERNEL_PATH)/pic.c -o pic.o $(C_FLAGS)
	$(CC) $(KERNEL_PATH)/pit.c -o pit.o $(C_FLAGS)
	$(CC) $(KERNEL_PATH)/assert.c -o assert.o $(C_FLAGS)
	$(CC) $(KERNEL_PATH)/task.c -o task.o $(C_FLAGS)
	$(CC) $(MATH_PATH)/math-util.c -o math-util.o $(C_FLAGS)
	$(CC) $(MEMORY_PATH)/mem-util.c -o mem-util.o $(C_FLAGS)
	$(CC) $(MEMORY_PATH)/ordered-array.c -o ordered-array.o $(C_FLAGS)
	$(CC) $(KERNEL_PATH)/i386/gdt.c -o gdt.o $(C_FLAGS)
	$(CC) $(KERNEL_PATH)/i386/ldt.c -o ldt.o $(C_FLAGS)
	$(CC) $(KERNEL_PATH)/i386/idt.c -o idt.o $(C_FLAGS)
	$(CC) $(MEMORY_PATH)/paging.c -o paging.o $(C_FLAGS)
	$(CC) $(STDLIB_PATH)/itoa.c -o itoa.o $(C_FLAGS)
	$(CC) $(STDLIB_PATH)/free.c -o free.o $(C_FLAGS)
	$(CC) $(STDLIB_PATH)/malloc.c -o malloc.o $(C_FLAGS)
	$(CC) $(STDLIB_PATH)/memchr.c -o memchr.o $(C_FLAGS)
	$(CC) $(STDLIB_PATH)/memcmp.c -o memcmp.o $(C_FLAGS)
	$(CC) $(STDLIB_PATH)/memcpy.c -o memcpy.o $(C_FLAGS)
	$(CC) $(STDLIB_PATH)/memmove.c -o memmove.o $(C_FLAGS)
	$(CC) $(STDLIB_PATH)/memset.c -o memset.o $(C_FLAGS)
	$(CC) $(STDIO_PATH)/getchar.c -o getchar.o $(C_FLAGS)
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
	$(CC) $(STRING_PATH)/append.c -o append.o $(C_FLAGS)
	$(CC) $(KERNEL_PATH)/procmgr.c -o procmgr.o $(C_FLAGS)
	$(CC) $(SYSTEM_PATH)/portio.c -o portio.o $(C_FLAGS)

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
	qemu-system-i386 -soundhw pcspk -machine ubuntu -drive format=raw,file=$(ISO_FILE)
clean:
	$(RM) *.o $(BIN) *iso/ *.iso
