#ifndef REGISTERS_H
#define REGISTERS_H
#endif

typedef enum {
	LOW,
	HIGH
}	GPIO_DOUT;

typedef enum {
	INPUT,
	OUTPUT
} GPIO_MODE;
typedef enum {
	FLOATING = 0,
	OPEN_DRAIN = 0,
	PULL_UP = 1,
	PUSH_PULL = 1
	
} GPIO_CTRL1;

typedef enum {
	INTERRUPT_DIS = 0,
	OUTPUT_2MHZ = 0,
	INTERRUPT_EN = 1,
	OUTPUT_20MHZ = 1
	
} GPIO_CTRL2;



void IML_GPIO_Init(GPIO_TYPE *gpiox, uint8_t pin, GPIO_MODE mode, GPIO_CTRL1 ctrl1, GPIO_CTRL2 ctrl2) {
	
	gpiox->MODE |= (mode << pin);
	gpiox->CTRL1 |= (ctrl1 << pin);
	gpiox->CTRL2 |= (ctrl2 << pin);
}
void IML_GPIO_WritePin(GPIO_TYPE *gpiox, uint8_t pin, uint8_t state) {
	gpiox->DOUT = (gpiox->DOUT & ~(1U << pin)) | (state << pin);
}
uint8_t IML_GPIO_ReadPin(GPIO_TYPE *gpiox, uint8_t pin) {
	return (gpiox->DIN & (1 << pin)) ? 1 : 0;
}






