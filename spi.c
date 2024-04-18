#include <stm32f1xx.h>
#include "spi.h"

#define SPIGPIO GPIOA
#define SCK 5 // 3
#define MISO 6 // 4
#define MOSI 7 // 5

void spi_enable() {
  RCC->APB2ENR |= RCC_APB2ENR_IOPAEN // port clock
			| RCC_APB2ENR_AFIOEN // alt function clock
			| RCC_APB2ENR_SPI1EN; //	spi clock
	GPIOA->CRL &= 0x000FFFFF;
	GPIOA->CRL |= 0xD4D00000; // pb6 input/float, pb7 & pb5 output/alt-func open-drain
	SPI1->CR1 = SPI_CR1_SSM | SPI_CR1_SSI // software slave select
			| SPI_CR1_MSTR | SPI_CR1_SPE // spi master
			| (5 << SPI_CR1_BR_Pos); // baudrate
	AFIO->MAPR &= ~AFIO_MAPR_SPI1_REMAP;
}

void spi_disable() {
	SPI1->CR1 = 0;
  RCC->APB2ENR &= ~RCC_APB2ENR_SPI1EN;
}

uint8_t spi_transfer8(uint8_t data) {
	SPI1->DR = data;
	while (!(SPI1->SR & SPI_SR_RXNE));
	return SPI1->DR;
}

void spi_transfer(uint8_t * data, uint8_t len) {
	uint8_t *p = data;
	SPI1->DR = *p;
	while (--len > 0) {
		uint8_t out = *(p + 1);
		while (!(SPI1->SR & SPI_SR_RXNE));
		uint8_t in = SPI1->DR;
		while (!(SPI1->SR & SPI_SR_TXE));
		SPI1->DR = out;
		*p++ = in;
	}
}
