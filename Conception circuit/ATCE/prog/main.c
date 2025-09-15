#include "USB.h"
#include "PID.h"
#include <avr/io.h> 
#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
//#include "Descriptors.h"
#include "erreur.h"
#include <stdint.h>
#include "VirtualSerial.h"
#include <string.h>
#include <stdio.h>

//#include <init_PWM_PD7.h>

extern USB_ClassInfo_CDC_Device_t VirtualSerial_CDC_Interface;
extern FILE USBSerialStream;

int main(void) {
    char buffer[40]; 
    SetupHardware();
    CDC_Device_CreateStream(&VirtualSerial_CDC_Interface, &USBSerialStream);
   
    
    // Configuration PWM sur PD7 (OCR4A)
    DDRD |= (1 << PD7);
    TCCR4B = (1 << CS40); //prescaler de 1
    TC4H=0x03;
    OCR4C=0xff;  // periode
    TCCR4C |= ((1<<COM4D1) | (1<<PWM4D));  // 0x82
    TC4H=0x01;
    OCR4D = 0;   // rapport cyclique
    
    //Configuration input sur PD4 (ICP1)
    DDRD &= ~(1 << PD4);

 //   while (1) 
  //  {   sprintf(buffer, "F_ERR:\r\n");  
//		fputs(buffer, &USBSerialStream);
 //       CDC_Device_USBTask(&VirtualSerial_CDC_Interface);
  //      USB_USBTask();

	//	}
    
    setup_input_capture();
    //setup_reference_timer();
     GlobalInterruptEnable();
    uint32_t err = 0;
    uint32_t c = 0;
    while (1) {
        // cli();
        err = measure_cycles();
        //sei();
        c = PID(c, err);
        TC4H=   ((c >> 8) > 3) ? 3 : (c >> 8);
        OCR4D = (c > 1023) ? 1023 : c;
        sprintf(buffer, "Cmd:%ld Err:%ld\r\n", c ,err);  
        fputs(buffer, &USBSerialStream);
        CDC_Device_USBTask(&VirtualSerial_CDC_Interface);
        USB_USBTask();
    }
}
