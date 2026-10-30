# TFT LCD Display Driver STM32

An STM32 project for driving an ST7735 TFT LCD over SPI.

## Current status

The current `main` program initializes the display and fills its 128 × 160 pixel area with solid red. Bitmap data is then used to display a custom image, with an example present.

## Hardware

- **Microcontroller:** STM32L432KC
- **Display controller:** ST7735
- **Interface:** SPI1
- **Connections configured in the source:**
  - PA2 — display reset (RES)
  - PA3 — command/data select (RS/DC)
  - PA4 — chip select (CS)
  - PB3 — SPI clock (SCK)
  - PB5 — SPI data out (MOSI/SDA)

## Repository layout

- `Inc/` — headers and display/graphics helpers
- `Src/` — application and source files
- `Startup/` — MCU startup code
- `STM32L432KCUX_FLASH.ld` — linker script
