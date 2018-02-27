/*
 * uart.h
 *
 * Created: 18/03/17 13:13:39
 *  Author: Sondre
 */ 


#ifndef UART_H_
#define UART_H_

#include <avr/io.h>
#include <stdlib.h>
#include <stdio.h>

void uart_init();
void uart_tx_char(char c,  FILE* stream);

#endif /* UART_H_ */