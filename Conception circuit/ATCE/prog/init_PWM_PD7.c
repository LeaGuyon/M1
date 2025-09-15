void init_PWM_PD7() {
    DDRD |= (1 << PD7); 
    
    TCCR2A = (1 << COM2A1) | (1 << WGM20);
    TCCR2B = (1 << CS20);
    
    OCR2A = 0;
}
