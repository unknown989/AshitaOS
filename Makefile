# GPPPARAMS = -m32 -nostdlib -fno-use-cxa-atexit -fno-builtin -fno-rtti -fno-exceptions -fno-leading-underscore
GPPPARAMS = -m32 -std=gnu99 -fno-use-cxa-atexit -fno-builtin -fno-rtti -fno-exceptions -fno-leading-underscore



ASPARAMS = --32
LDPARAMS = -melf_i386

objects = loader.o kernel.o
all:fast
%.o: %.cpp
	g++ $(GPPPARAMS) -o $@ -c $<

%.o: %.s
	as $(ASPARAMS) -o $@ -c $<
	
kernel.bin: linker.ld $(objects)
	ld $(LDPARAMS) -T $< -o $@ $(objects)

install:
	sudo cp kernel.bin /boot/

clean:
	rm kernel.bin loader.o kernel.o
	
full:
	rm kernel.bin loader.o kernel.o iso/boot/kernel.bin kernel.iso

kernel.iso : kernel.bin
	mkdir -p iso/boot/grub
	cp $< iso/boot
	echo "set timeout=0" >> iso/boot/grub/grub.cfg
	echo "set default=0" >> iso/boot/grub/grub.cfg
	echo "" >> iso/boot/grub/grub.cfg
	echo "menuentry 'Ashita OS' {" >> iso/boot/grub/grub.cfg
	echo "	multiboot /boot/kernel.bin" >> iso/boot/grub/grub.cfg
	echo "	boot" >> iso/boot/grub/grub.cfg
	echo "}" >> iso/boot/grub/grub.cfg
	grub-mkrescue --output=$@ iso
	rm -rf iso
	
fast: kernel.iso
	(killall qemu-system-x86_64 || true) 
	qemu-system-x86_64 -kernel kernel.bin
	
	
run:
	(killall qemu-system-x86_64 || true) 
	qemu-system-x86_64 kernel.iso
