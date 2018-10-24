build:
	i386-elf-gcc -ffreestanding -c function.c -o function.o
	i386-elf-ld -o function.bin -Ttext 0x0 --oformat binary function.o

	i386-elf-gcc -ffreestanding -c functioncalls.c -o functioncalls.o
	i386-elf-ld -o functioncalls.bin -Ttext 0x0 --oformat binary functioncalls.o

	i386-elf-gcc -ffreestanding -c localvars.c -o localvars.o
	i386-elf-ld -o localvars.bin -Ttext 0x0 --oformat binary localvars.o
	
	i386-elf-gcc -ffreestanding -c pointers.c -o pointers.o
	i386-elf-ld -o pointers.bin -Ttext 0x0 --oformat binary pointers.o