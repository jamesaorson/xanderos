# $@ = target file
# $< = first dependency
# $^ = all dependencies

C_SOURCES = $(wildcard src/kernel/*.cpp src/drivers/*.cpp src/cpu/*.cpp src/libc/*.cpp)
HEADERS = $(wildcard src/kernel/*.h src/drivers/*.h src/cpu/*.h src/libc/*.h)

# Nice syntax for file extension replacement
OBJ = ${C_SOURCES:.cpp=.o src/cpu/interrupt.o}

# Change this if your cross-compiler is somewhere else
CC = i386-elf-gcc
GDB = i386-elf-gdb

# -g: Use debugging symbols in gcc
CFLAGS = -g -ffreestanding -Wall -Wextra -fno-exceptions -m32 -lstdc++

# First rule is run by default
dist/xanderos.raw: src/boot/sector.bin src/kernel/kernel.bin
	cat $^ > $@

# '--oformat binary' deletes all symbols as a collateral, so we don't need
# to 'strip' them manually on this case
src/kernel/kernel.bin: src/kernel/kernel_entry.o ${OBJ}
	i386-elf-ld -o $@ -Ttext 0x1000 $^ --oformat binary

# Used for debugging purposes
kernel.elf: src/kernel/kernel_entry.o ${OBJ}
	i386-elf-ld -o $@ -Ttext 0x1000 $^ 

run: dist/xanderos.raw
	qemu-system-i386 $< -boot c

# Gets a disk read error
run_from_disk: dist/xanderos.raw
	qemu-system-i386 $< -boot c

run_from_floppy: dist/xanderos.raw
	qemu-system-i386 -fda $<

dist: dist/xanderos.raw
	@ echo Building VDI image of Xanderos...
	@ qemu-img convert -f raw -O vdi dist/xanderos.raw dist/xanderos.vdi
	@ echo Done building VDI image of Xanderos!

	@ echo "\nBuilding VMDK image of Xanderos..."
	@ qemu-img convert -f raw -O vmdk dist/xanderos.raw dist/xanderos.vmdk
	@ echo Done building VMDK image of Xanderos!

# Open the connection to qemu and load our kernel-object file with symbols
debug: dist/xanderos.raw kernel.elf
	qemu-system-i386 -s -fda $< &
	${GDB} -ex "target remote localhost:1234" -ex "symbol-file kernel.elf"

# Generic rules for wildcards
# To make an object, always compile from its .c
%.o: %.cpp ${HEADERS}
	${CC} ${CFLAGS} -c $< -o $@

%.o: %.asm
	nasm $< -f elf -o $@

%.bin: %.asm
	nasm $< -f bin -o $@

clean:
	rm -rf *.bin *.dis *.o dist/xanderos.raw *.elf
	rm -rf src/boot/*.bin src/boot/*.o src/cpu/*.bin src/cpu/*.o src/drivers/*.bin src/drivers/*.o src/kernel/*.bin src/kernel/*.o
