//-----------------------------------------------------
//File: main.c
//Auth: ELECTRONIC ASSEMBLY JM
//DATE: 08-28-2013
//-----------------------------------------------------

/*used microcontroller:
Renesas R8C25 with 20MHz external clock to DOGM204-A (SSD1803A)
uC-Pin		Disp-Pin	Function
10 (VSS)	 14		  	GND
12 (VCC)	 13		  	VDD (3.3V)
24 (p1_4)	 15		 	MOSI
23 (p1_5)	 16	 	 	MISO
23 (p1_6)	 17	 	 	SCLK
 3 (p3_3)	 18  		CS
37 (p6_3)	 20		  	RES
*/

//---Includes---
#include "sfr_r825.h"
#include "define.h"

#include "main.h"
#include "timer.h"
#include "lcd_spi.h"

//definitions
#define TIME 1000
#define CONTRSTART 35
#define CONTRSPAN  15

//--- module global varibles ---

//-----------------------------------------------------
//Func: main()
//Desc: main function with main loop, show a sample screen
//-----------------------------------------------------
void main(void)
{
//Define own chars (arrow up and down)
	unsigned char arrowd[] = {0x04, 0x04, 0x04, 0x04, 0x15, 0x0E, 0x04, 0x00};
	unsigned char arrowu[8]=0;
	unsigned char i=0, j=0;
	unsigned char charset1[] = {0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1A,0x1B,0x1C,0x1D,0x1E,0x1F , 0};
	unsigned char charset2[] = {0xF0,0xF1,0xF2,0xF3,0xF4,0xF5,0xF6,0xF7,0xF8,0xF9,0xFA,0xFB,0xFC,0xFD,0xFE,0xFF , 0};

	for (i=0; i<7; i++)
		arrowu[i]=arrowd[6-i];
	pd2_7 = 1;

	pd2_2 = 1;  //Portpin for light backlight up
	p2_2 = 1;

	externClock();

	initTimerRA();

	asm("FSET I");	//Interrupt enable

	initDispl(); 	//init display

//define own characters
	DefineCharacter(0,arrowd);
	DefineCharacter(2,arrowu);

	DisplayOnOff(DISPLAY_ON); //Disable cursor
	i=CONTRSTART;
	while(1)
	{
		p2_7 = !p2_7; 	//Blink an LED
		
		switch(j++)
		{
			case 0:
				DisplLines(DOUBLEHEIGHT_OFF);
				ClrDisplay();
				SetPostion(LINE1);
				WriteString("DOGS104-A ");
				SetPostion(LINE2);
				WriteString(" SPI I2C  ");
				SetPostion(LINE3);
				WriteString("3.3 V     ");
				SetPostion(LINE4);
				WriteString("LED light ");
				break;
			case 1:
				ClrDisplay();
				SetROM(ROMA);
				SetPostion(LINE1);
				WriteString("3char sets");
				SetPostion(LINE2);
				WriteString("ROMA-Euro1");
				SetPostion(LINE3);
				WriteString(charset1);
				SetPostion(LINE4);
				WriteString(charset2);
				break;
			case 2:
				ClrDisplay();
				SetROM(ROMB);
				SetPostion(LINE1);
				WriteString("3char sets");
				SetPostion(LINE2);
				WriteString("ROMB-Euro2");
				SetPostion(LINE3);
				WriteString(charset1);
				SetPostion(LINE4);
				WriteString(charset2);
				break;
			case 3:
				ClrDisplay();
				SetROM(ROMC);
				SetPostion(LINE1);
				WriteString("3char sets");
				SetPostion(LINE2);
				WriteString("ROMB-Japan");
				SetPostion(LINE3);
				WriteString(charset1);
				SetPostion(LINE4);
				WriteString(charset2);
				break;
			case 4:
				ClrDisplay();
				DisplLines(DOUBLEHEIGHT_TOP);
				SetPostion(LINE1);
				WriteString("5.2mm char");
				SetPostion(LINE2);
				WriteString("2.6mm char");
				SetPostion(LINE3);
				WriteString("----------");
				break;
			case 5:
				ClrDisplay();
				DisplLines(DOUBLEHEIGHT_MID);
				SetPostion(LINE1);
				WriteString("2.6mm char");
				SetPostion(LINE2);
				WriteString("5.2mm char");
				SetPostion(LINE3);
				WriteString("----------");
				break;
			case 6:
				ClrDisplay();
				DisplLines(DOUBLEHEIGHT_BOT);
				SetPostion(LINE1);
				WriteString("2.6mm char");
				SetPostion(LINE2);
				WriteString("----------");
				SetPostion(LINE3);
				WriteString("5.2mm char");
				break;
			case 7:
				ClrDisplay();
				DisplLines(DOUBLEHEIGHT_DOUBLE);
				SetPostion(LINE1);
				WriteString("5.2mm char");
				SetPostion(LINE2);
				WriteString("Big Letter");
				j=0;
				break;
			default:
				j=0;
				break;
		}

		if(i > (CONTRSTART + CONTRSPAN))
			i=CONTRSTART;
		
		SetContrast(i++);  //show different contrast levels, using i as increment
		
		

		Delay(TIME);
	}

}

//-----------------------------------------------------
//Func: externClock()
//Desc: switch to external clock no devision (20MHz)
//-----------------------------------------------------
void externClock (void)
{
	asm("FCLR I");	//Interrupt disable

	prcr = 1;		//Protect off

	cm13 = 1;		//Xin Xout
	cm15 = 1;		//XCIN-XCOUT drive capacity select bit : HIGH
	cm05 = 0;		//Xin on
	cm16 = 0;		//Main clock = No division mode 20MHz
	cm17 = 0;		//Main clock = No division mode
	cm06 = 0;		//CM16 and CM17 enable

	//Waitting for stable of oscillation
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");

	ocd2 = 0;		//Main clock change

	prcr = 0;		//Protect on
}