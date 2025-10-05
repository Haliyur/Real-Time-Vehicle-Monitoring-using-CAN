 //i2c_main.c

#include <LPC21xx.h>
#include "types.h"
#include "i2c.h"
#include "delay.h"
#include "uart.h"
#include "uart0.h"
#include "lcd.h"
#include "lcd_defines.h"

#define MMA7660_ADDR 0x4C
#define rLED (1<<16) // P1.16
#define gLED (1<<17) // P1.17

// Convert raw 6-bit unsigned to signed value
char to_signed_6bit(u8 val) {
    if (val > 31)
        return val - 64;
    return val;
}

// I2C read and write functions for general device
void i2c_device_write(u8 sa, u8 reg, u8 data) {
    i2c_start();
    i2c_write(sa << 1);     // Write mode
    i2c_write(reg);         // Register address
    i2c_write(data);        // Data
    i2c_stop();
    delay_ms(10);
}

u8 i2c_device_read(u8 sa, u8 reg) {
    u8 data;
    i2c_start();
    i2c_write(sa << 1);     // Write mode
    i2c_write(reg);         // Register address
    i2c_restart();
    i2c_write((sa << 1) | 1); // Read mode
    data = i2c_nack();
    i2c_stop();
    return data;
}

int main() {
    signed char x, y, z;

    init_i2c();
        uart0_init();
    IODIR1 = rLED | gLED;

  //  delay_ms(100);

    // Set MMA7660 to Active Mode
    i2c_device_write(MMA7660_ADDR, 0x07, 0x01);
   // delay_ms(100);  // Allow time to stabilize
  while(1)
    {
    // Read and convert X, Y, Z axis
    x = to_signed_6bit(i2c_device_read(MMA7660_ADDR, 0x00));
    y = to_signed_6bit(i2c_device_read(MMA7660_ADDR, 0x01));
    z = to_signed_6bit(i2c_device_read(MMA7660_ADDR, 0x02));

    // Handle based on movement
    if (x > 20 || y > 20 || z > 20) {
        IOSET1 = gLED;   // Bright if positive tilt
        IOCLR1 = rLED;
    } else if (x < -20 || y < -20 || z < -20) {
        IOSET1 = rLED;   // Red if negative tilt
        IOCLR1 = gLED;
    }
    else if(x<-10 || y<-10 || z<-10){
           strLCD("ALERT");
    }
    else {
        IOCLR1 = gLED | rLED; // No strong tilt
    }



                strLCD("X = ");
    uart0_print_num(x);
    uart0_print("\r\n");
                delay_ms(1000);
                uart0_print("\r\n");

                strLCD("Y = ");
    uart0_print_num(y);
    uart0_print("\r\n");
                delay_ms(1000);
                uart0_print("\r\n");

                strLCD("Z = ");
    uart0_print_num(z);
    uart0_print("\r\n");
                delay_ms(1000);
                uart0_print("\r\n");
                uart0_print("\r\n");

                uart0_print("------------------\r\n");
  }
        /*
        uart0_print("X = ");
    uart0_tx(x + '0');
    uart0_print("\r\n");

    uart0_print("Y = ");
    uart0_tx(y + '0');
    uart0_print("\r\n");

    uart0_print("Z = ");
    uart0_tx(z + '0');
    uart0_print("\r\n");
        */
   // while (1);
}

/*
#include <LPC21xx.h>
#include "types.h"
#include "i2c.h"
#include "i2c_eeprom.h"
#include "delay.h"

#define MMA7660_ADDR 0x4C
#define rLED 1<<16 //P1.16
#define gLED 1<<17 //P1.17
#define I2C_EEPROM_SA 0x50
int main()
{
    u8 x, y, z;

    init_i2c();
    //IODIR1 = rLED | gLED;
        IODIR1=gLED|rLED;
        delay_ms(2000);

    // Set MMA7660 to Active mode
    i2c_device_write(MMA7660_ADDR, 0x07, 0x01);
    delay_ms(100);

    // Read X, Y, Z
    x = i2c_device_read(MMA7660_ADDR, 0x00);
    y = i2c_device_read(MMA7660_ADDR, 0x01);
    z = i2c_device_read(MMA7660_ADDR, 0x02);

    if (x > 32)
        IOPIN1 ^= gLED;
    else
        IOPIN1 ^= rLED;

    while (1);
}
*/

/*
#include <LPC21xx.h>
#include "types.h"
#include "i2c.h"
#include "i2c_eeprom.h"
#include "delay.h"


#define I2C_EEPROM_SA 0x50 //7Bit Slave Addr
#define rLED 1<<16 //P1.16
#define gLED 1<<17 //P1.17

int main()
{
        u8 t='a';
        init_i2c();
        IODIR1=gLED|rLED;

        delay_ms(2000);
        i2c_eeprom_write(I2C_EEPROM_SA,0x0000,'a');
        t=i2c_eeprom_read(I2C_EEPROM_SA,0x0000);
        delay_ms(2000);
        if(t=='a')
        {
                IOPIN1^=gLED;
        }
        else
        {
                IOPIN1^=rLED;
        }
        while(1);
}
 */


 //i2c_main.c
/*
#include <LPC21xx.h>
#include "types.h"
#include "i2c.h"
#include "delay.h"

#define MMA7660_ADDR 0x4C
#define rLED (1<<16) // P1.16
#define gLED (1<<17) // P1.17

// Convert raw 6-bit unsigned to signed value
char to_signed_6bit(u8 val) {
    if (val > 31)
        return val - 64;
    return val;
}


// I2C read and write functions for general device
void i2c_device_write(u8 sa, u8 reg, u8 data) {
    i2c_start();
    i2c_write(sa << 1);     // Write mode
    i2c_write(reg);         // Register address
    i2c_write(data);        // Data
    i2c_stop();
    delay_ms(10);
}

u8 i2c_device_read(u8 sa, u8 reg) {
    u8 data;
    i2c_start();
    i2c_write(sa << 1);     // Write mode
    i2c_write(reg);         // Register address
    i2c_restart();
    i2c_write((sa << 1) | 1); // Read mode
    data = i2c_nack();
    i2c_stop();
    return data;
}


void uart0_init() {
    PINSEL0 |= 0x05;  // P0.0 & P0.1 as TXD & RXD
    U0LCR = 0x83;     // 8-bit, enable DLAB
    U0DLM = 0;
    U0DLL = 97;       // 9600 baud @ 15MHz PCLK
    U0LCR = 0x03;     // Disable DLAB
}

void uart0_tx(char ch) {
    while (!(U0LSR & 0x20));
    U0THR = ch;
}

void uart0_print(char *str) {
    while (*str) uart0_tx(*str++);
}

int main()
{

   signed char x, y, z;

    init_i2c();
    IODIR1 = rLED | gLED;

    delay_ms(100);

    // Set MMA7660 to Active Mode
    i2c_device_write(MMA7660_ADDR, 0x07, 0x01);
    delay_ms(100);  // Allow time to stabilize


char buffer[40];
uart0_init();

// Read and convert axes
x = to_signed_6bit(i2c_device_read(MMA7660_ADDR, 0x00));
y = to_signed_6bit(i2c_device_read(MMA7660_ADDR, 0x01));
z = to_signed_6bit(i2c_device_read(MMA7660_ADDR, 0x02));


    // Handle based on movement
    if (x > 20 || y > 20 || z > 20) {
        IOSET1 = gLED;   // Bright if positive tilt
        IOCLR1 = rLED;
    } else if (x < -20 || y < -20 || z < -20) {
        IOSET1 = rLED;   // Red if negative tilt
        IOCLR1 = gLED;
    } else {
        IOCLR1 = gLED | rLED; // No strong tilt
    }

    while (1);

sprintf(buffer, "X=%d Y=%d Z=%d\r\n", x, y, z);
uart0_print(buffer);
}
*/