all: boot

boot.bin:
	nasm boot_sector.asm -f bin -o boot_sector.bin

boot: boot.bin
	qemu-system-i386 -drive format=raw,file=boot_sector.bin
