#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// 75ohm resistor, 2.1V 20mA LED, connected across pin A0 (3.3V) and GND

int main(void)
{
	// We are enabling RCC's clock supply to AHB2, and specifically GPIOA
	* (volatile uint32_t*) (0x40021000 + 0x4C) &= ~(1 << 0);
	* (volatile uint32_t*) (0x40021000 + 0x4C) |= (1 << 0);

	// We are setting GPIOA MODER to general output mode, bits 01
	* (volatile uint32_t*) (0x48000000 + 0x00) &= ~(3 << 0);
	* (volatile uint32_t*) (0x48000000 + 0x00) |= (1 << 0);

	// We are setting GPIOA ODR to high
	* (volatile uint32_t*) (0x48000000 + 0x14) &= ~(1 << 0);
	* (volatile uint32_t*) (0x48000000 + 0x14) |= (1 << 0);

	bool bitSwitch = 0;

    /* Loop forever */
	while (1) {
		for (uint16_t i=0;i<0xFFFF;i++) {
		}
		// We are changing the output of GPIOA by setting the bit value with BSSR
		if (bitSwitch) {
			* (volatile uint32_t*) (0x48000000 + 0x18) = (1 << 0);
		}
		if (!bitSwitch) {
			* (volatile uint32_t*) (0x48000000 + 0x18) = (1 << (0+16));
		}
		bitSwitch = !bitSwitch;

	}
}
