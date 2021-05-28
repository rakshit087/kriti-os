C_SOURCES = $(wildcard kernel/*.c kernel/include/*.c)
HEADERS = $(wildcard kernel/*.h kernel/include/*.h)
OBJ = ${C_SOURCES:.c=.o}

CC = i386elf-gcc/bin/i386-elf-gcc
LD = i386elf-gcc/bin/i386-elf-ld

CFLAGS = -g

boot.img: bootloader/boot.bin bootloader/loader.bin kernel.bin
	dd if=bootloader/boot.bin of=boot.img bs=512 count=1 conv=notrunc
	dd if=bootloader/loader.bin of=boot.img bs=512 count=5 seek=1 conv=notrunc
	dd if=kernel.bin of=boot.img bs=512 count=100 seek=6 conv=notrunc

kernel.bin: kernel/kernel_entry.o kernel/include/interrupt.o ${OBJ}
	${LD} -o $@ -Ttext 0x10000 $^ --oformat binary

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
	rm -rf kernel/*.o bootloader/*.bin kernel/include/*.o bootloader/*.o 
