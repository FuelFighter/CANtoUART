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
#include "uart1.h"

CanMessage_t rxFrame;
void transmit_can_to_serial(CanMessage_t *dataFrame);

int main(void)
{	
	uart_init();
	can_init(0,0);
	fdevopen(uart_tx_char,NULL);
	
	sei();
	
    while (1) 
    {
		if (can_read_message_if_new(&rxFrame))
		{
			transmit_can_to_serial(&rxFrame);
		}
    }
}

void transmit_can_to_serial(CanMessage_t *dataFrame)
{
	printf("[%03X:%d:", dataFrame->id,dataFrame->length);
	
	for(int i = 0; i < dataFrame->length; i++)
	{
		printf("%02X", dataFrame->data.u8[i]);
	}
	
	printf("]\n");
}
