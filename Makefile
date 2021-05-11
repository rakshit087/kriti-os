C_SOURCES = $(wildcard kernel/*.c kernel/drivers/*.c)
HEADERS = $(wildcard kernel/*.h kernel/drivers/*.h)
OBJ = ${C_SOURCES:.c=.o}

CC = i386elf-gcc/bin/i386-elf-gcc
LD = i386elf-gcc/bin/i386-elf-ld

CFLAGS = -g

boot.img: bootloader/bootloader.bin kernel.bin
	cat $^ > os-image.bin
	dd if=os-image.bin of=boot.img bs=512 count=16 conv=notrunc

kernel.bin: kernel/kernel_entry.o ${OBJ}
	${LD} -o $@ -Ttext 0x1000 $^ --oformat binary

run: boot.img
	qemu-system-i386 -drive file=boot.img,format=raw,index=0,media=disk

%.o: %.c ${HEADERS}
	${CC} ${CFLAGS} -ffreestanding -c $< -o $@

%.o: %.asm
	nasm $< -f elf -o $@

%.bin: %.asm
	nasm $< -f bin -o $@

clean:
	rm -rf *.bin *.dis *.o os-image.bin *.elf
	rm -rf kernel/*.o bootloader/*.bin kernel/drivers/*.o bootloader/*.o
