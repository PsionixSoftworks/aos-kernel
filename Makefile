# Setup commands for building:
CP 							:= 	cp
RM 							:= 	rm -rf
MKDIR 						:= 	mkdir -pv

INCLUDE_PATH				= 	-IAdamantium/kernel/include
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
SOURCE_PATH			= 	Adamantium/kernel/src
BOOTCODE_PATH		:= 	Adamantium/bootcode
ASSEMB_PATH			:= 	Adamantium/assemb
ADAMANTIUM_PATH		:= 	$(SOURCE_PATH)/adamantium
DRIVER_PATH			:= 	$(SOURCE_PATH)/drivers
FILESYSTEM_PATH		:= 	$(SOURCE_PATH)/filesystem
i386_PATH			:= 	$(SOURCE_PATH)/i386
INIT_PATH			:=	$(SOURCE_PATH)/init
LIBC_PATH			:= 	$(SOURCE_PATH)/libc
MATH_PATH			:= 	$(SOURCE_PATH)/math
MEMORY_PATH			:= 	$(SOURCE_PATH)/memory
SYSTEM_PATH			:= 	$(SOURCE_PATH)/system

ASM_FILES_IN		:=	$(BOOTCODE_PATH)/boot.asm \
						$(ASSEMB_PATH)/interrupt.asm \
						$(ASSEMB_PATH)/cpuid.asm \
						$(ASSEMB_PATH)/math.asm \
						$(ASSEMB_PATH)/process.asm
C_FILES_IN			:=	$(INIT_PATH)/main.c \
						$(DRIVER_PATH)/vga.c \
						$(DRIVER_PATH)/i8042.c \
						$(DRIVER_PATH)/tty.c \
						$(DRIVER_PATH)/device.c \
						$(DRIVER_PATH)/driver.c \
						$(FILESYSTEM_PATH)/vfs.c \
						$(FILESYSTEM_PATH)/initrd.c \
						$(i386_PATH)/gdt.c \
						$(i386_PATH)/ldt.c \
						$(i386_PATH)/idt.c \
						$(ADAMANTIUM_PATH)/pit.c \
						$(MEMORY_PATH)/mem-util.c \
						$(MEMORY_PATH)/ordered-array.c \
						$(MEMORY_PATH)/paging.c \
						$(MEMORY_PATH)/linked-list.c \
						$(ADAMANTIUM_PATH)/cpu.c \
						$(ADAMANTIUM_PATH)/rtc.c \
						$(DRIVER_PATH)/keyboard.c \
						$(ADAMANTIUM_PATH)/mutex.c \
						$(ADAMANTIUM_PATH)/assert.c \
						$(ADAMANTIUM_PATH)/task.c \
						$(ADAMANTIUM_PATH)/irq.c \
						$(ADAMANTIUM_PATH)/isr.c \
						$(ADAMANTIUM_PATH)/pic.c \
						$(LIBC_PATH)/itoa.c \
						$(LIBC_PATH)/free.c \
						$(LIBC_PATH)/ftoa.c \
						$(LIBC_PATH)/malloc.c \
						$(LIBC_PATH)/memchr.c \
						$(LIBC_PATH)/memcmp.c \
						$(LIBC_PATH)/memcpy.c \
						$(LIBC_PATH)/memmove.c \
						$(LIBC_PATH)/memset.c \
						$(LIBC_PATH)/getchar.c \
						$(LIBC_PATH)/str-backspace.c \
						$(LIBC_PATH)/strcat.c \
						$(LIBC_PATH)/strcmp.c \
						$(LIBC_PATH)/strcpy.c \
						$(LIBC_PATH)/strlen.c \
						$(LIBC_PATH)/strsplit.c \
						$(LIBC_PATH)/to-lower.c \
						$(LIBC_PATH)/to-upper.c \
						$(LIBC_PATH)/strcspn.c \
						$(LIBC_PATH)/strspn.c \
						$(LIBC_PATH)/strtok.c \
						$(LIBC_PATH)/strchr.c \
						$(LIBC_PATH)/append.c \
						$(ADAMANTIUM_PATH)/procmgr.c \
						$(SYSTEM_PATH)/portio.c

# Put all input files here separated by a '\':
OUTPUT_FILES 		:= 	boot.o	\
						cpuid.o \
						interrupt.o \
						math.o \
						process.o \
						main.o \
						i8042.o \
						tty.o \
						device.o \
						driver.o \
						vfs.o \
						initrd.o \
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
						rtc.o \
						paging.o \
						linked-list.o \
						ordered-array.o \
						itoa.o \
						free.o \
						ftoa.o \
						malloc.o \
						memchr.o \
						memcmp.o \
						memcpy.o \
						memmove.o \
						memset.o \
						putchar.o \
						puts.o \
						printf.o \
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
	$(NASM) $(BOOTCODE_PATH)/boot.asm -o boot.o
	$(NASM) $(ASSEMB_PATH)/interrupt.asm -o interrupt.o
	$(NASM)	$(ASSEMB_PATH)/cpuid.asm -o cpuid.o
	$(NASM) $(ASSEMB_PATH)/math.asm -o math.o
	$(NASM) $(ASSEMB_PATH)/process.asm -o process.o

# Compile the kernel files:
kernel: $(C_FILES_IN)
	$(CC) $(INIT_PATH)/main.c -o main.o $(C_FLAGS)
	$(CC) $(DRIVER_PATH)/tty.c -o tty.o $(C_FLAGS)
	$(CC) $(DRIVER_PATH)/keyboard.c -o keyboard.o $(C_FLAGS)
	$(CC) $(DRIVER_PATH)/vga.c -o vga.o $(C_FLAGS)
	$(CC) $(DRIVER_PATH)/i8042.c -o i8042.o $(C_FLAGS)
	$(CC) $(DRIVER_PATH)/device.c -o device.o $(C_FLAGS)
	$(CC) $(DRIVER_PATH)/driver.c -o driver.o $(C_FLAGS)
	$(CC) $(FILESYSTEM_PATH)/vfs.c -o vfs.o $(C_FLAGS)
	$(CC) $(FILESYSTEM_PATH)/initrd.c -o initrd.o $(C_FLAGS)
	$(CC) $(ADAMANTIUM_PATH)/cpu.c -o cpu.o $(C_FLAGS)
	$(CC) $(ADAMANTIUM_PATH)/mutex.c -o mutex.o $(C_FLAGS)
	$(CC) $(ADAMANTIUM_PATH)/irq.c -o irq.o $(C_FLAGS)
	$(CC) $(ADAMANTIUM_PATH)/isr.c -o isr.o $(C_FLAGS)
	$(CC) $(ADAMANTIUM_PATH)/pic.c -o pic.o $(C_FLAGS)
	$(CC) $(ADAMANTIUM_PATH)/pit.c -o pit.o $(C_FLAGS)
	$(CC) $(ADAMANTIUM_PATH)/assert.c -o assert.o $(C_FLAGS)
	$(CC) $(ADAMANTIUM_PATH)/task.c -o task.o $(C_FLAGS)
	$(CC) $(ADAMANTIUM_PATH)/rtc.c -o rtc.o $(C_FLAGS)
	$(CC) $(MATH_PATH)/math-util.c -o math-util.o $(C_FLAGS)
	$(CC) $(MEMORY_PATH)/mem-util.c -o mem-util.o $(C_FLAGS)
	$(CC) $(MEMORY_PATH)/ordered-array.c -o ordered-array.o $(C_FLAGS)
	$(CC) $(i386_PATH)/gdt.c -o gdt.o $(C_FLAGS)
	$(CC) $(i386_PATH)/ldt.c -o ldt.o $(C_FLAGS)
	$(CC) $(i386_PATH)/idt.c -o idt.o $(C_FLAGS)
	$(CC) $(MEMORY_PATH)/paging.c -o paging.o $(C_FLAGS)
	$(CC) $(MEMORY_PATH)/linked-list.c -o linked-list.o $(C_FLAGS)
	$(CC) $(LIBC_PATH)/itoa.c -o itoa.o $(C_FLAGS)
	$(CC) $(LIBC_PATH)/free.c -o free.o $(C_FLAGS)
	$(CC) $(LIBC_PATH)/ftoa.c -o ftoa.o $(C_FLAGS)
	$(CC) $(LIBC_PATH)/malloc.c -o malloc.o $(C_FLAGS)
	$(CC) $(LIBC_PATH)/memchr.c -o memchr.o $(C_FLAGS)
	$(CC) $(LIBC_PATH)/memcmp.c -o memcmp.o $(C_FLAGS)
	$(CC) $(LIBC_PATH)/memcpy.c -o memcpy.o $(C_FLAGS)
	$(CC) $(LIBC_PATH)/memmove.c -o memmove.o $(C_FLAGS)
	$(CC) $(LIBC_PATH)/memset.c -o memset.o $(C_FLAGS)
	$(CC) $(LIBC_PATH)/putchar.c -o putchar.o $(C_FLAGS)
	$(CC) $(LIBC_PATH)/puts.c -o puts.o $(C_FLAGS)
	$(CC) $(LIBC_PATH)/printf.c -o printf.o $(C_FLAGS)
	$(CC) $(LIBC_PATH)/getchar.c -o getchar.o $(C_FLAGS)
	$(CC) $(LIBC_PATH)/str-backspace.c -o str-backspace.o $(C_FLAGS)
	$(CC) $(LIBC_PATH)/strcat.c -o strcat.o $(C_FLAGS)
	$(CC) $(LIBC_PATH)/strcmp.c -o strcmp.o $(C_FLAGS)
	$(CC) $(LIBC_PATH)/strcpy.c -o strcpy.o $(C_FLAGS)
	$(CC) $(LIBC_PATH)/strlen.c -o strlen.o $(C_FLAGS)
	$(CC) $(LIBC_PATH)/strsplit.c -o strsplit.o $(C_FLAGS)
	$(CC) $(LIBC_PATH)/to-lower.c -o to-lower.o $(C_FLAGS)
	$(CC) $(LIBC_PATH)/to-upper.c -o to-upper.o $(C_FLAGS)
	$(CC) $(LIBC_PATH)/strcspn.c -o strcspn.o $(C_FLAGS)
	$(CC) $(LIBC_PATH)/strspn.c -o strspn.o $(C_FLAGS)
	$(CC) $(LIBC_PATH)/strtok.c -o strtok.o $(C_FLAGS)
	$(CC) $(LIBC_PATH)/strchr.c -o strchr.o $(C_FLAGS)
	$(CC) $(LIBC_PATH)/append.c -o append.o $(C_FLAGS)
	$(CC) $(ADAMANTIUM_PATH)/procmgr.c -o procmgr.o $(C_FLAGS)
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
	$(RM) *.o $(BIN) *iso/ *.iso
clean:
	$(RM) *.o $(BIN) *iso/ *.iso
