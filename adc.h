//adc.h
#include "types.h"
void Init_ADC(void);
//f32 Read_ADC(u8 chNo);
void Read_ADC(u8 chNo,u32 *adcDVal,f32 *eAR);
