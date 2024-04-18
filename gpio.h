#ifndef _gpio_h
#define _gpio_h
#include <stdbool.h>

typedef enum {
	INPUT,
	INPUT_PULLUP,
	INPUT_PULLDOWN,
	INPUT_ANALOG,
	OUTPUT,
	OUTPUT_OPENDRAIN
} gpio_pin_mode_t;

typedef enum {
	PA = 0,
	PB = 1,
	PC = 2,
	PD = 3,
} gpio_port_t;

typedef enum {
	PA0 = (PA << 16) + 0x00,
	PA1 = (PA << 16) + 0x01,
	PA2 = (PA << 16) + 0x02,
	PA3 = (PA << 16) + 0x03,
	PA4 = (PA << 16) + 0x04,
	PA5 = (PA << 16) + 0x05,
	PA6 = (PA << 16) + 0x06,
	PA7 = (PA << 16) + 0x07,
	PA8 = (PA << 16) + 0x08,
	PA9 = (PA << 16) + 0x09,
	PA10 = (PA << 16) + 0x0A,
	PA11 = (PA << 16) + 0x0B,
	PA12 = (PA << 16) + 0x0C,
	PA13 = (PA << 16) + 0x0D,
	PA14 = (PA << 16) + 0x0E,
	PA15 = (PA << 16) + 0x0F,
	PB0 = (PB << 16) + 0x00,
	PB1 = (PB << 16) + 0x01,
	PB2 = (PB << 16) + 0x02,
	PB3 = (PB << 16) + 0x03,
	PB4 = (PB << 16) + 0x04,
	PB5 = (PB << 16) + 0x05,
	PB6 = (PB << 16) + 0x06,
	PB7 = (PB << 16) + 0x07,
	PB8 = (PB << 16) + 0x08,
	PB9 = (PB << 16) + 0x09,
	PB10 = (PB << 16) + 0x0A,
	PB11 = (PB << 16) + 0x0B,
	PB12 = (PB << 16) + 0x0C,
	PB13 = (PB << 16) + 0x0D,
	PB14 = (PB << 16) + 0x0E,
	PB15 = (PB << 16) + 0x0F,
	PC0 = (PC << 16) + 0x00,
	PC1 = (PC << 16) + 0x01,
	PC2 = (PC << 16) + 0x02,
	PC3 = (PC << 16) + 0x03,
	PC4 = (PC << 16) + 0x04,
	PC5 = (PC << 16) + 0x05,
	PC6 = (PC << 16) + 0x06,
	PC7 = (PC << 16) + 0x07,
	PC8 = (PC << 16) + 0x08,
	PC9 = (PC << 16) + 0x09,
	PC10 = (PC << 16) + 0x0A,
	PC11 = (PC << 16) + 0x0B,
	PC12 = (PC << 16) + 0x0C,
	PC13 = (PC << 16) + 0x0D,
	PC14 = (PC << 16) + 0x0E,
	PC15 = (PC << 16) + 0x0F,
	PD0 = (PD << 16) + 0x00,
	PD1 = (PD << 16) + 0x01,
	PD2 = (PD << 16) + 0x02,
	PD3 = (PD << 16) + 0x03,
	PD4 = (PD << 16) + 0x04,
	PD5 = (PD << 16) + 0x05,
	PD6 = (PD << 16) + 0x06,
	PD7 = (PD << 16) + 0x07,
	PD8 = (PD << 16) + 0x08,
	PD9 = (PD << 16) + 0x09,
	PD10 = (PD << 16) + 0x0A,
	PD11 = (PD << 16) + 0x0B,
	PD12 = (PD << 16) + 0x0C,
	PD13 = (PD << 16) + 0x0D,
	PD14 = (PD << 16) + 0x0E,
	PD15 = (PD << 16) + 0x0F,
} gpio_pin_t;

#ifdef __cplusplus
extern "C" {
#endif
void gpio_enable_port(gpio_port_t port);
void gpio_disable_port(gpio_port_t port);
void gpio_pin_mode(gpio_pin_t pin, gpio_pin_mode_t mode);
void gpio_pin_set(gpio_pin_t pin);
void gpio_pin_clear(gpio_pin_t pin);
void gpio_pin_write(gpio_pin_t pin, bool value);
#ifdef __cplusplus
}
#endif
#endif
