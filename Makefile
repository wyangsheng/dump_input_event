cc=/opt/toolchain/arm-cortex_a8-linux-gnueabi-4.9.3/bin/arm-cortex_a8-linux-gnueabi-gcc

all:
	$(cc) -o dump_input_event dump_input_event.c

clean:
	rm dump_input_event
