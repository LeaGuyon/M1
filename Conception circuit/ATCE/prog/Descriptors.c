#include <avr/io.h>
#include <avr/interrupt.h>
#define F _CPU 16000000UL

volatile uint32_t ext_oscillations = 0;
volatile uint32_t int_oscillations = 0;
volatile uint8_t measurement_ready = 0;

// Configuration du Timer1 pour capture sur PD4 (ICP1)
void setup_input_capture() {
    TCCR1A = 0;            
    TCCR1B = (1 << ICES1) | 
             (1 << CS12);            // Prescaler 256 (16MHz/256 = 62.5kHz)
    TIMSK1 = (1 << ICIE1); 
}

// Configuration du Timer3 pour période de 1s
void setup_reference_timer() {
    TCCR3A = 0;
    TCCR3B = (1 << WGM32) |
             (1 << CS32);  
    OCR3A = 62500 - 1;               // 1 seconde (62.5kHz / 62500 = 1Hz?
    TIMSK3 = (1 << OCIE3A);
}

// ISR pour comptage des impulsions externes (PD4)
ISR(TIMER1_CAPT_vect) {
    ext_oscillations++;
}

// ISR pour fin de mesure 1s
ISR(TIMER3_COMPA_vect) {
    int_oscillations = 62500;         //16MHz/256
    measurement_ready = 1;
}

int16_t measure_frequency_error() {
    //cli();
    ext_oscillations = 0;
    measurement_ready = 0;
    setup_input_capture();
    setup_reference_timer();
    //sei();

    while (!measurement_ready);

    //cli();
    int32_t error = ((int32_t)ext_oscillations - (int32_t)int_oscillations) / (int32_t)int_oscillations;
    //sei();

    return (int16_t)error; 
}
