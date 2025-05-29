#ifndef ADC_H
#define ADC_H

#include <xc.h>

#define VREF 5.0        // Voltaje de referencia del ADC

void setupADC(void);
unsigned int readADC(void);
float readVoltage(void);

#endif