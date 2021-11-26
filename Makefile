PLATFORM=x86_64-elf-

CC=$(PLATFORM)gcc
AS=nasm

CFLAGS=-nostdlib -nostdinc -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs -Wall

SOURCES=$(wildcard src/*.c) $(wildcard src/*.S)
OBJS=$(patsubst src/%,obj/%,$(patsubst %.S,%.o,$(patsubst %.c,%.o,$(SOURCES))))

.PHONY: clean

all: kina

kina: $(OBJS) linker.ld
	ld -Tlinker.ld -melf_x86_64 $(OBJS) -o $@

obj/%.o: src/%.S obj
	$(AS) -f elf64 $< -o $@

obj/%.o: src/%.c obj
	$(CC) $< -c $(CFLAGS) -o $@

kina.iso: kina iso/boot/grub/grub.cfg
	cp kina iso/boot/kina
	grub-mkrescue -o $@ iso

iso/boot/grub/grub.cfg:
	mkdir -p iso/boot/grub/
	cp grub.cfg.example $@

obj:
	mkdir -p obj

clean:
	rm -rf iso obj
	rm -f *.o
	rm -f kina kina.iso
