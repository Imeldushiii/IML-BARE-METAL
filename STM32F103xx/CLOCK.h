#define FLASH_ACR       (*(volatile uint32_t*)(0x40022000))
#define HSON (1 << 16)
#define HSONRDY (1 << 17)
#define PLLRDY (1 << 25)

typedef struct {
    volatile uint32_t CLOCK_CR;
    volatile uint32_t CLOCK_CFGR;
    volatile uint32_t CLOCK_CIR;
    volatile uint32_t CLOCK_APB2RSTR;
    volatile uint32_t CLOCK_APB1RSTR;
    volatile uint32_t CLOCK_AHBENR;
    volatile uint32_t CLOCK_APB2ENR;
    volatile uint32_t CLOCK_APB1ENR;
    volatile uint32_t CLOCK_BDCR;
    volatile uint32_t CLOCK_CSR;
} CLOCK_type;

#define Clock       ((CLOCK_type*) RCC_BASE)
#define CLOCK_SOURCE_HSI    0
#define CLOCK_SOURCE_HSE    1
#define CLOCK_SOURCE_PLL    2

typedef struct {
    uint8_t PLLSource;    // 0 = HSI/2, 1 = HSE
    uint8_t PLLMul;       // Mnożnik PLL (2-16, patrz dokumentacja)
} PLL_Config;
void IML_SystemClock_Init(uint8_t clock_source, PLL_Config *pll_config);

void IML_SystemClock_Init(uint8_t clock_source, PLL_Config *pll_config){
    Clock->CLOCK_CR |= (1 << 0);
    while (!(Clock->CLOCK_CR & (1 << 1)));
    if (clock_source == CLOCK_SOURCE_PLL) {
        Clock->CLOCK_CFGR &= ~((0xF << 18) | (1 << 16)); // Wyczyść PLLMUL i PLLSRC
        Clock->CLOCK_CFGR |= (pll_config->PLLMul << 18) | (pll_config->PLLSource << 16);
        Clock->CLOCK_CR |= (1 << 24);
        while (!(Clock->CLOCK_CR & (1 << 25)));
        FLASH_ACR |= (0x2 << 0);
        Clock->CLOCK_CFGR &= ~(0x3);
        Clock->CLOCK_CFGR |= (0x2);
        while ((Clock->CLOCK_CFGR & (0xC)) != (0x8));
        
    }

}
