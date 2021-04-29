cd bootloader
nasm bootloader.asm -f bin -o bootloader.bin
mv bootloader.bin ..
cd ..
cd kernel
gcc -ffreestanding -c kernel.c -o kernel.o
ld -o kernel.bin -Ttext 0x0 --oformat binary kernel.o
mv kernel.bin .. 
cd ..
cat bootloader.bin kernel.bin > os-image
dd if=os-image of=boot.img bs=512 count=2 conv=notrunc
rm bootloader.bin
rm kernel.bin