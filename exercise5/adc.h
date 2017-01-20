#ifndef _ADC_H
#define _ADC_H
#define  Vref   5000
extern void ADC_Init(uint8_t Channel);
extern uint32_t ADC_Read(uint8_t Channel);
#endif