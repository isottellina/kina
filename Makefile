PLATFORM=x84_64-elf-

CC=$(PLATFORM)gcc
AS=nasm

.PHONY: clean

all: kina

kina: boot.o linker.ld
	ld -Tlinker.ld -melf_x86_64 $< -o $@

boot.o: src/boot.S
	$(AS) -f elf64 $^ -o $@

kina.iso: kina iso/boot/grub/grub.cfg
	cp kina iso/boot/kina
	grub-mkrescue -o $@ iso

iso/boot/grub/grub.cfg:
	mkdir -p iso/boot/grub/
	cp grub.cfg.example $@

clean:
	rm -rf iso
	rm *.o
	rm -f kina kina.iso
