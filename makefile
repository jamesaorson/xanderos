build:
	nasm -f bin src/boot_main.asm -o dist/boot.bin

32_build:
	nasm -f bin src/32_bit_main.asm -o dist/32_boot.bin

run:
	qemu-system-x86_64 dist/boot.bin -boot c

32_run:
	qemu-system-x86_64 dist/32_boot.bin