all: boot

boot.bin:
	nasm boot-sector.asm -f bin -o boot-sector.bin

boot: boot.bin
	qemu-system-i386 -drive format=raw,file=boot-sector.bin
