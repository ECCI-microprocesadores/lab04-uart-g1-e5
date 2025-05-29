#include "uart.h"
#include <stdio.h>

void UART_Init(void) {
    TRISC6 = 0; // TX como salida
    TRISC7 = 1; // RX como entrada

    SPBRG1 = 103; // Baudrate 9600 para Fosc = 64MHz
    TXSTA1bits.BRGH = 1; // Alta velocidad (BRGH = 1)
    BAUDCON1bits.BRG16 = 1; // 16 bits del generador de baudrate

    RCSTA1bits.SPEN = 1; // Habilita el módulo serial
    TXSTA1bits.SYNC = 0; // Modo asíncrono
    TXSTA1bits.TXEN = 1; // Habilita transmisión
    RCSTA1bits.CREN = 1; // Habilita recepción

    PIE1bits.RC1IE = 1;   // Habilita interrupción por recepción UART
    PIR1bits.RC1IF = 0;   // Limpia bandera
    INTCONbits.PEIE = 1;  // Habilita interrupciones periféricas
    INTCONbits.GIE = 1;   // Habilita interrupciones globales
}

void UART_WriteChar(char data) {
    while (!TXSTA1bits.TRMT); // Espera a que se vacíe el buffer de transmisión
    TXREG1 = data;
}

void UART_WriteString(const char* str) {
    while (*str) {
        UART_WriteChar(*str++);
    }
}

void UART_WriteUInt(uint16_t value) {
    char buffer[6];
    uint8_t i = 0;
    
    do {
        buffer[i++] = (value % 10) + '0';
        value /= 10;
    } while (value > 0);
    
    while (i > 0) {
        UART_WriteChar(buffer[--i]);
    }
}

void UART_WriteVoltage(uint16_t adcValue) {
    float voltage = (adcValue * 5.0) / 1023.0;
    int integerPart = (int)voltage;
    int decimalPart = (int)((voltage - integerPart) * 100);
    
    UART_WriteUInt(integerPart);
    UART_WriteChar('.');
    if (decimalPart < 10) UART_WriteChar('0');
    UART_WriteUInt(decimalPart);
}