#ifndef ST7735_H_
#define ST7735_H_

#include "common.h"
#include "spi.h"


static uint8_t SWRESET[] = {0x01, 0};	// Needs 150ms delay
static uint8_t SLPOUT[] = {0x11, 0};	// Needs 500ms delay
static uint8_t FRMCTR1[] = {0xB1, 3, 0x01, 0x2C, 0x2D};
static uint8_t FRMCTR2[] = {0xB2, 3, 0x01, 0x2C, 0x2D};
static uint8_t FRMCTR3[] = {0xB3, 6, 0x01, 0x2C, 0x2D, 0x01, 0x2C, 0x2D};
static uint8_t INVCTR[]  = {0xB4, 1, 0x07};
static uint8_t PWCTR1[]  = {0xC0, 3, 0xA2, 0x02, 0x84};
static uint8_t PWCTR2[]  = {0xC1, 1, 0xC5};
static uint8_t PWCTR3[]  = {0xC2, 2, 0x0A, 0x00};
static uint8_t PWCTR4[]  = {0xC3, 2, 0x8A, 0x2A};
static uint8_t PWCTR5[]  = {0xC4, 2, 0x8A, 0xEE};
static uint8_t VMCTR1[]  = {0xC5, 1, 0x0E};
static uint8_t INVOFF[]   = {0x20, 0};
static uint8_t MADCTL[]   = {0x36, 1, 0xC8};
static uint8_t COLMOD[]   = {0x3A, 1, 0x05};

static uint8_t CASET[] = {0x2A, 4, 0x00, 0x00, 0x00, 0x7F};
static uint8_t RASET[] = {0x2B, 4, 0x00, 0x00, 0x00, 0x9F};

static uint8_t GMCTRP1[] = {0xE0, 16, 0x02, 0x1C, 0x07, 0x12, 0x37, 0x32, 0x29, 0x2D, 0x29, 0x25, 0x2B, 0x39, 0x00, 0x01, 0x03, 0x10};
static uint8_t GMCTRN1[] = {0xE1, 16, 0x03, 0x1D, 0x07, 0x06, 0x2E, 0x2C, 0x29, 0x2D, 0x2E, 0x2E, 0x37, 0x3F, 0x00, 0x00, 0x02, 0x10};
static uint8_t NORON[]   = {0x13, 0};	// Needs 10ms delay
static uint8_t DISPON[]  = {0x29, 0};	// Needs 100ms delay

static uint8_t RAMWR[] = {0x2C, 0};

static inline void ST7735_sendCommand(struct SPI* pSPI, uint8_t* pCommand) {
	SPI_startWrite(pSPI);
	SPI_setTypeCommand();
	SPI_writeByte(pSPI, *pCommand);
	pCommand += 1;

	while(pSPI->SR & (1 << 7)) {	// IF BSY = 1, then SPI still working. DO NOT set CS high yet.
	}
	SPI_setTypeData();
	uint8_t numArgs = *pCommand;
	pCommand += 1;
	for (int i=0;i<numArgs;i++) {
		SPI_writeByte(pSPI, *pCommand);
		pCommand += 1;
	}
	SPI_endWrite(pSPI);
}

static inline void ST7735_RAMWR_CS_Preset(struct SPI* pSPI, uint8_t* pCommand) {
	SPI_setTypeCommand();
	SPI_writeByte(pSPI, *pCommand);
	pCommand += 1;

	while(pSPI->SR & (1 << 7)) {	// IF BSY = 1, then SPI still working. DO NOT set CS high yet.
	}
	SPI_setTypeData();
	uint8_t numArgs = *pCommand;
	pCommand += 1;
	for (int i=0;i<numArgs;i++) {
		SPI_writeByte(pSPI, *pCommand);
		pCommand += 1;
	}
}

#endif
