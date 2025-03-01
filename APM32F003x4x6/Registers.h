/*
  ####    #####     ####     ####
 ##  ##   ##  ##     ##     ##  ##
 ##       ##  ##     ##     ##  ##
 ## ###   #####      ##     ##  ##
 ##  ##   ##         ##     ##  ##
 ##  ##   ##         ##     ##  ##
  ####    ##        ####     ####

*/

#define PERIPH_BASE ((uint32_t)0x40000000U)

#define GPIOA_BASE (PERIPH_BASE + 0x0000U)
#define GPIOB_BASE (PERIPH_BASE + 0x0400U)
#define GPIOC_BASE (PERIPH_BASE + 0x0800U)
#define GPIOD_BASE (PERIPH_BASE + 0x0C00U)

typedef struct {
	volatile uint32_t DOUT;
	volatile uint32_t DIN;
	volatile uint32_t MODE;
	volatile uint32_t CTRL1;
	volatile uint32_t CTRL2;
	
	
}	GPIO_TYPE;
#define GPIOA ((GPIO_TYPE*) GPIOA_BASE)
#define GPIOB ((GPIO_TYPE*) GPIOB_BASE)
#define GPIOC ((GPIO_TYPE*) GPIOC_BASE)
#define GPIOD ((GPIO_TYPE*) GPIOD_BASE)


























