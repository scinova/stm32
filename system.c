#include <stm32f1xx.h>
#include <stdint.h>
#include "system.h"

static volatile uint32_t _system_ticks;

void SysTick_Handler() {
  _system_ticks++;
}

uint32_t system_ticks() {
	__disable_irq();
	uint32_t v = _system_ticks;
	__enable_irq();
	return v;
}

void system_set_hse_72mhz_clock() {
	FLASH->ACR &=~FLASH_ACR_LATENCY_0; // latency 2 wait states
	FLASH->ACR |= FLASH_ACR_LATENCY_1;
	RCC->CR |= RCC_CR_HSEON; // enable hse
	while (!(RCC->CR & RCC_CR_HSERDY));
	RCC->CFGR |= RCC_CFGR_PLLSRC // HSE as PLL input
		| RCC_CFGR_PPRE1_DIV2 // APB1 prescale 2 (<36MHz)
		| RCC_CFGR_PLLMULL9; // clk = 8 * 9 = 72Mhz
	RCC->CR |= RCC_CR_PLLON;
	while (!(RCC->CR & RCC_CR_PLLRDY));
	RCC->CFGR |= RCC_CFGR_SW_PLL; // PLL as system clock source
  SystemCoreClockUpdate();
}

void system_init(void) {
	system_set_hse_72mhz_clock();
  SysTick_Config(SystemCoreClock / 1000);
  __enable_irq();
}
