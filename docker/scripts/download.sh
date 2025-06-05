#!/bin/bash
#set -e

# PREPARATION

#echo "building cross compiler..."
#sleep 2
export PREFIX="$HOME/opt/cross"
export TARGET=i386-elf
export PATH="$PREFIX/bin:$PATH"
mkdir -p $HOME/src
cd $HOME/src

## Download and extract binutils and gcc (replace x.y.z with the actual versions)

# Function to get the latest version of a tool
get_latest_version() {
  local tool=$1
  local url=$2
  local pattern=$3

  # Download the directory listing
  wget -qO- $url | grep -oP "$pattern" | sort -V | tail -n1
}

# Get the latest version of binutils
BINUTILS_LATEST_VERSION=$(get_latest_version "binutils" "http://ftp.gnu.org/gnu/binutils/" "binutils-[0-9]+\.[0-9]+")
BINUTILS_LATEST_TAR=$(get_latest_version "binutils" "http://ftp.gnu.org/gnu/binutils/" "binutils-[0-9]+\.[0-9]+\.tar\.gz")
BINUTILS_URL="http://ftp.gnu.org/gnu/binutils/$BINUTILS_LATEST_TAR"

# Get the latest version of gcc
GCC_LATEST_VERSION=$(get_latest_version "gcc" "http://ftp.gnu.org/gnu/gcc/" "gcc-[0-9]+\.[0-9]+\.[0-9]+")
GCC_LATEST="http://ftp.gnu.org/gnu/gcc/$GCC_LATEST_VERSION"
GCC_LATEST_TAR=$(get_latest_version "gcc" "$GCC_LATEST" "gcc-[0-9]+\.[0-9]+\.[0-9]+\.tar\.gz")
GCC_URL=$GCC_LATEST/$GCC_LATEST_TAR

# Download and extract binutils and gcc
wget $BINUTILS_URL
tar -xzf $BINUTILS_LATEST_TAR
rm $BINUTILS_LATEST_TAR
mv $BINUTILS_LATEST_VERSION binutils

wget $GCC_URL
tar -xzf $GCC_LATEST_TAR
rm $GCC_LATEST_TAR
mv $GCC_LATEST_VERSION gcc
