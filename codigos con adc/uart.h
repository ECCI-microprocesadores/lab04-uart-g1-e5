#ifndef UART_H
#define UART_H

#include <xc.h>
#include <stdint.h>

#define _XTAL_FREQ 64000000UL

void UART_Init(void);
void UART_WriteChar(char data);
void UART_WriteString(const char* str);
void UART_WriteUInt(uint16_t value);
void UART_WriteVoltage(uint16_t adcValue);

#endif