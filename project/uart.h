/*
 * uart.h
 *
 * Created: 18/03/17 13:13:39
 *  Author: Jorgejac
 */ 

#ifndef UART_H_
#define UART_H_
typedef enum {
	BAUD_300 = 0x682,
	BAUD_600 = 0x340,
	BAUD_1200 = 0x1A0,
	BAUD_2400 = 0x0CF,
	BAUD_4800 = 0x067,
	BAUD_9600 = 0x033,
	BAUD_19200 = 0x019,
	BAUD_38400 = 0x00C,
	BAUD_250000 = 0x001,
	BAUD_500000 = 0x000
} baud_t;


void uart0_init(baud_t ubrr);
void uart0_transmit(char c);
void uart0_transmit_str(char * data);
unsigned char uart0_receive();
int uart0_has_new_message();


#endif /* UART_H_ */