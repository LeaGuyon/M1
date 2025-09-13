# Nom du fichier source principal (sans extension)
NAME = blinkLED
# Tu peux changer le fichier source en décommentant l’un des suivants :
# NAME = adc-dac-timer
# NAME = adc-dac-printf
# NAME = filtre
# NAME = miniblink
# NAME = timer_jmf

# Chemins
LIBOPENCM3_INC = /home/lea/M1/libopencm3/include
LIBOPENCM3_LIB = /home/lea/M1/libopencm3/lib

# Fichier de lien (linker script)
LD_SCRIPT = /home/lea/M1/stm32/stm32f4-discovery.ld

# Options de compilation
CFLAGS = -I$(LIBOPENCM3_INC) \
	-fno-common -mthumb -mcpu=cortex-m3 -msoft-float \
	-DSTM32F1 -DSTM32F10X_LD_VL -c

# Options de linkage
LDFLAGS = -L$(LIBOPENCM3_LIB) -T$(LD_SCRIPT) -nostartfiles \
	-Wl,--gc-sections -Wl,--start-group -lc -lnosys -Wl,--end-group \
	-mthumb -mcpu=cortex-m3 -msoft-float -mfix-cortex-m3-ldrd

# Règle par défaut
all: $(NAME).bin

# Génération du binaire à partir de l'ELF
$(NAME).bin: $(NAME).elf
	arm-none-eabi-objcopy -Obinary $(NAME).elf $(NAME).bin

# Compilation du fichier source en objet
$(NAME).o: $(NAME).c
	arm-none-eabi-gcc $(CFLAGS) $< -o $@

# Édition de lien pour créer l'ELF
$(NAME).elf: $(NAME).o
	arm-none-eabi-gcc -o $@ $^ -lopencm3_stm32f1 $(LDFLAGS)

# Flash via ST-Link
flash: $(NAME).bin
	st-flash write $(NAME).bin 0x8000000

# Nettoyage
clean:
	rm -f *.elf *.o *.bin
