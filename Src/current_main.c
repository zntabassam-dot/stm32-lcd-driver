#include "common.h"
#include "bitmaps.h"
#include "gpio.h"
#include "graphics.h"
#include "pins.h"
#include "spi.h"
#include "st7735.h"
#include "systick.h"




int main(void)
{


	// We are enabling RCC's clock supply to AHB2, and specifically GPIOA
	* (volatile uint32_t*) (0x40021000 + 0x4C) &= ~(1 << 0);
	* (volatile uint32_t*) (0x40021000 + 0x4C) |= (1 << 0);

	// We are enabling RCC's clock supply to APB2, specifically SPI1
	* (volatile uint32_t*) (0x40021000 + 0x60) &= ~(1 << 12);
	* (volatile uint32_t*) (0x40021000 + 0x60) |= (1 << 12);

	// Also enable GPIOB (bit 1 of the same AHB2ENR register)
	* (volatile uint32_t*) (0x40021000 + 0x4C) &= ~(1 << 1);
	* (volatile uint32_t*) (0x40021000 + 0x4C) |= (1 << 1);


	GPIO_SET_MODER(pinA2, GPIO_OUTPUT_MODE);	// Intended for RES pin
	GPIO_SET_MODER(pinA3, GPIO_OUTPUT_MODE);	// Intended for RS (DC) pin
	GPIO_SET_MODER(pinA4, GPIO_OUTPUT_MODE);	// Manual control of NSS (CS) pin

//	// Set MODER = alternate function for pins A5, A7
//	GPIO_SET_MODER(pinA5, GPIO_AF_MODE);
//	GPIO_SET_MODER(pinA7, GPIO_AF_MODE);
//
//	// Set AF5 for SPI1 to pins A5, A7
//	GPIO_SET_AFR(pinA5, 5);	// SCK
//	GPIO_SET_AFR(pinA7, 5);	// MOSI (SDA)

	GPIO_SET_MODER(pinB3, GPIO_AF_MODE);
	GPIO_SET_MODER(pinB5, GPIO_AF_MODE);

	GPIO_SET_AFR(pinB3, 5);	// SCK
	GPIO_SET_AFR(pinB5, 5);	// MOSI (SDA)

	//Set SPI registers, then enable last
	SPI_SET_CR1(SPI1, 0b0000001100000100);	// Set SSM, SSI, MSTR = 1
	SPI_SET_CR2(SPI1, 0b0000011100000000);	// Set data register size to 8-bits
	SPI_SET_ENABLE(SPI1, true);


	GPIO_SET_BSRR(pinA2, HIGH);	// Start of setting RES pin
	delay_ms(3500);
	GPIO_SET_BSRR(pinA2, LOW);
	delay_ms(3500);
	GPIO_SET_BSRR(pinA2, HIGH);	// End of setting RES pin, keep RES high

	GPIO_SET_BSRR(pinA3, HIGH);	// Keep RS (DC) high, ST7735 will interpret as data
	GPIO_SET_BSRR(pinA4, HIGH);	// Initialise with high, set CS low to begin transmission. High will end transmission (if not BSY)

	// ST7735 init sequence
	ST7735_sendCommand(SPI1, SWRESET);
	delay_ms(200);
	ST7735_sendCommand(SPI1, SLPOUT);
	delay_ms(750);
	ST7735_sendCommand(SPI1, DISPON);
	delay_ms(200);
	ST7735_sendCommand(SPI1, FRMCTR1);
	ST7735_sendCommand(SPI1, FRMCTR2);
	ST7735_sendCommand(SPI1, FRMCTR3);
	ST7735_sendCommand(SPI1, INVCTR);
	ST7735_sendCommand(SPI1, PWCTR1);
	ST7735_sendCommand(SPI1, PWCTR2);
	ST7735_sendCommand(SPI1, PWCTR3);
	ST7735_sendCommand(SPI1, PWCTR4);
	ST7735_sendCommand(SPI1, PWCTR5);
	ST7735_sendCommand(SPI1, VMCTR1);
	ST7735_sendCommand(SPI1, INVOFF);
	ST7735_sendCommand(SPI1, MADCTL);
	ST7735_sendCommand(SPI1, COLMOD);

	ST7735_sendCommand(SPI1, CASET);
	ST7735_sendCommand(SPI1, RASET);

	ST7735_sendCommand(SPI1, GMCTRP1);
	ST7735_sendCommand(SPI1, GMCTRN1);
	ST7735_sendCommand(SPI1, NORON);
	delay_ms(200);

	SPI_startWrite(SPI1);
	ST7735_RAMWR_CS_Preset(SPI1, RAMWR);
	SPI_setTypeData();


	for (int y=0;y<128;y++) {
		for (int x=0;x<160;x++) {
//			uint16_t index = (160 * y) + x;
//			uint16_t colour = bitmap[index];
//			writePixel_CS_Preset(SPI1, colour);

			writePixel_CS_Preset(SPI1, 0xF800);
		}
	}


	SPI_endWrite(SPI1);

	/* Loop forever */
	while (1) {
	}


}
