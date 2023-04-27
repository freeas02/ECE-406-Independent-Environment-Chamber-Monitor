//-----------------------------------------------------
//File: lcd_spi.c
//Auth: ELECTRONIC ASSEMBLY JM
//DATE: 08-25-2013
//-----------------------------------------------------

//---Includes---
#include "sfr_r825.h"
#include "define.h"
#include "lcd_spi.h"

#include "timer.h"

//--- module global varibles ---
unsigned char dh_function_set = 0x38;  //double hight font off default

//--- waitstates for testing ---
//use these macros to slow the communication down
#define WAITST 2

#define Wait(x)
//#define Wait(x) asm("nop")
/*
void Wait (unsigned char waitstates)
{
	unsigned char i=0;
	for (i=0; i<waitstates; i++)
	{
		asm("nop");
	}
}
*/


//-----------------------------------------------------
//Func: initDispl()
//Desc: inits Display
//-----------------------------------------------------
void initDispl(void)
{
	unsigned char i;

	//Port init (dd -> datadirection register; 1 output, 0 input)
	ddCS = 1;
	CS = 1;	
	ddSID = 1;
	SID = 1;
	ddSOD = 0;
	ddSCLK = 1;
	SCLK = 1;
	ddRPOWER = 1;
	POWER = 1;

	//SPI mode: Pol 0 (falling edge), UFORM = 0 (LSB first)
	u0mr = 0x01; //synchronous serial mode, internal clock, 1 stop bit, no parity
	u0c0 = 0x00; //f1, CMOS output, falling edge, LSB first
	u0c1 = 0x67; //enable trans, enable rec, enable cont rec
//	u0brg = 0x81; //baud: 1200 u0brg = (f/(BitRate x 16)-1; f= 20MHz/8 -->u0c0 f8
	u0brg = 0x0A; //baud: 115200 u0brg = (f/(BitRate x 16)-1; f= 20MHz/1 -->u0c0 f1


	//Perform a display reset
	POWER = 1;
	Delay(5);
	POWER=0;
	Delay(100);

	//init Display
	//init Display
	WriteIns(0x3A);	//8-Bit data length extension Bit RE=1; REV=0
	WriteIns(0x09);	//4 line display
	WriteIns(0x06);	//Bottom view
	WriteIns(0x1E);	//Bias setting BS1=1
	WriteIns(0x39);	//8-Bit data length extension Bit RE=0; IS=1
	WriteIns(0x1B);	//BS0=1 -> Bias=1/6
	WriteIns(0x6E); //Devider on and set value
	WriteIns(0x56); //Booster on and set contrast (BB1=C5, DB0=C4)
	WriteIns(0x7A); //Set contrast (DB3-DB0=C3-C0)
	WriteIns(dh_function_set); //8-Bit data length extension Bit RE=0; IS=0

	ClrDisplay();
	DisplayOnOff(DISPLAY_ON | CURSOR_ON | BLINK_ON);
}

//-----------------------------------------------------
//Func: WriteChar(character)
//Desc: sends a single character to display
//-----------------------------------------------------
void WriteChar (char character)
{
	WriteData(character);
}

//-----------------------------------------------------
//Func: WriteString(string)
//Desc: sends a string to display, must be 0 terminated
//-----------------------------------------------------
void WriteString(_far char * string)
{
	do
	{
		WriteData(*string++);
	}
	while(*string);
}

//-----------------------------------------------------
//Func: WriteString(string)
//Desc: sends a string to display, must be 0 terminated
//-----------------------------------------------------
void DisplLines(unsigned char lines)
{
	if(lines == DOUBLEHEIGHT_OFF)
	{
		WriteIns(lines);
		dh_function_set = 0x38;
	}
	else
	{
		WriteIns(0x3C);
		WriteIns(0x3A);
		WriteIns(lines);
		WriteIns(0x3C);
		dh_function_set = 0x3C;
	}
	
}

//-----------------------------------------------------
//Func: SetPostion(postion)
//Desc: set postion
//-----------------------------------------------------
void SetPostion(char pos)
{
	WriteIns(LCD_HOME_L1+pos);
}

//-----------------------------------------------------
//Func: DisplayOnOff(control)
//Desc: use definitions of header file to set display
//-----------------------------------------------------
void DisplayOnOff(char data)
{
	WriteIns(0x08+data);
}

//-----------------------------------------------------
//Func: DefineCharacter(memory postion, character data)
//Desc: stores an own defined character
//-----------------------------------------------------
void DefineCharacter(unsigned char postion, unsigned char *data)
{
	unsigned char i=0;
	WriteIns(0x40+8*postion);

	for (i=0; i<8; i++)
	{
		WriteData(data[i]);
	}
	SetPostion(LINE1);
}
//-----------------------------------------------------
//Func: ClrDisplay
//Desc: Clears entire Display content and set home pos
//-----------------------------------------------------
void ClrDisplay(void)
{
	WriteIns(0x01);
	SetPostion(LINE1);
}

//-----------------------------------------------------
//Func: SetContrast
//Desc: Sets contrast 0..63
//-----------------------------------------------------
void SetContrast(unsigned char contr)
{
	WriteIns(0x39);
	WriteIns(0x54 | (contr >> 4));
	WriteIns(0x70 | (contr & 0x0F));
	WriteIns(dh_function_set);

}

//-----------------------------------------------------
//Func: SetView
//Desc: view bottom view(0x06), top view (0x05)
//-----------------------------------------------------
void SetView(unsigned char view)
{
	WriteIns(0x3A);
	WriteIns(view);
	WriteIns(dh_function_set);
}

//-----------------------------------------------------
//Func: SetROM
//Desc: Changes the Rom code (ROMA=0x00, ROMB=0x04, ROMC=0x0C)
//---------------------------------------------------
void SetROM (unsigned char rom)
{
	WriteIns(0x2A);
	WriteIns(0x72);
	WriteData(rom);
	WriteIns(0x28);
}


//-----------------------------------------------------
//Func: WriteIns(instruction)
//Desc: sends instruction to display
//-----------------------------------------------------
static void WriteIns(char ins)
{
	CS = 0;
	CheckBusy();
	SPI_put(0x1F);  			//Send 5 synchronisation bits, RS = 0, R/W = 0
	SPI_put(ins & 0x0F); 		//send lower data bits
	SPI_put((ins>>4) & 0x0F); 	//send higher data bits
	CS = 1;
}

//-----------------------------------------------------
//Func: WriteData(data)
//Desc: sends data to display
//-----------------------------------------------------
static void WriteData(char data)
{
	CS = 0;
	CheckBusy();
	SPI_put(0x5F);				//Send 5 synchronisation bits, RS = 1, R/W = 0
	SPI_put(data & 0x0F);		//send lower data bits
	SPI_put((data>>4) & 0x0F);	//send higher data bits
	CS = 1;
}

//-----------------------------------------------------
//Func: CheckBusy()
//Desc: checks if display is idle
//-----------------------------------------------------
unsigned char CheckBusy(void)
{
	unsigned char readData = 1;

/*	do
	{
		SPI_put(0x3F); //Send 5 synchronisation bits, RS = 0, R/W = 1
		SPI_put(0x00); //dummy write to receive data
		while(ri_u0c1 == 0); 	//wait while data is received
		readData= ~u0rbl;  		//store data
	}while(readData&0x80); //check for busyflag
*/
	return readData;
}

//-----------------------------------------------------
//Func: SPI_put()
//Desc: waits till data is sent over the spi interface
//-----------------------------------------------------
static void SPI_put (unsigned char byte)
{
	u0tb = ~byte;
	while(ti_u0c1 == 0);
	while(txept_u0c0 == 0);
}





