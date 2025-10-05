//FUEL_NODE.c

#include "delay.h"
#include "lcd_defines.h"
#include "lcd.h"
#include "adc.h"
#include "adc_defines.h"
#include "types.h"
#include "interrupt.h"
#include "can.h"
#include "can_defines.h"

f32 result;
f32 eAR_voltage;
u32 fuel_per;
u32 VMIN,VMAX;
f32 ch0;


int main()
{
    CANF txF;
    Init_CAN1();
    InitLCD();
    Init_ADC();
    txF.ID=1;
    txF.vbf.RTR=0;
    txF.vbf.DLC=0x4;
    txF.Data1=1;
    txF.Data2=0;
    cmdLCD(0x0f);
    while(1)
    {

        /*eAR_voltage = Read_ADC(ch0);
        cmdLCD(GOTO_LINE1_POS0);
        strLCD("Voltage: ");
        cmdLCD(GOTO_LINE1_POS0+9);
        F32LCD(eAR_voltage, 3);
        strLCD(" V\r\n");
        fuel_per = ((eAR_voltage - VMIN) * 100) / (VMAX - VMIN);
        if(fuel_per>=100)
        {
            fuel_per=100;
        }
        else if(fuel_per<=0)
        {
            fuel_per=0;
        }
        delay_ms(500);
        if(fuel_per>=100)
        {
            fuel_per=100;
        }
        else if(fuel_per<=0)
        {
            fuel_per=0;
        }
        */

        result = Read_ADC(0x01);  //setting channel 1 for reading
        cmdLCD(0x80);
        F32LCD(result,4);
        //delay_s(1);
        fuel_per = ((result-0.28)/(2.19-0.28))*100;
        if(fuel_per>=100)
        {
            fuel_per=100;
        }
        else if(fuel_per<=0)
        {
            fuel_per=0;
        }
        //cmdLCD(GOTO_LINE1_POS0);
        //      u32LCD(fuel_per);
        delay_ms(100);
        //cmdLCD(CLEAR_LCD);
        txF.Data1=fuel_per;
        txF.Data2=0;
        CAN1_Tx(txF);
        txF.Data1=((~txF.Data1)&0x0);
    }
}