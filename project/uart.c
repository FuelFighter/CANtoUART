#include "uart.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdio.h>

#define UART0_RX_BUFFER_SIZE 32     /* 2,4,8,16,32,64,128 or 256 bytes */
#define UART0_TX_BUFFER_SIZE 32
#define UART0_RX_BUFFER_MASK (UART0_RX_BUFFER_SIZE - 1)
#define UART0_TX_BUFFER_MASK (UART0_RX_BUFFER_SIZE - 1)

/* Static Variables */
static unsigned char UART0_RxBuf[UART0_RX_BUFFER_SIZE];
static volatile unsigned char UART0_RxHead;
static volatile unsigned char UART0_RxTail;
static unsigned char UART0_TxBuf[UART0_TX_BUFFER_SIZE];
static volatile unsigned char UART0_TxHead;
static volatile unsigned char UART0_TxTail;

void uart0_init(baud_t ubrr)
{
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;
	
	UCSR0C = (3 << UCSZ0);	// 8 bit transfer
	UCSR0B |= (1 << TXEN0)|(1 << RXEN0)|(1 << RXCIE0);
	
	UART0_RxHead = 0;
	UART0_RxTail = 0;
	UART0_TxHead = 0;
	UART0_TxTail = 0;
}

void uart0_transmit(char c)
{
		unsigned char tmphead;
		/* Calculate buffer index */
		tmphead = (UART0_TxHead + 1) & UART0_TX_BUFFER_MASK;
		/* Wait for free space in buffer */
		while (tmphead == UART0_TxTail);
		/* Store data in buffer */
		UART0_TxBuf[tmphead] = c;
		/* Store new index */
		UART0_TxHead = tmphead;
		/* Enable UDRE interrupt */
		UCSR0B |= (1<<UDRIE0);
}

void uart0_transmit_str(char * data)
{
	unsigned char tmphead;
	for (size_t byte = 0; byte < strlen(data); byte++)
	{
		/* Calculate buffer index */
		tmphead = (UART0_TxHead + 1) & UART0_TX_BUFFER_MASK;
		/* Wait for free space in buffer */
		while (tmphead == UART0_TxTail);
		/* Store data in buffer */
		UART0_TxBuf[tmphead] = data[byte];
		/* Store new index */
		UART0_TxHead = tmphead;
	}
	/* Enable UDRE interrupt */
	UCSR0B |= (1<<UDRIE0);
}

unsigned char uart0_receive()
{
	unsigned char tmptail;
	
	/* Wait for incoming data */
	while (UART0_RxHead == UART0_RxTail);
	/* Calculate buffer index */
	tmptail = (UART0_RxTail + 1) & UART0_RX_BUFFER_MASK;
	/* Store new index */
	UART0_RxTail = tmptail;
	/* Return data */
	return UART0_RxBuf[tmptail];
}

int uart0_has_new_message()
{
	if (UART0_RxHead != UART0_RxTail) return 1;
	return 0;
}

ISR(USART0_RX_vect)
{
	unsigned char data;
	unsigned char tmphead;
	
	/* Read the received data */
	data = UDR0;
	/* Calculate buffer index */
	tmphead = (UART0_RxHead + 1) & UART0_RX_BUFFER_MASK;
	/* Store new index */
	UART0_RxHead = tmphead;

	if (tmphead == UART0_RxTail) {
		/* ERROR! Receive buffer overflow */
	}
	/* Store received data in buffer */
	UART0_RxBuf[tmphead] = data;
}

ISR(USART0_UDRE_vect)
{
	unsigned char tmptail;

	/* Check if all data is transmitted */
	if (UART0_TxHead != UART0_TxTail) 
	{
		/* Calculate buffer index */
		tmptail = ( UART0_TxTail + 1 ) & UART0_TX_BUFFER_MASK;
		/* Store new index */
		UART0_TxTail = tmptail;
		/* Start transmission */
		UDR0 = UART0_TxBuf[tmptail];
	} else {
		/* Disable UDRE interrupt */
		UCSR0B &= ~(1<<UDRIE0);
	}
}