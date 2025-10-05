#include <LPC21xx.h>
#include "types.h"
void CfgPortPinFunc(u32 portNo,
	                  u32 pinNo,
                    u32 pinFunc)
{
	if(portNo==0)
	{
		if(pinNo<16)
		{
	    PINSEL0=((PINSEL0&~(3<<(pinNo*2)))|
			         (pinFunc<<(pinNo*2)));
		}	
	  else if((pinNo>=16)&&(pinNo<32))
		{
   	PINSEL1=((PINSEL1&~(3<<((pinNo%16)*2)))|
	           (pinFunc<<((pinNo%16)*2)));
	  }
	}
}
