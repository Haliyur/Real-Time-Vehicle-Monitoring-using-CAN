//lcd_test.c
#include "lcd.h"
#include "lcd_defines.h"
#include "delay.h"
main()
{
	InitLCD();
	CharLCD('A');
	CmdLCD(GOTO_LINE2_POS0);
	StrLCD("V24HE7-ARM");
	delay_ms(1000);
	CmdLCD(CLEAR_LCD);
	U32LCD(1234567890);
	CmdLCD(GOTO_LINE2_POS0);
	S32LCD(-1234567890);
	delay_ms(1000);
	CmdLCD(CLEAR_LCD);
	F32LCD(123.456789,6);
	while(1);
}
