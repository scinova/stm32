#ifndef _ili9341_h
#define _ili9341_h
#include "gpio.h"
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif
void ili9341_enable(pin_t cspin, pin_t dcpin);
void ili9341_disable();
void ili9341_set_pixel(uint16_t x, uint16_t y, uint16_t color);
#ifdef __cplusplus
}
#endif
#endif
