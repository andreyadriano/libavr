# Arquivo: Makefile
# Autor: Arliones Hoeller, IFSC-SJE

APP := infeasible_edd_test.cpp
COMPONENTS := gpio.o uart.o fifo.o adc_channel.o timer.o scaffold.o
SERIAL_PORT := /dev/ttyACM0

CC_FLAGS := -mmcu=atmega328p
# CC_FLAGS := -mmcu=atmega328p -Wl,-u,vfprintf -lprintf_flt  # habilita uso de floats no printf

all: $(COMPONENTS)
	avr-g++ $(CC_FLAGS) $(APP) $(COMPONENTS) -o main.elf
	avr-size main.elf
	avr-objcopy -O ihex main.elf main.ihex
	avrdude -p atmega328p -c arduino -P $(SERIAL_PORT) -U flash:w:main.ihex

%.o: %.cpp
	avr-g++ $(CC_FLAGS) -c $< -o $@

clean:
	rm -f *.o *.elf *.ihex