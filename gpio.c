#include <stm32f1xx.h>
#include <stdbool.h>
#include "gpio.h"

GPIO_TypeDef * _GPIOX[] = {
	GPIOA,
	GPIOB,
	GPIOC,
	GPIOD,
};

GPIO_TypeDef * gpio_gpio(gpio_pin_t pin) {
  return _GPIOX[pin >> 16];
}

void gpio_enable_port(gpio_port_t port) {
	switch (port) {
		case PA:
			RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
			break;
		case PB:
			RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
			break;
		case PC:
			RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
      break;
		case PD:
			RCC->APB2ENR |= RCC_APB2ENR_IOPDEN;
			break;
  }
}

void gpio_pin_mode(gpio_pin_t pin, gpio_pin_mode_t mode) {
	uint8_t pin_nr = pin & 0xff;
 	uint8_t mod, cnf;
	uint32_t val, mask;
	bool lowpin = (pin_nr < 8);
	GPIO_TypeDef * gpio = gpio_gpio(pin);
	switch (mode) {
		case INPUT:
			mod = 0;
			cnf = 1;
			break;
		case INPUT_PULLUP:
			mod = 0;
			cnf = 2;
			break;
		case INPUT_PULLDOWN:
			mod = 0;
			cnf = 2; // ?
			break;
		case INPUT_ANALOG:
			mod = 0;
			cnf = 0;
			break;
		case OUTPUT:
			mod = 3; // ,2,3
			cnf = 0;
			break;
		case OUTPUT_OPENDRAIN:
			mod = 1; // ,2,3
			cnf = 1;
			break;
	}
	val = ((cnf << 2) | mod) << ((pin_nr - (lowpin ? 0 : 8)) * 4);
	mask = 0xF << ((pin_nr - (lowpin ? 0 : 8)) * 4);
	if (lowpin) {
		gpio->CRL &= ~mask;
		gpio->CRL |= val;
	} else {
		gpio->CRH &= ~mask;
		gpio->CRH |= val;
	}
}

void gpio_pin_set(gpio_pin_t pin) {
	GPIO_TypeDef * gpio = gpio_gpio(pin);
  uint8_t pin_nr = pin & 0xf;
  gpio->BSRR |= 1 << pin_nr;
}

void gpio_pin_clear(gpio_pin_t pin) {
	GPIO_TypeDef * gpio = gpio_gpio(pin);
  uint8_t pin_nr = pin & 0xf;
  gpio->BRR |= 1 << pin_nr;
}
