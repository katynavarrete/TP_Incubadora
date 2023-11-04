CC=avr-gcc
OBJETOS=main.o twi.o lcd_ssd1306.o utils_hum_tem.o utils_corriente.o   utils_reley.o timer1_servo.o utils_parlante.o
APP=final
CFLAGS=-Os -DF_CPU=16000000UL -mmcu=atmega328p 
LDFLAGS=-mmcu=atmega328p
FIRMWARE=imagen.hex

# $@:Se sustituye por el nombre del objetivo de la presente regla.
# $*:Se sustituye por la raíz de un nombre de fichero.
# $<:Se sustituye por la primera dependencia de la presente regla.
# $^:Se sustituye por una lista separada por espacios de cada una de las dependencias de la presente regla.

all: $(APP)


$(APP): $(OBJETOS)
	$(CC) $(LDFLAGS) -o $@ $^ 

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

flash:
	avr-objcopy -O ihex -R .eeprom $(APP) $(FIRMWARE)
	avrdude -p atmega328p -c arduino -P /dev/ttyUSB0 -b 57600 -D -U flash:w:$(FIRMWARE):i
	# avrdude -p atmega328p -c arduino -P /dev/ttyUSB0 -b 115200 -D -U flash:w:$(FIRMWARE):i
clean:
	rm $(OBJETOS) $(APP) $(FIRMWARE)
