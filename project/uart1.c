#include "uart1.h"
#include <avr/io.h>
#include <stdlib.h>
#include <stdio.h>

void uart_init()
{
	const uint32_t baud_rate = 500000;
	UBRR1 = (F_CPU / 16) / baud_rate - 1;
	UCSR1C = (3 << UCSZ0);	// 8 bit transfer
	UCSR1B |= (1 << TXEN1); // Enable transmit only
}

void uart_tx_char(char c, FILE * stream)
{
	while (!(UCSR1A & (1 << UDRE1))) { }; // Wait until data register is empty
	UDR1 = c;
}