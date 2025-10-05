//EXTERNAL_INTERRUPTS.c^M
/*^M
#include <lpc21xx.h>^M
#include "pin_function_defines.h"^M
#include "defines.h"^M
#include "delay.h"^M
^M
void eint0_isr(void) __irq;^M
void eint1_isr(void) __irq;^M
^M
void Enable_EINT0(void);^M
void Enable_EINT1(void);^M
^M
unsigned int count;^M
^M
#define AL_LED_8 14^M
#define L_SW 8^M
#define R_SW 9^M
^M
#define EINT0_LED 10^M
#define EINT1_LED 11^M
*/
/* external_interrupts_test2.c */

#include <lpc21xx.h>
#include "pin_function_defines.h"
#include "defines.h"

#define AL_LED_8 21
#define EINT0_LED 10
#define EINT1_LED 11

//#define EINT2_LED 12^M
//#define EINT3_LED 13^M

void delay_ms(unsigned dlyMS);
void eint0_isr(void) __irq;
void eint1_isr(void) __irq;
//void eint2_isr(void) __irq;^M
//void eint3_isr(void) __irq;^M
void Enable_EINT0(void);
void Enable_EINT1(void);
//void Enable_EINT2(void);^M
//void Enable_EINT3(void);^M

unsigned int count;
int main()
{

    Enable_EINT0();

    Enable_EINT1();
    while(1);

    //Enable_EINT2();^M
    //Enable_EINT3();^M
}

void eint0_isr(void) __irq
{
    int i;
    for(i=0;i<=16;i++)
    {
        IOSET0 = 0X0F<<AL_LED_8;                                                                                                                   ^M
        IOCLR0 = i<<AL_LED_8;
        //delay_ms(10);
        IOCLR0 = 0XF0<<AL_LED_8;
    }
    CPLBIT(IOPIN0,EINT0_LED);//isr activity^M
    SSETBIT(EXTINT,0);//clear EINT0 flag^M
    VICVectAddr=0;//dummy write to clear ^M
    //interrupt flag in VIC^M
    delay_ms(100);

}

void eint1_isr(void) __irq
{
    int i;
    for(i=256;i>=17;i--)
    {
        IOSET0 = 0XF0<<AL_LED_8;
        IOCLR0 = i<<AL_LED_8;
        //delay_ms(10);^M
        IOCLR0 = 0X0F<<AL_LED_8;
    }
    CPLBIT(IOPIN0,EINT1_LED);//isr activity^M
    SSETBIT(EXTINT,1);//clear EINT1 flag^M
    VICVectAddr=0;//dummy write;^M
    delay_ms(100);
}

void Enable_EINT0(void)
{
    CFGPIN(PINSEL0,1,FUNC4);
    SETBIT(IODIR0,EINT0_LED);
    SSETBIT(VICIntEnable,14);
    VICVectCntl0=0x20|14;
    VICVectAddr0=(unsigned)eint0_isr;
    SCLRBIT(EXTINT,0);
    SETBIT(EXTMODE,0);
    SETBIT(EXTPOLAR,0);
}

void Enable_EINT1(void)
{
    CFGPIN(PINSEL0,3,FUNC4);
    SETBIT(IODIR0,EINT1_LED);
    SSETBIT(VICIntEnable,15);
    VICVectCntl1=0x20|15;
    VICVectAddr1=(unsigned)eint1_isr;
    SCLRBIT(EXTINT,1);
    SETBIT(EXTMODE,1);
    SETBIT(EXTPOLAR,1);
}