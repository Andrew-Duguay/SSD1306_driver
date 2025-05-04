#include "uart.h"

#define USART2EN			(1U<<17)
#define GPIOAEN				(1U<<0)
#define CR1_TE				(1U<<3)
#define CR1_RE				(1U<<2)
#define CR1_UE				(1U<<13)
#define SR_TXE				(1U<<7)
#define SR_RXNE				(1U<<5)

#define SYS_FREQ			16000000
#define APB1_CLK			SYS_FREQ
#define UART_BAUDRATE		115200


void uart2_write(int ch);
static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t periphClk, uint32_t baudrate);
static uint32_t compute_uart_bd(uint32_t periphClk, uint32_t baudrate);

int __io_putchar(int ch){
	uart2_write(ch);
	return ch;
}

void uart2_write(int ch){
	//ensure transmit data register is empty
	while(!(USART2->SR & SR_TXE)){};
	//write to transmit data register
	USART2->DR = (ch & 0xFF);
}

char uart2_read(void){
	while(!(USART2->SR & SR_RXNE)){};
	return USART2->DR;
}

static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t periphClk, uint32_t baudrate){
	USARTx->BRR = compute_uart_bd(periphClk, baudrate);
}

static uint32_t compute_uart_bd(uint32_t periphClk, uint32_t baudrate){
	return ((periphClk + (baudrate/2))/baudrate);
}

void uart2_rxtx_init(void){
	//configure UART GPIOA
	//enable clock access to GPIOA
	RCC->AHB1ENR |= GPIOAEN;

	//set PA2 to alternate function mode
	GPIOA->MODER &=~ (1U<<4);
	GPIOA->MODER |=  (1U<<5);

	//set PA3 to alternate function mode
	GPIOA->MODER &=~ (1U<<6);
	GPIOA->MODER |=  (1U<<7);

	//Set alternate function of PA2 to AF7
	GPIOA->AFR[0] |=  (1U<<8);
	GPIOA->AFR[0] |=  (1U<<9);
	GPIOA->AFR[0] |=  (1U<<10);
	GPIOA->AFR[0] &=~ (1U<<11);
	//Set alternate function of PA2 to AF7
	GPIOA->AFR[0] |=  (1U<<12);
	GPIOA->AFR[0] |=  (1U<<13);
	GPIOA->AFR[0] |=  (1U<<14);
	GPIOA->AFR[0] &=~ (1U<<15);

	//Enable clock access to UART2
	RCC->APB1ENR |= USART2EN;

	//Configure baudrate
	uart_set_baudrate(USART2, APB1_CLK, UART_BAUDRATE);

	//Configure transfer direction
	USART2->CR1 = (CR1_TE | CR1_RE);

	//enable UART module
	USART2->CR1 |= CR1_UE;

}
