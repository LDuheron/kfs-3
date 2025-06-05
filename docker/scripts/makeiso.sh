#!/bin/bash

#Clean old versions
cd /home/mount/src
export ISODIR=kfsiso
rm -f ../kfs.iso
rm -rf $ISODIR
mkdir $ISODIR
mkdir $ISODIR/boot
mkdir $ISODIR/boot/grub

#Copy files
cp grub.cfg $ISODIR/boot/grub
cp kfs.bin $ISODIR/boot/

#Create bootloader image
grub-mkimage -O i386-pc \
	-o /tmp/core.img \
	-p "(cd)" \
	-c $ISODIR/boot/grub/grub.cfg \
	biosdisk \
	multiboot \
	iso9660

cat /usr/lib/grub/i386-pc/cdboot.img /tmp/core.img > $ISODIR/boot/grub/grub.img

#Build ISO
xorriso \
  -outdev ../kfs.iso \
  -map $ISODIR / \
  -boot_image grub bin_path=/boot/grub/grub.img \

rm -rf $ISODIR
