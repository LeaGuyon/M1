#include <libopencm3/stm32/rcc.h> // do NOT e x p l i c i t l y load f1 / rcc . h
#include <libopencm3/stm32/gpio.h>

	static void gpio_setup(void) {
		rcc_clock_setup_pll(&rcc_hse_configs[RCC_CLOCK_HSE8_24MHZ]);// VL Discovery i s 24 MHz
		rcc_periph_clock_enable(RCC_GPIOC);
		gpio_set_mode(GPIOC, GPIO_MODE_OUTPUT_2_MHZ, GPIO_CNF_OUTPUT_PUSHPULL, GPIO8 | GPIO9) ;
		}

		int main(void) {
			int i;
			gpio_setup();
			gpio_set(GPIOC,GPIO8);
			gpio_clear(GPIOC, GPIO9);
				while(1){
					gpio_toggle(GPIOC, GPIO8);
					gpio_toggle (GPIOC,GPIO9);
					for (i=0; i<1600000; i ++) __asm__ ("nop");
					}
		return 0 ;
}
