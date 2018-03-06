/*
 * project.c
 *
 * Created: 27.02.2018 18:25:08
 * Author : Jorgeja
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "UniversalModuleDrivers/can.h"
#include "UniversalModuleDrivers/uart.h"
#include "UniversalModuleDrivers/can_uart.h"

CanMessage_t rxFrame;
CanMessage_t txFrame;

int main(void)
{	
	can_init(0,0);
	// Initiate UART0_USB
	uart_init(BAUD_500000,DISABLED);
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

