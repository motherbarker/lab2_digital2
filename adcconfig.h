
#ifndef ADCCONFIG_H
#define	ADCCONFIG_H

#include <xc.h>

void adc_init(uint8_t J, uint8_t R, uint8_t clock, uint8_t channel);
uint16_t adc_read(void);
void adc_sel_channel(uint8_t channel);
uint8_t adc_get_channel(void);


#endif	/* ADC_LIB_H */