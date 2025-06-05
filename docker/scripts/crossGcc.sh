#!/bin/bash
#set -e

export PREFIX="$HOME/opt/cross"
export TARGET=i386-elf
export PATH="$PREFIX/bin:$PATH"


cd $HOME/src/gcc
./contrib/download_prerequisites
cd $HOME/src/
mkdir build-gcc
cd build-gcc
../gcc/configure --target=$TARGET --prefix="$PREFIX" --with-sysroot="$PREFIX/$TARGET" --disable-nls --enable-languages=c --without-headers --disable-hosted-libstdcxx
make all-gcc -j8
make all-target-libgcc -j8
#make all-target-libstdc++-v3
make install-target-libgcc -j8
make install-gcc -j8
#make install-target-libstdc++-v3
