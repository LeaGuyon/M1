#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 16000000UL

volatile uint32_t cycle_count = 0;
volatile uint8_t measurement_done = 0;
volatile uint8_t first_capture = 1;

void setup_input_capture() {
    // PD4 en entrée (ICP1)
    DDRD &= ~(1 << PD4);

    TCCR1A = 0; // Mode normal
    TCCR1B = (1 << ICES1) | (1 << CS10); // Front montant, pas de prescaler (16 MHz)
    TIMSK1 |= (1 << ICIE1); // Activation interruption capture
}

ISR(TIMER1_CAPT_vect) {
    if (first_capture) {
        TCNT1 = 0;
        first_capture = 0;
    } else {
        cycle_count = ICR1;
        measurement_done = 1;
        first_capture = 1;
    }
}

uint32_t measure_cycles() {
    measurement_done = 0;

    // Attente bloquante jusqu’à la prochaine mesure complète
    while (!measurement_done);

    return cycle_count-10433;
}
