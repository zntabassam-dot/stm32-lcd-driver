#ifndef GRAPHICS_H_
#define GRAPHICS_H_

#include "common.h"
#include "spi.h"


static inline void writePixel_CS_Preset(struct SPI* pSPI, uint16_t colour) {
	uint8_t MSByte = (colour >> 8);
	uint8_t LSByte = (colour & 0xFF);
	SPI_writeByte(pSPI, MSByte);
	SPI_writeByte(pSPI, LSByte);
}




#endif
