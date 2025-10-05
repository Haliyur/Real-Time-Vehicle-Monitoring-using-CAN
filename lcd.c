//lcd.c
#include <LPC21xx.h>
#include "types.h"
#include "delay.h"
#include "lcd_defines.h"
void WriteLCD(u8 byte)
{
	//select write operations
	IOCLR0=1<<LCD_RW;
	//write any byte onto d0 to d7
	IOPIN0=((IOPIN0&~(0xFF<<LCD_DATA))|
	       (byte<<LCD_DATA));
	//apply high to low on enable
	IOSET0=1<<LCD_EN;
	delay_us(1);
	IOCLR0=1<<LCD_EN;
	
	delay_ms(2);
}

void CmdLCD(u8 cmd)
{
	//select cmd reg
	IOCLR0=1<<LCD_RS;
	//write to cmd reg
	WriteLCD(cmd);
}

void CharLCD(u8 ascii)
{
	//select data reg
	IOSET0=1<<LCD_RS;
	//write to ddram via data reg
	WriteLCD(ascii);
}

void InitLCD(void)
{
	//cfg p0.8(d0) to p0.15(d7),rs,rw,en as gpio out
	IODIR0|=((0xFF<<LCD_DATA)|
	         (1<<LCD_RS)|(1<<LCD_RW)|(1<<LCD_EN));
	
	delay_ms(15);
	CmdLCD(0x30);
	CmdLCD(0x30);
	CmdLCD(0x30);
	CmdLCD(MODE_8BIT_2LINE);
  CmdLCD(DSP_ON_CUR_OFF);
  CmdLCD(CLEAR_LCD);
  CmdLCD(SHIFT_CUR_RIGHT);	
}

void StrLCD(s8 *s)
{
	while(*s)
		CharLCD(*s++);
}

void U32LCD(u32 n)
{
	s32 i=0;
	u8 digit[10];
	if(n==0)
	{
		CharLCD('0');
	}
  else
	{
		while(n>0)
		{
			digit[i]=(n%10)+48;
			n/=10;
			i++;
		}
		for(--i;i>=0;i--)
		   CharLCD(digit[i]);
	}		
}

void S32LCD(s32 n)
{
	if(n<0)
	{
		CharLCD('-');
		n=-n;
	}
  U32LCD(n);	
}

void F32LCD(f32 fNum,u8 nDP)
{
	s32 i;
	u32 n;
	if(fNum<0)
	{
		CharLCD('-');
		fNum=-fNum;
	}
	n=fNum;
	U32LCD(n);
	CharLCD('.');
	for(i=0;i<nDP;i++)
	{
		fNum=(fNum-n)*10;
		n=fNum;
		CharLCD(n+48);
	}
	
}

void BuildCGRAM(s8 *,u8);
