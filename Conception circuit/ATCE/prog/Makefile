MCU=atmega32u4
DFU=dfu-programmer
TARGET=main
FCT=USB
FCT1=PID
FCT2=erreur
FCT3=init_PWM_PD7
REP=/media/etudiant/AUBERTIN/scolarite/L3/EP2/c/TP3/lufa/
REPEEA=/media/etudiant/AUBERTIN/scolarite/L3/EP2/c/TP6/lib_atmega/

all: $(TARGET).hex

$(TARGET).hex: $(TARGET).out
	avr-objcopy -Oihex $(TARGET).out $(TARGET).hex # for MS-Windows (winavr requires .hex)
	avr-objdump -dSt $(TARGET).out > $(TARGET).lst

$(TARGET).out: $(TARGET).o $(FCT).o $(FCT1).o $(FCT2).o
	avr-gcc -L$(REP)/VirtualSerial/ -L$(REP)/VirtualSerial_lib/ -L$(REPEEA)/lib/ -L$(REPEEA)/src/ -mmcu=$(MCU) -o $(TARGET).out $(TARGET).o $(FCT).o $(FCT1).o $(FCT2).o -lVirtualSerial -lLEEA

$(FCT).o: $(FCT).c $(FCT).h
	avr-gcc -Wall -g -mmcu=$(MCU) -I$(REP)/VirtualSerial/ -I$(REP)/VirtualSerial_example/ -I$(REP)/lufa-LUFA-140928/ -I$(REPEEA)/include/ -DF_USB=16000000UL \
	-std=gnu99 -Os -c $(FCT).c

$(FCT1).o: $(FCT1).c $(FCT1).h
	avr-gcc -Wall -g -mmcu=$(MCU) -I$(REP)/VirtualSerial/ -I$(REP)/VirtualSerial_example/ -I$(REP)/lufa-LUFA-140928/ -I$(REPEEA)/include/ -DF_USB=16000000UL \
	-std=gnu99 -Os -c $(FCT1).c

$(FCT2).o: $(FCT2).c $(FCT2).h
	avr-gcc -Wall -g -mmcu=$(MCU) -I$(REP)/VirtualSerial/ -I$(REP)/VirtualSerial_example/ -I$(REP)/lufa-LUFA-140928/ -I$(REPEEA)/include/ -DF_USB=16000000UL \
	-std=gnu99 -Os -c $(FCT2).c
	
$(FCT3).o: $(FCT3).c $(FCT3).h
	avr-gcc -Wall -g -mmcu=$(MCU) -I$(REP)/VirtualSerial/ -I$(REP)/VirtualSerial_example/ -I$(REP)/lufa-LUFA-140928/ -I$(REPEEA)/include/ -DF_USB=16000000UL \
	-std=gnu99 -Os -c $(FCT3).c

$(TARGET).o: $(TARGET).c
	avr-gcc -Wall -g -mmcu=$(MCU) -I$(REP)/VirtualSerial/ -I$(REP)/VirtualSerial_example/ -I$(REP)/lufa-LUFA-140928/ -I$(REPEEA)/include/ -DF_USB=16000000UL \
	-std=gnu99 -Os -c $(TARGET).c

install: $(TARGET).hex
	$(DFU) $(MCU) erase
	$(DFU) $(MCU) flash $(TARGET).hex
	$(DFU) $(MCU) reset

clean:
	rm *.o $(TARGET).out
