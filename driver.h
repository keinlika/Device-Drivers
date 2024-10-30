// bitmask macros
#define bit(x) (1<<(x))
#define bitpair(x) (0b11 << (x*2))
#define ubit(x) (0b10 << (x*2))
#define lbit(x) (0b01 << (x*2))

// GPIO Port struct
typedef struct {
  unsigned int MODER;   // offset: 0x00
  unsigned int OTYPER;  // offset: 0x04
  unsigned int OSPEEDR; // offset: 0x08
  unsigned int PUPDR;   // offset: 0x0C
  unsigned int IDR;     // offset: 0x10
  unsigned int ODR;     // offset: 0x14
} Port;

// Base addresses of the GPIO Port control registers
unsigned int* AHB2ENR = (unsigned int*) 0x4002104c;
Port* GPIOA = (Port*) 0x48000000; // base address of GPIOA
Port* GPIOB = (Port*) 0x48000400; // base address of GPIOB
Port* GPIOC = (Port*) 0x48000800; // base address of GPIOC


// configure as input
void GPIO_configure_input_mode(Port* GPIOx, unsigned int pin){

	// reset both bits for this pin tin the MODE register
	GPIOx->MODER &= ~bitpair(pin);

	return;
}

//configures a pin as output
void GPIO_configure_output_mode(Port* GPIOx, unsigned int pin){

		unsigned int temp = GPIOx->MODER;
		temp &= ~ubit(pin);     // Reset the upper bit for this pin in PUPDR
	    temp |= lbit(pin);      // Set the bits for pull-up in PUPDR
	    GPIOx->MODER = temp;
}

// enables the clock from GPIO port A
void GPIOA_enable_clock(void){

	//GPIO Clock enable register
	unsigned int* RCC_AHB2ENR = (unsigned int*) 0x4002104c;

	// reset both bits for this pin in the MODE resgiester
	*RCC_AHB2ENR |= 0b01;
	return;
}


void GPIOB_enable_clock(void){

	//GPIO Clock enable register
	unsigned int* RCC_AHB2ENR = (unsigned int*) 0x4002104c;

	// set  bit 0 for PORT A
	*RCC_AHB2ENR |= 0b10;
	return;
}

void GPIOC_enable_clock(void){

	//GPIO Clock enable register
	unsigned int* RCC_AHB2ENR = (unsigned int*) 0x4002104c;

	// set  bit 0 for PORT A
	*RCC_AHB2ENR |= 0b100;
	return;
}


// enable pull-up resister
void GPIO_enable_pull_up_resistor(Port* GPIOx, unsigned int pin) {
	unsigned int temp = GPIOx->PUPDR;
    temp |= lbit(pin);      // Set the bits for pull-up in PUPDR
	temp &= ~ubit(pin);     // Reset the upper bit for this pin in PUPDR
    GPIOx->PUPDR = temp;

    return;
}

// enable pull-down resister
void GPIO_enable_pull_down_resistor(Port* GPIOx, unsigned int pin) {
	unsigned int temp = GPIOx->PUPDR;
    temp |= ubit(pin);       // Set the lower bit for this pin in PUPDR
    temp &= ~lbit(pin);      // Reset the upper  the bits for pull-down in PUPDR
    GPIOx->PUPDR = temp;

    return;
}

// disable pull down resister
void GPIO_disable_pull_resistor(Port* GPIOx, unsigned int pin) {
	unsigned int temp = GPIOx->PUPDR;
    temp &= ~ubit(pin);  // Clear the bits for this pin in PUPDR
    temp &= ~lbit(pin);  // Clear the bits for this pin in PUPDR
    GPIOx->PUPDR = temp;

    return;
}


void GPIO_write_pin(Port* GPIOx, unsigned int pin, unsigned int state){
	if (state){
		GPIOx->ODR |= bit(pin); // set bit
	}
	else {
		GPIOx->ODR &= ~bit(pin); // reset bit
	}

	return;
}

unsigned int GPIO_read_pin(Port* GPIOx, unsigned int pin){
	if ((GPIOx->IDR & bit(pin)) == 0){
		return 0;
	}
	else{
		return 1;
	}
}
