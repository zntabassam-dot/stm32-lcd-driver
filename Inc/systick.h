#ifndef SYSTICK_H_
#define SYSTICK_H_

struct SysTick {
	volatile uint32_t CTRL, LOAD, VAL, CALIB;
};

#define SYSTICK ((struct SysTick*) 0xE000E010)   // Fixed ARM Cortex-M4 core address, same for all STM32L4 chips

// --- Assumes default reset clock config: MSI running at 4 MHz, no prescalers touched ---
#define SYSCLK_HZ 4000000UL

static inline void delay_ms(uint32_t ms) {
	// Reload value = (clock ticks per ms) * ms, minus 1 (since it counts down to 0 inclusive)
	uint32_t reload = (SYSCLK_HZ / 1000UL) * ms - 1UL;

	SYSTICK->LOAD = reload;         // Set countdown starting value
	SYSTICK->VAL = 0;               // Clear current value (also clears COUNTFLAG)
	SYSTICK->CTRL = (1 << 2) | (1 << 0);   // CLKSOURCE=1 (use processor/HCLK clock), ENABLE=1 (TICKINT left 0 - no interrupt, we're polling)

	while (!(SYSTICK->CTRL & (1 << 16))) {   // Poll COUNTFLAG (bit 16) - set to 1 each time VAL counts down to 0
	}

	SYSTICK->CTRL = 0;   // Disable SysTick when done
}

#endif /* SYSTICK_H_ */
