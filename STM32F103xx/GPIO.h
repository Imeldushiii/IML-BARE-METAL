#ifndef GPIO_H
#define GPIO_H
#endif







//32 bity = 4 bajty, idealnie wtedy jest i tak po kolei 


//Jak nie damy wartości, to wartosci dadza sie po kolei np, 1,2,3,4
typedef enum {
    GPIO_MODE_INPUT,
    GPIO_MODE_OUTPUT_10MHZ,
    GPIO_MODE_OUTPUT_20MHZ,
    GPIO_MODE_OUTPUT_50MHZ
}  GPIO_mode;

typedef enum {
    GPIO_CNF_INPUT_ANALOG,    // Wejście analogowe
    GPIO_CNF_INPUT_FLOATING,  // Wejście bez podciągania
    GPIO_CNF_INPUT_PULL,      // Wejście z podciąganiem
    GPIO_CNF_OUTPUT_PUSHPULL, // Wyjście push-pull
    GPIO_CNF_OUTPUT_OPENDRAIN

} GPIO_config;
// Rejestry RCC strona 114/ 7.3.7 APB2 clock enable register




/*


 #####    ##  ##   ##  ##    ####    ######    ####     ####    ##  ##    #####
 ##       ##  ##   ### ##   ##  ##     ##       ##     ##  ##   ### ##   ##
 ####     ##  ##   ######   ##         ##       ##     ##  ##   ######    ####
 ##       ##  ##   ## ###   ##  ##     ##       ##     ##  ##   ## ###       ##
 ##        ####    ##  ##    ####      ##      ####     ####    ##  ##   #####




*/
void IML_GPIO_Init(GPIO_type *gpiox, uint8_t pin, GPIO_mode mode, GPIO_config config);
void IML_GPIO_WritePin(GPIO_type *gpiox, uint8_t pin, uint8_t state);
uint8_t IML_GPIO_ReadPin(GPIO_type *gpiox, uint8_t pin);
void IML_GPIO_TogglePin(GPIO_type *gpiox, uint8_t pin);


void IML_GPIO_Init(GPIO_type *gpiox, uint8_t pin, GPIO_mode mode, GPIO_config config) {
    volatile uint32_t *configRegister;
    uint8_t pinPosition;
    if (pin < 8) {
        configRegister = &gpiox->CRL;
        pinPosition = pin * 4;
    }
    else {
        configRegister = &gpiox->CRH;
        pinPosition = (pin - 8) * 4;
    }
    *configRegister &= ~(0xF << pinPosition);
    *configRegister |= (mode << pinPosition);

}

void IML_GPIO_WritePin(GPIO_type *gpiox, uint8_t pin, uint8_t state) {
    if (state) {
        gpiox->BSRR = (1 << pin);
    }
    else {
        gpiox->BRR = (1 << pin);
    }
}
uint8_t IML_GPIO_ReadPin(GPIO_type *gpiox, uint8_t pin) {
    return (gpiox->IDR & (1 << pin)) ? 1 : 0;

}
void IML_GPIO_TogglePin(GPIO_type *gpiox, uint8_t pin){
    gpiox->ODR ^= (1 << pin);
}

 // STM32F103C8T6_H