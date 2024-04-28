#ifndef _gpio_h
#define _gpio_h

typedef enum {
	PortA = 0,
	PortB = 1,
	PortC = 2,
	PortD = 2,
} port_t;

typedef enum {
	PinA0  = 0x0000,
	PinA1  = 0x0001,
	PinA2  = 0x0002,
	PinA3  = 0x0003,
	PinA4  = 0x0004,
	PinA5  = 0x0005,
	PinA6  = 0x0006,
	PinA7  = 0x0007,
	PinA8  = 0x0008,
	PinA9  = 0x0009,
	PinA10 = 0x000A,
	PinA11 = 0x000B,
	PinA12 = 0x000C,
	PinA13 = 0x000D,
	PinA14 = 0x000E,
	PinA15 = 0x000F,
	PinB0  = 0x0100,
	PinB1  = 0x0101,
	PinB2  = 0x0102,
	PinB3  = 0x0103,
	PinB4  = 0x0104,
	PinB5  = 0x0105,
	PinB6  = 0x0106,
	PinB7  = 0x0107,
	PinB8  = 0x0108,
	PinB9  = 0x0109,
	PinB10 = 0x010A,
	PinB11 = 0x010B,
	PinB12 = 0x010C,
	PinB13 = 0x010D,
	PinB14 = 0x010E,
	PinB15 = 0x010F,
	PinC0  = 0x0200,
	PinC1  = 0x0201,
	PinC2  = 0x0202,
	PinC3  = 0x0203,
	PinC4  = 0x0204,
	PinC5  = 0x0205,
	PinC6  = 0x0206,
	PinC7  = 0x0207,
	PinC8  = 0x0208,
	PinC9  = 0x0209,
	PinC10 = 0x020A,
	PinC11 = 0x020B,
	PinC12 = 0x020C,
	PinC13 = 0x020D,
	PinC14 = 0x020E,
	PinC15 = 0x020F,
	PinD0  = 0x0300,
	PinD1  = 0x0301,
	PinD2  = 0x0302,
	PinD3  = 0x0303,
	PinD4  = 0x0304,
	PinD5  = 0x0305,
	PinD6  = 0x0306,
	PinD7  = 0x0307,
	PinD8  = 0x0308,
	PinD9  = 0x0309,
	PinD10 = 0x030A,
	PinD11 = 0x030B,
	PinD12 = 0x030C,
	PinD13 = 0x030D,
	PinD14 = 0x030E,
	PinD15 = 0x030F,
} pin_t;

typedef enum {
	Input,
	InputFloat = Input,
	InputPullUp,
	InputPullDown,
	InputAnalog,
	Output ,
	OutputOpenDrain,
	AlternateOutput,
	AlternateOutputPushPull = AlternateOutput,
	AlternateOutputOpenDrain,
} pin_mode_t;

#define pin_port(pin) ((port_t) (pin >> 8))
#define pin_number(pin) (pin & 0xFF)
#define pin_mask(pin) ((uint16_t)(1 << pin_number(pin)))
#ifdef __cplusplus
extern "C" {
#endif
void port_enable(port_t port);
void port_disable(port_t port);
void pin_mode(pin_t pin, pin_mode_t mode);
void pin_set(pin_t pin);
void pin_reset(pin_t pin);
#ifdef __cplusplus
extern "C" {
#endif
#endif
