#include "ADC.h"

void setupADC(void) {
    TRISA0 = 1;         // RA0 como entrada
    ANSELAbits.ANSA0 = 1; // Habilita RA0 como analógico
    ADCON0 = 0b00000001; // ADC ON, canal AN0
    ADCON1 = 0b00110000; // Justificación derecha, VDD/VSS como referencia
    ADCON2 = 0b10101110; // Tiempo de adquisición 12 TAD, Fosc/64
}

unsigned int readADC(void) {
    ADCON0bits.GO = 1;
    while(ADCON0bits.GO);
    return ((ADRESH << 8) | ADRESL);
}

float readVoltage(void) {
    unsigned int adcValue = readADC();
    return (adcValue * VREF) / 1023.0;
}