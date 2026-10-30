#ifndef SPI_H_
#define SPI_H_

#include "common.h"
#include "gpio.h"


#define SPI1 ((struct SPI*) (0x40013000))

struct SPI {
	volatile uint32_t CR1, CR2, SR, DR, CRCPR, RXCRCR, TXCRCR;
};

static inline void SPI_SET_ENABLE(struct SPI* pSPI, bool enable) {
	if (enable) {
		pSPI->CR1 |= (1 << 6);
	} else {
		pSPI->CR1 &= ~(1 << 6);
	}
}

static inline void SPI_SET_CR1(struct SPI* pSPI, uint16_t setting) {	// Don't enable/disable (SPE) in this function
	pSPI->CR1 = 0;
	pSPI->CR1 = setting;
}

static inline void SPI_SET_CR2(struct SPI* pSPI, uint16_t setting) {
	pSPI->CR2 = 0;
	pSPI->CR2 |= setting;
}


static inline void SPI_startWrite(struct SPI* pSPI) {	// Set CS Low to start data transfer
	while (!(pSPI->SR & (1 << 1))) {	// If TXE = 0, then buffer not empty! Wait before writing
	}
	GPIO_SET_BSRR(pinA4, 0);
}

static inline void SPI_endWrite(struct SPI* pSPI) {
	while(pSPI->SR & (1 << 7)) {	// IF BSY = 1, then SPI still working. DO NOT set CS high yet.
	}
	GPIO_SET_BSRR(pinA4, 1);	// Set CS High to stop data transfer
}

static inline void SPI_setTypeCommand() {
	GPIO_SET_BSRR(pinA3, LOW);
}

static inline void SPI_setTypeData() {
	GPIO_SET_BSRR(pinA3, HIGH);
}

static inline void SPI_writeByte(struct SPI* pSPI, uint8_t byte) {
	while (!(pSPI->SR & (1 << 1))) {	// If TXE = 0, then buffer not empty! Wait before writing
		}
	pSPI->DR = byte;
}



#endif







