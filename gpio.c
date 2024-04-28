#include <stm32f1xx.h>
#include "gpio.h"

typedef GPIO_TypeDef gpio_t;
#define GPIO(x) ((gpio_t *) (0x40010800 + 0x400 * (x)))

typedef enum {
	INPUT,
	OUTPUT_10MHZ,
	OUTPUT_2MHZ,
	OUTPUT_50MHZ,
} gpio_crx_mod_t;

typedef enum {
	INPUT_ANALOG = 0,
	INPUT_FLOAT = 1,
	INPUT_PULL = 2,
	OUTPUT_PUSHPULL = 0,
	OUTPUT_OPENDRAIN = 1,
	ALTERNATE_OUTPUT_PUSHPULL = 2,
	ALTERNATE_OUTPUT_OPENDRAIN = 3,
} gpio_crx_cnf_t;

void port_enable(port_t port) {
	if (port == PortA) RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	if (port == PortB) RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
	if (port == PortC) RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
	if (port == PortD) RCC->APB2ENR |= RCC_APB2ENR_IOPDEN;
}

void pin_mode(pin_t pin, pin_mode_t mode) {
	gpio_crx_mod_t mod = 0;
	gpio_crx_cnf_t cnf = 0;
	switch (mode) {
		case Input:
			mod = INPUT; cnf = INPUT_FLOAT;
			break;
		case InputPullUp:
			mod = INPUT; cnf = INPUT_PULL;
			break;
		case InputPullDown:
			mod = INPUT; cnf = INPUT_PULL;
			break;
		case InputAnalog:
			mod = INPUT; cnf = INPUT_ANALOG;
			break;
		case Output:
			mod = OUTPUT_10MHZ; cnf = OUTPUT_PUSHPULL;
			break;
		case OutputOpenDrain:
 			mod = OUTPUT_10MHZ; cnf = OUTPUT_OPENDRAIN;
			break;
		case AlternateOutput:
 			mode = OUTPUT_10MHZ; cnf = ALTERNATE_OUTPUT_PUSHPULL;
			break;
		case AlternateOutputOpenDrain:
 			mod = OUTPUT_10MHZ; cnf = ALTERNATE_OUTPUT_OPENDRAIN;
			break;
	}
	uint32_t val, mask;
	gpio_t * gpio = GPIO(pin_port(pin));
	if (pin_number(pin) < 8) {
		val = ((cnf << 2) + mod) << (4 * pin_number(pin));
		mask = 0xf << (4 * pin_number(pin));
		gpio->CRL = (gpio->CRL & ~mask) | val;
	} else {
		val = ((cnf << 2) + mod) << (4 * (pin_number(pin) - 8));
		mask = 0xf << (4 * (pin_number(pin) - 8));
		gpio->CRH = (gpio->CRH & ~mask) | val;
	}
}

void pin_set(pin_t pin) {
	gpio_t * gpio = GPIO(pin_port(pin));
	gpio->BSRR |= pin_mask(pin);
}

void pin_reset(pin_t pin) {
	gpio_t * gpio = GPIO(pin_port(pin));
	gpio->BRR |= pin_mask(pin);
}
