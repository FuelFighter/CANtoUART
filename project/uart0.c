/*
 * uart.c
 *
 * Created: 18/03/17 13:13:47
 *  Author: Sondre
 */ 

#include "uart0.h"
#include <avr/io.h>
#include <stdlib.h>

void uart_init()
{
	const uint32_t baud_rate = 500000;
	UBRR0 = (F_CPU / 16) / baud_rate - 1;
	UCSR0C = (3 << UCSZ0);	// 8 bit transfer
	UCSR0B |= (1 << TXEN0); // Enable transmit only
}

void uart_tx_char(char c, FILE * stream)
{
	while (!(UCSR0A & (1 << UDRE0))) { }; // Wait until data register is empty
	UDR0 = c;
}
