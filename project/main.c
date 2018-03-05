/*
 * project.c
 *
 * Created: 27.02.2018 18:25:08
 * Author : Ultrawack
 */ 
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "can.h"
#include "uart.h"
#include "can_uart.h"

CanMessage_t rxFrame;
CanMessage_t txFrame;
void transmit_can_to_serial(CanMessage_t *dataFrame);

int main(void)
{	
	can_init(0,0);
	can_uart_init(UART0_USB);
	sei();
	
    while (1) 
    {
		if (can_read_message_if_new(&rxFrame))
		{
			can_to_uart(&rxFrame);
		}
		uart_to_can_if_new(&txFrame);
    }
}

