

#ifndef Clock_speed

#define Clock_speed 8000000
#endif

#define USART1_BASE        (PERIPH_BASE + 0x13800U)
#define USART2_BASE        (PERIPH_BASE + 0x04400U)
#define USART3_BASE        (PERIPH_BASE + 0x04800U)
#define UART4_BASE         (PERIPH_BASE + 0x04C00U)
#define UART5_BASE         (PERIPH_BASE + 0x05000U)


typedef struct {
    volatile uint32_t USART_SR;
    volatile uint32_t USART_DR;
    volatile uint32_t USART_BRR;
    volatile uint32_t USART_CR1;
    volatile uint32_t USART_CR2;
    volatile uint32_t USART_CR3;
    volatile uint32_t USART_GTPR;
} USART_TYPE;

#define USART1 ((USART_TYPE*)USART1_BASE)
#define USART2 ((USART_TYPE*)USART2_BASE)
#define USART3 ((USART_TYPE*)USART3_BASE)
#define UART4  ((USART_TYPE*)UART4_BASE)
#define UART5  ((USART_TYPE*)UART5_BASE)

/* 
PROBLEMY SĄ Z TYMI GPIOA, BO GDY ZMIENIŁEM NA GPIOD ALBO CO INNEGO TO NAGLE WSZYSTKO DZIALA
*/
typedef struct  {
    USART_TYPE *Instance;
    uint32_t BaudRate;
    uint16_t TxPin;
    uint16_t RxPin;
    GPIO_type *GPIOport;
 
}   UART_CONFIG;
/*


TODO
TE REJESTRY NIZEJ SPRAWDZ BO APB2ENR NIE WSZYSTKO TO UART


*/
void* USART_instances[] = {USART1, USART2, USART3, UART4, UART5};
uint32_t USART_enable_bits[] = {RCC_APB2ENR_USART1EN, RCC_APB1ENR_USART2EN, RCC_APB1ENR_USART3EN, RCC_APB1ENR_UART4EN, RCC_APB1ENR_UART5EN};
size_t USART_num_instances = sizeof(USART_instances) / sizeof(USART_instances[0]);

void* GPIO_instances[] = {GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, GPIOF, GPIOG};
uint32_t GPIO_enable_bits[] = {RCC_APB2ENR_IOPAEN,RCC_APB2ENR_IOPBEN,RCC_APB2ENR_IOPCEN,RCC_APB2ENR_IOPDEN,RCC_APB2ENR_IOPEEN,RCC_APB2ENR_IOPFEN,RCC_APB2ENR_IOPGEN};
size_t GPIO_num_instances = sizeof(GPIO_instances) / sizeof(GPIO_instances[0]);


void IML_UART_Init(const UART_CONFIG *config);
void IML_UART_SEND_CHAR(const UART_CONFIG *config, uint8_t data);
uint8_t IML_UART_RECEIVE_CHAR(const UART_CONFIG * config);
void IML_UART_SendString(const UART_CONFIG *config, const char *str);


void IML_UART_Init(const UART_CONFIG *config) {
    
    //USART
    for (size_t i = 0; i < USART_num_instances; i++) {
        if (config->Instance == USART_instances[i]) {
            RCC_APB2ENR |= USART_enable_bits[i];
            break;
        }
    }
    //GPIO
    for (size_t i = 0; i < GPIO_num_instances; i++) {
        if (config->GPIOport == GPIO_instances[i]) {
            RCC_APB2ENR |= GPIO_enable_bits[i];
            break;
        }
    }
        // TX
    if(config->TxPin < 8) {
        config->GPIOport->CRL &= ~(0xF << (config->TxPin * 4));
        config->GPIOport->CRL |= (0xB << (config->TxPin * 4));
        
        
    }
    else {
        config->GPIOport->CRH &= ~(0xF << ((config->TxPin - 8) * 4));
        config->GPIOport->CRH |= (0xB << ((config->TxPin - 8) * 4));
    }

    // RX

    if (config->RxPin < 8) {
        config->GPIOport->CRL &= ~(0xF << (config->RxPin * 4));
        config->GPIOport->CRL |= (0x4 << (config->RxPin * 4));
    }
    else {
        config->GPIOport->CRH &= ~(0xF << ((config->RxPin - 8) * 4));
        config->GPIOport->CRH |= (0x4 << ((config->RxPin - 8) * 4));

    }
    //br
    
    config->Instance->USART_BRR = (Clock_speed + (config->BaudRate / 2)) / config->BaudRate;
    config->Instance->USART_CR1 |= (1 << 13) | (1 << 3) | (1 << 2);
    // CONFIG
}
void IML_UART_SEND_CHAR(const UART_CONFIG *config, uint8_t data) {
    while (!(config->Instance->USART_SR & (1 << 7)));
    config->Instance->USART_DR = data;

}
void IML_UART_SendString(const UART_CONFIG *config, const char *str) {
    while (*str) {
        IML_UART_SEND_CHAR(config, *str++);
    }
}
uint8_t IML_UART_RECEIVE_CHAR(const UART_CONFIG * config) {
    while (!(config->Instance->USART_SR & (1 << 5)));
    return config->Instance->USART_DR & 0xFF;
}




//NEVER MIND
