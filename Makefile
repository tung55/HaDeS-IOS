CC = gcc
AS = nasm
LD = ld
# Cờ -fno-pie và -fno-stack-protector cực kỳ quan trọng để không bị crash
CFLAGS = -m32 -ffreestanding -fno-pie -fno-pic -fno-stack-protector -O2 -Wall -Wextra
LDFLAGS = -m elf_i386 -T linker.ld

C_SOURCES = $(wildcard kernel/*.c)
ASM_SOURCES = boot.asm
OBJ = $(C_SOURCES:.c=.o) $(ASM_SOURCES:.asm=.o)

all: myos.iso

kernel/%.o: kernel/%.c
	$(CC) $(CFLAGS) -Iinclude -c $< -o $@

%.o: %.asm
	$(AS) -f elf32 $< -o $@

myos.bin: $(OBJ)
	$(LD) $(LDFLAGS) -o $@ $(OBJ)

# Cấu hình GRUB ép buộc bật đồ họa 1024x768x32
myos.iso: myos.bin
	mkdir -p iso/boot/grub
	cp myos.bin iso/boot/
	echo 'set timeout=0' > iso/boot/grub/grub.cfg
	echo 'insmod all_video' >> iso/boot/grub/grub.cfg
	echo 'set gfxmode=1024x768x32' >> iso/boot/grub/grub.cfg
	echo 'set gfxpayload=keep' >> iso/boot/grub/grub.cfg
	echo 'menuentry "HaDeS/IOS" {' >> iso/boot/grub/grub.cfg
	echo '  multiboot /boot/myos.bin' >> iso/boot/grub/grub.cfg
	echo '  boot' >> iso/boot/grub/grub.cfg
	echo '}' >> iso/boot/grub/grub.cfg
	grub-mkrescue -o myos.iso iso 2>/dev/null

clean:
	rm -f kernel/*.o *.o myos.bin myos.iso
	rm -rf iso
