#include <stm32f1xx.h>
#include "uart.h"

static uint8_t tx_buffer[UART_TX_BUFFER_SIZE + 1];
static uint8_t tx_head;
static uint8_t tx_tail;

static uint8_t rx_buffer[UART_RX_BUFFER_SIZE + 1];
static uint8_t rx_head;
static uint8_t rx_tail;

void _uart_enable(uint32_t baudrate, bool enable_tx, bool enable_rx) {
	RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN; // port A
	// pins a2 and a3 for usart2
	GPIOA->CRL &= (GPIO_CRL_MODE2 | GPIO_CRL_CNF2 | GPIO_CRL_MODE3 | GPIO_CRL_CNF3);
	GPIOA->CRL |= ((0x1 << GPIO_CRL_MODE2_Pos) | (0x2 << GPIO_CRL_CNF2_Pos) |
		(0x0 << GPIO_CRL_MODE3_Pos) | (0x1 << GPIO_CRL_CNF3_Pos));
	// baudrate
	uint16_t uartdiv = SystemCoreClock / baudrate;
	USART2->BRR = (((uartdiv / 16) << USART_BRR_DIV_Mantissa_Pos) |
			((uartdiv % 16) << USART_BRR_DIV_Fraction_Pos));
	USART2->CR1 |= USART_CR1_UE;
	if (enable_tx)
		USART2->CR1 |= USART_CR1_TE;
	if (enable_rx)
		USART2->CR1 |= USART_CR1_RE | USART_CR1_RXNEIE;
	NVIC_EnableIRQ(USART2_IRQn);
}

void uart_enable(uint32_t baudrate) {
	_uart_enable(baudrate, true, true);
}

void uart_enable_tx_only(uint32_t baudrate) {
	_uart_enable(baudrate, true, false);
}

void uart_enable_rx_only(uint32_t baudrate) {
	_uart_enable(baudrate, false, true);
}

void uart_disable() {
	NVIC_DisableIRQ(USART2_IRQn);
	USART2->CR1 &= 0;
	RCC->APB1ENR &= ~RCC_APB1ENR_USART2EN;
	GPIOA->CRL &= GPIO_CRL_MODE2 | GPIO_CRL_CNF2 | GPIO_CRL_MODE3 | GPIO_CRL_CNF3;
}

bool uart_tx_buffer_is_empty() {
	uint8_t next = (tx_head < UART_TX_BUFFER_SIZE ? tx_head + 1 : 0);
	return tx_tail != next;
}

void uart_write(uint8_t * data, uint8_t len) {
	bool empty = (tx_head == tx_tail);
	for (int i = 0; i < len; i++) {
		tx_buffer[tx_head] = data[i];
		tx_head = (tx_head < UART_TX_BUFFER_SIZE ? tx_head + 1 : 0);
	}
	if (empty) {
		//USART2->DR = tx_buffer[tx_tail];
		USART2->CR1 |= USART_CR1_TXEIE;
	}
}

void uart_print(uint8_t * data) {
	uart_write(data, strlen((char *)data));
}

bool uart_data_is_available() {
	return (rx_head != rx_tail);
}

uint8_t uart_read() {
	if (rx_head == rx_tail)
		return 0;
	uint8_t c = rx_buffer[rx_tail];
	rx_tail = (rx_tail < UART_RX_BUFFER_SIZE ? rx_tail + 1 : 0);
	return c;
}

void USART2_IRQHandler(void) {
	if (USART2->SR & USART_SR_RXNE) {
		uint8_t next = rx_head + 1;
		if (next >= UART_RX_BUFFER_SIZE)
			next = 0;
		uint8_t v = USART2->DR;
		if (next != rx_tail) {
			rx_buffer[rx_head] = v;
			rx_head = next;
		}
	}
	if (USART2->SR & USART_SR_TXE) {
		if (tx_head != tx_tail) {
			USART2->DR = tx_buffer[tx_tail];
			tx_tail = (tx_tail < UART_TX_BUFFER_SIZE ? tx_tail + 1 : 0);
		} else
			USART2->CR1 &= ~USART_CR1_TXEIE;
	}
}
