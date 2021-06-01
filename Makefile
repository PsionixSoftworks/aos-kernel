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
DRIVER_PATH			:= 	$(KERNEL_PATH)/drivers
MEMORY_PATH			:= 	$(KERNEL_PATH)/memory
SYSTEM_PATH			:= 	$(KERNEL_PATH)/system
X86_PATH			:=	$(KERNEL_PATH)/x86
STDLIB_PATH			:= 	stdlib
MATH_PATH			:= 	math
STRING_PATH			:= 	string

ASM_FILES_IN		:=	asm/boot/boot.S \
						asm/interrupt.asm \
						asm/cpuid.asm
C_FILES_IN			:=	$(INIT_PATH)/main.c \
						$(DRIVER_PATH)/vga.c \
						$(DRIVER_PATH)/i8042.c \
						$(KERNEL_PATH)/tty.c \
						$(KERNEL_PATH)/i386/gdt.c \
						$(KERNEL_PATH)/i386/ldt.c \
						$(KERNEL_PATH)/i386/idt.c \
						$(KERNEL_PATH)/pit.c \
						$(MEMORY_PATH)/mem-util.c \
						$(MEMORY_PATH)/paging.c \
						$(KERNEL_PATH)/cpu.c \
						$(DRIVER_PATH)/keyboard.c \
						$(SYSTEM_PATH)/system.c \
						$(KERNEL_PATH)/mutex.c \
						$(KERNEL_PATH)/assert.c \
						$(KERNEL_PATH)/message-dispatcher.c \
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
						$(STRING_PATH)/append.c
# Put all input files here separated by a '\':
OUTPUT_FILES 		:= 	asm/boot/boot.o	\
						asm/cpuid.o \
						asm/interrupt.o \
						asm/math.o \
						init/main.o \
						kernel/drivers/i8042.o \
						kernel/tty.o \
						kernel/cpu.o \
						kernel/mutex.o \
						kernel/assert.o \
						kernel/drivers/keyboard.o \
						kernel/drivers/vga.o \
						kernel/memory/mem-util.o \
						math/math-util.o \
						kernel/irq.o \
						kernel/isr.o \
						kernel/pic.o \
						kernel/pit.o \
						kernel/system/system.o \
						kernel/i386/gdt.o \
						kernel/i386/ldt.o \
						kernel/i386/idt.o \
						kernel/memory/paging.o \
						stdlib/itoa.o \
						stdlib/free.o \
						stdlib/malloc.o \
						stdlib/memchr.o \
						stdlib/memcmp.o \
						stdlib/memcpy.o \
						stdlib/memmove.o \
						stdlib/memset.o \
						string/str-backspace.o \
						string/strcat.o \
						string/strcmp.o \
						string/strcpy.o \
						string/strlen.o \
						string/strsplit.o \
						string/to-lower.o \
						string/to-upper.o \
						string/strcspn.o \
						string/strspn.o \
						string/strtok.o \
						string/strchr.o \
						string/append.o \
						kernel/message-dispatcher.o

# Compile all of the files into the iso:
.PHONY: all
all: bootloader kernel linker iso clean
	@echo Make has completed compilation of aos-kernel.

# Compile the bootloader files:
bootloader: $(ASM_FILES_IN)
	$(ASM) asm/boot/boot.S -o asm/boot/boot.o
	$(NASM) asm/interrupt.asm -o asm/interrupt.o
	$(NASM)	asm/cpuid.asm -o asm/cpuid.o
	$(NASM) asm/math.asm -o asm/math.o

# Compile the kernel files:
kernel: $(C_FILES_IN)
	$(CC) $(INIT_PATH)/main.c -o $(INIT_PATH)/main.o $(C_FLAGS)
	$(CC) $(KERNEL_PATH)/tty.c -o $(KERNEL_PATH)/tty.o $(C_FLAGS)
	$(CC) $(DRIVER_PATH)/keyboard.c -o $(DRIVER_PATH)/keyboard.o $(C_FLAGS)
	$(CC) $(DRIVER_PATH)/vga.c -o $(DRIVER_PATH)/vga.o $(C_FLAGS)
	$(CC) $(DRIVER_PATH)/i8042.c -o $(DRIVER_PATH)/i8042.o $(C_FLAGS)
	$(CC) $(KERNEL_PATH)/cpu.c -o $(KERNEL_PATH)/cpu.o $(C_FLAGS)
	$(CC) $(KERNEL_PATH)/mutex.c -o $(KERNEL_PATH)/mutex.o $(C_FLAGS)
	$(CC) $(KERNEL_PATH)/irq.c -o $(KERNEL_PATH)/irq.o $(C_FLAGS)
	$(CC) $(KERNEL_PATH)/isr.c -o $(KERNEL_PATH)/isr.o $(C_FLAGS)
	$(CC) $(KERNEL_PATH)/pic.c -o $(KERNEL_PATH)/pic.o $(C_FLAGS)
	$(CC) $(KERNEL_PATH)/pit.c -o $(KERNEL_PATH)/pit.o $(C_FLAGS)
	$(CC) $(KERNEL_PATH)/assert.c -o $(KERNEL_PATH)/assert.o $(C_FLAGS)
	$(CC) $(KERNEL_PATH)/message-dispatcher.c -o $(KERNEL_PATH)/message-dispatcher.o $(C_FLAGS)
	$(CC) $(MATH_PATH)/math-util.c -o $(MATH_PATH)/math-util.o $(C_FLAGS)
	$(CC) $(MEMORY_PATH)/mem-util.c -o $(MEMORY_PATH)/mem-util.o $(C_FLAGS)
	$(CC) $(SYSTEM_PATH)/system.c -o $(SYSTEM_PATH)/system.o $(C_FLAGS)
	$(CC) $(KERNEL_PATH)/i386/gdt.c -o $(KERNEL_PATH)/i386/gdt.o $(C_FLAGS)
	$(CC) $(KERNEL_PATH)/i386/ldt.c -o $(KERNEL_PATH)/i386/ldt.o $(C_FLAGS)
	$(CC) $(KERNEL_PATH)/i386/idt.c -o $(KERNEL_PATH)/i386/idt.o $(C_FLAGS)
	$(CC) $(MEMORY_PATH)/paging.c -o $(MEMORY_PATH)/paging.o $(C_FLAGS)
	$(CC) $(STDLIB_PATH)/itoa.c -o $(STDLIB_PATH)/itoa.o $(C_FLAGS)
	$(CC) $(STDLIB_PATH)/free.c -o $(STDLIB_PATH)/free.o $(C_FLAGS)
	$(CC) $(STDLIB_PATH)/malloc.c -o $(STDLIB_PATH)/malloc.o $(C_FLAGS)
	$(CC) $(STDLIB_PATH)/memchr.c -o $(STDLIB_PATH)/memchr.o $(C_FLAGS)
	$(CC) $(STDLIB_PATH)/memcmp.c -o $(STDLIB_PATH)/memcmp.o $(C_FLAGS)
	$(CC) $(STDLIB_PATH)/memcpy.c -o $(STDLIB_PATH)/memcpy.o $(C_FLAGS)
	$(CC) $(STDLIB_PATH)/memmove.c -o $(STDLIB_PATH)/memmove.o $(C_FLAGS)
	$(CC) $(STDLIB_PATH)/memset.c -o $(STDLIB_PATH)/memset.o $(C_FLAGS)
	$(CC) $(STRING_PATH)/str-backspace.c -o $(STRING_PATH)/str-backspace.o $(C_FLAGS)
	$(CC) $(STRING_PATH)/strcat.c -o $(STRING_PATH)/strcat.o $(C_FLAGS)
	$(CC) $(STRING_PATH)/strcmp.c -o $(STRING_PATH)/strcmp.o $(C_FLAGS)
	$(CC) $(STRING_PATH)/strcpy.c -o $(STRING_PATH)/strcpy.o $(C_FLAGS)
	$(CC) $(STRING_PATH)/strlen.c -o $(STRING_PATH)/strlen.o $(C_FLAGS)
	$(CC) $(STRING_PATH)/strsplit.c -o $(STRING_PATH)/strsplit.o $(C_FLAGS)
	$(CC) $(STRING_PATH)/to-lower.c -o $(STRING_PATH)/to-lower.o $(C_FLAGS)
	$(CC) $(STRING_PATH)/to-upper.c -o $(STRING_PATH)/to-upper.o $(C_FLAGS)
	$(CC) $(STRING_PATH)/strcspn.c -o $(STRING_PATH)/strcspn.o $(C_FLAGS)
	$(CC) $(STRING_PATH)/strspn.c -o $(STRING_PATH)/strspn.o $(C_FLAGS)
	$(CC) $(STRING_PATH)/strtok.c -o $(STRING_PATH)/strtok.o $(C_FLAGS)
	$(CC) $(STRING_PATH)/strchr.c -o $(STRING_PATH)/strchr.o $(C_FLAGS)
	$(CC) $(STRING_PATH)/append.c -o $(STRING_PATH)/append.o $(C_FLAGS)

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
	$(RM) *.o $(BIN) *iso/ *.iso \
	asm/boot/*.o \
	asm/*.o \
	init/*.o \
	kernel/*.o \
	kernel/drivers/*.o \
	kernel/memory/*.o \
	kernel/system/*.o \
	kernel/x86/*.o \
	math/*.o \
	stdlib/*.o \
	string/*.o
