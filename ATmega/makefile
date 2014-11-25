F_CPU = 16000000

default:
	avr-gcc -mmcu=atmega328p -DF_CPU=$(F_CPU) -o test.elf main.c commands.s nrf24l01.c usart.c
	avr-objcopy -O ihex test.elf test.hex
	avr-size test.elf

clean:
	rm -rf *.elf *.o *.hex

d:
	#may need to change /dev/tty to correct port on your computer
	avrdude -p m328p -P /dev/ttyACM1 -c avrispv2 -F -u -U flash:w:test.hex
