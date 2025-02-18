
// Adres bazowy peryferiów strona 51/ 3.3 Memory Map
#define PERIPH_BASE        0x40000000U
#define RCC_BASE           (PERIPH_BASE + 0x21000U)
#define RCC_APB2ENR        *(volatile uint32_t*)(RCC_BASE + 0x18U)
#define RCC_APB1ENR        *(volatile uint32_t*)(RCC_BASE + 0x1CU)

/* 4x4_offr https://pl.rakko.tools/tools/68/
  ####    #####     ####     ####
 ##  ##   ##  ##     ##     ##  ##
 ##       ##  ##     ##     ##  ##
 ## ###   #####      ##     ##  ##
 ##  ##   ##         ##     ##  ##
 ##  ##   ##         ##     ##  ##
  ####    ##        ####     ####
*/
#define GPIOA_BASE         (PERIPH_BASE + 0x10800U)
#define GPIOB_BASE         (PERIPH_BASE + 0x10C00U)
#define GPIOC_BASE         (PERIPH_BASE + 0x11000U)
#define GPIOD_BASE         (PERIPH_BASE + 0x11400U)
#define GPIOE_BASE         (PERIPH_BASE + 0x11800U)
#define GPIOF_BASE         (PERIPH_BASE + 0x11C00U)
#define GPIOG_BASE         (PERIPH_BASE + 0x12000U)

#define RCC_APB2ENR_IOPAEN (1 << 2)  // GPIOA
#define RCC_APB2ENR_IOPBEN (1 << 3)  // GPIOB
#define RCC_APB2ENR_IOPCEN (1 << 4)  // GPIOC
#define RCC_APB2ENR_IOPDEN (1 << 5)  // GPIOD
#define RCC_APB2ENR_IOPEEN (1 << 6)  // GPIOE
#define RCC_APB2ENR_IOPFEN (1 << 7)  // GPIOF
#define RCC_APB2ENR_IOPGEN (1 << 8)  // GPIOG


typedef struct {
    
    volatile uint32_t CRL;     // Konfiguracja pinów 0-7
    volatile uint32_t CRH;     // Konfiguracja pinów 8-15
    volatile uint32_t IDR;     // Rejestr wejścia
    volatile uint32_t ODR;     // Rejestr wyjścia
    volatile uint32_t BSRR;    // Rejestr atomowego ustawiania/resetowania
    volatile uint32_t BRR;     // Rejestr resetowania (tylko F1)
    volatile uint32_t LCKR;
}   GPIO_type;



#define GPIOA   ((GPIO_type*)GPIOA_BASE)
#define GPIOB   ((GPIO_type*)GPIOB_BASE)
#define GPIOC   ((GPIO_type*)GPIOC_BASE)
#define GPIOD   ((GPIO_type*)GPIOD_BASE)
#define GPIOE   ((GPIO_type*)GPIOE_BASE)
#define GPIOF   ((GPIO_type*)GPIOF_BASE)
#define GPIOG   ((GPIO_type*)GPIOG_BASE)
/*
 ##  ##    ####      ##     #####    ######
 ##  ##   ##  ##    ####    ##  ##     ##
 ##  ##   ##       ##  ##   ##  ##     ##
 ##  ##    ####    ######   #####      ##
 ##  ##       ##   ##  ##   ####       ##
 ##  ##   ##  ##   ##  ##   ## ##      ##
  ####     ####    ##  ##   ##  ##     ##
*/

#define RCC_APB2ENR_USART1EN  (1 << 14)
#define RCC_APB1ENR_USART2EN  (1 << 17)
#define RCC_APB1ENR_USART3EN  (1 << 18)
#define RCC_APB1ENR_UART4EN  (1 << 19)
#define RCC_APB1ENR_UART5EN  (1 << 20)

