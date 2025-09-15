#include "USB.h"
#include "PID.h"
#include <avr/io.h>
#include "Descriptors.h"
#include <stdint.h>
#include "VirtualSerial.h"

extern USB_ClassInfo_CDC_Device_t VirtualSerial_CDC_Interface;
extern FILE USBSerialStream;

void USB(uint32_t freq_error) {
    char buffer[20];
     SetupHardware();
/* Create a regular character stream for the interface so that it can be used with the stdio.h functions */
  CDC_Device_CreateStream(&VirtualSerial_CDC_Interface, &USBSerialStream);
  GlobalInterruptEnable();
  
    while (1){
    sprintf(buffer, "F_ERR:%ld\n", freq_error);  
    for (uint8_t i = 0; i < strlen(buffer); i++) {
        fputc(buffer[i], &USBSerialStream);
    }

    CDC_Device_USBTask(&VirtualSerial_CDC_Interface);
    USB_USBTask();
    }
}
