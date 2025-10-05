//adc_test.c
#include "adc.h"

f32 eAR;
u32 adcDVal;
main()
{
	Init_ADC();
	while(1)
	{
		Read_ADC(0,&adcDVal,&eAR);
	}
}
