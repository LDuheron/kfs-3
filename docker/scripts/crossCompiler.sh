#!/bin/bash
#set -e

export PREFIX="$HOME/opt/cross"
export TARGET=i386-elf
export PATH="$PREFIX/bin:$PATH"

# Ensure the sysroot directories exist
mkdir -p $PREFIX/$TARGET/usr/include
mkdir -p $PREFIX/$TARGET/usr/lib

# BINUTILS
cd $HOME/src
mkdir build-binutils
cd build-binutils
../binutils/configure --target=$TARGET --prefix="$PREFIX" --with-sysroot="$PREFIX/$TARGET" --disable-nls --disable-werror
make -j8
make install -j8


# The $PREFIX/bin dir _must_ be in the PATH. We did that above.
#which -- $TARGET-as || echo $TARGET-as is not in the PATH
