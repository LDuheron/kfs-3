all: devkit iso kfs

devkit:
	docker build -t final:latest -f Dockerfile .

iso:
	docker run --volume $(PWD):/home/mount final

kfs:
	qemu-system-i386 -cdrom kfs.iso

clean:
	docker system prune -a -f
