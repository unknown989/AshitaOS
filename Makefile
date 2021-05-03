GPPPARAMS = -m32
ASPARAMS = --32

objects = loader.o kernel.o


%.o %.cpp:
	g++ $(GPPPARAMS) -o $@ -c $<

%.o %.s:
	as $(ASPARAMS) -o $@ -c $<

kernel.bin:linker.ld $(objects):
	ld $(LDPARAMS) -T $< -o $@ $(objects)
