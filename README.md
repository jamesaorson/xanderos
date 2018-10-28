# tree/master/13-kernel-barebonesXanderOS
Following https://github.com/cfenollosa/os-tutorial

# Environment setup

Required packages
-----------------

First, install the required packages. On linux, use your package distribution. On a Mac, [install brew](http://brew.sh/) if
you didn't do it on lesson 00, and get those packages with `brew install`

- gmp
- mpfr
- libmpc
- gcc

Yes, we will need `gcc` to build our cross-compiled `gcc`, especially on a Mac where gcc has been deprecated for `clang`

Once installed, find where your packaged gcc is (remember, not clang) and export it. For example:

```
export CC=/usr/bin/gcc
export LD=/usr/bin/gcc
```

We will need to build binutils and a cross-compiled gcc, and we will put them into `/usr/local/i386elfgcc`, so
let's export some paths now. Feel free to change them to your liking.

```
export PREFIX="/usr/local/i386elfgcc"
export TARGET=i386-elf
export PATH="$PREFIX/bin:$PATH"
```

binutils
--------

Remember: always be careful before pasting walls of text from the internet. I recommend copying line by line.

```sh
mkdir /tmp/src
cd /tmp/src
curl -O http://ftp.gnu.org/gnu/binutils/binutils-2.31.tar.gz # If the link 404's, look for a more recent version
tar xf binutils-2.31.tar.gz
mkdir binutils-build
cd binutils-build
../binutils-2.31/configure --target=$TARGET --enable-interwork --enable-multilib --disable-nls --disable-werror --prefix=$PREFIX 2>&1 | tee configure.log
make all install 2>&1 | tee make.log
```

gcc
---
```sh
cd /tmp/src
curl -O http://mirror.bbln.org/gcc/releases/gcc-8.2.0/gcc-8.2.0.tar.bz2
tar xf gcc-8.2.0.tar.bz2
mkdir gcc-build
cd gcc-build
../gcc-8.2.0/configure --target=$TARGET --prefix="$PREFIX" --disable-nls --disable-libssp --enable-languages=c --without-headers
make all-gcc 
make all-target-libgcc 
make install-gcc 
make install-target-libgcc 
```

That's it! You should have all the GNU binutils and the compiler at `/usr/local/i386elfgcc/bin`, prefixed by `i386-elf-` to avoid
collisions with your system's compiler and binutils.

You may want to add the `$PATH` to your `.bashrc`. From now on, on this tutorial, we will explicitly use the prefixes when using
the cross-compiled gcc.

GDB
---

Furthermore, since from now on we will use mostly C to code, we'll take advantage of qemu's
ability to open a connection to gdb. First, let's install a cross-compiled `gdb` since
OSX uses `lldb` which is not compatible with the ELF file format (neither is the `gdb` available
on Homebrew's repos)

```sh
cd /tmp/src
curl -O http://ftp.rediris.es/mirror/GNU/gdb/gdb-8.2.tar.gz
tar xf gdb-8.2.tar.gz
mkdir gdb-build
cd gdb-build
export PREFIX="/usr/local/i386elfgcc"
export TARGET=i386-elf
../gdb-7.8/configure --target="$TARGET" --prefix="$PREFIX" --program-prefix=i386-elf-
make
make install
```

Check out the Makefile target `make debug`. This target uses builds `kernel.elf`, which
is an object file (not binary) with all the symbols we generated on the kernel, thanks to
the `-g` flag on gcc.