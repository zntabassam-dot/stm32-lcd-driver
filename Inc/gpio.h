#ifndef GPIO_H_
#define GPIO_H_

#include "common.h"


#define GPIO_PINANDBANK(bank, pin_num) ((bank - 'A') << 8 | (pin_num))	// converts (char bank, int pin) to uint16_t
#define GPIO_BANK(bank) (bank - 'A')	// uint8_t for bank
#define GPIO_GETBANK(pin_def) (pin_def >> 8)	// input uint16_t, take 8 MSB, equivalent to bank
#define GPIO_GETPIN(pin_def) (pin_def & 0xFF)	// input uint16_t, take 8 LSB, equivalent to pin
#define GPIO_POINTER(bank) ((struct GPIO*) (0x48000000 + (bank * 0x0400)))	// takes bank and points to relative struct address

#define bankA GPIO_BANK('A')
#define bankB GPIO_BANK('B')
#define bankC GPIO_BANK('C')
#define bankH GPIO_BANK('H')

struct GPIO {
	volatile uint32_t MODER, OTYPER, OSPEEDR, PUPDR, IDR, ODR, BSRR, LCKR, AFRL, AFRH, BRR;
};

enum{GPIO_INPUT_MODE, GPIO_OUTPUT_MODE, GPIO_AF_MODE, GPIO_ANALOG_MODE};	// MODER input values

static inline void GPIO_SET_MODER(uint16_t pin_and_bank, uint8_t mode) {
	struct GPIO* pGPIO_BANK = GPIO_POINTER(GPIO_GETBANK(pin_and_bank));	// obtain pointer to struct
	uint8_t pin = GPIO_GETPIN(pin_and_bank);	// obtain pin number
	pGPIO_BANK->MODER &= ~(3 << (pin*2));	// clear bits
	pGPIO_BANK->MODER |= (mode << (pin*2));	// set mode
}

static inline void GPIO_SET_ODR(uint8_t bank, uint16_t full_output) {	// for chosen bank, assign all pin outputs as desired
	struct GPIO* pGPIO_BANK = GPIO_POINTER(bank);
	pGPIO_BANK->ODR &= ~(0xFFFF);
	pGPIO_BANK->ODR |= (full_output);
}

static inline void GPIO_SET_BSRR(uint16_t pin_and_bank, bool set) {	// for singular pin, choose to set/reset
	struct GPIO* pGPIO_BANK = GPIO_POINTER(GPIO_GETBANK(pin_and_bank));
	uint8_t pin = GPIO_GETPIN(pin_and_bank);
	if (set) {
		pGPIO_BANK->BSRR |= (1 << pin);
	} else {
		pGPIO_BANK->BSRR |= (1 << (pin+16));
	}

}

static inline void GPIO_SET_AFR(uint16_t bank_and_pin, uint8_t AF_num) {
	struct GPIO* pGPIO_BANK = GPIO_POINTER(GPIO_GETBANK(bank_and_pin));
	uint8_t pin = GPIO_GETPIN(bank_and_pin);
	if (pin <= 7) {
		pGPIO_BANK->AFRL &= ~(0xF << (4*pin));	// Clears current AF number
		pGPIO_BANK->AFRL |= (AF_num << (4*pin));
	} else {
		pin -= 8;
		pGPIO_BANK->AFRH &= ~(0xF << (4*pin));	// Clears current AF number
		pGPIO_BANK->AFRH |= (AF_num << (4*pin));
	}
}





#endif
