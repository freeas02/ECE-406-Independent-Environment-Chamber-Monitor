//-----------------------------------------------------
//File: lcd_spi.h
//Auth: ELECTRONIC ASSEMBLY JM
//DATE: 08-07-2012
//-----------------------------------------------------
#ifndef LCDSPI_H
#define LCDSPI_H


//--- Port definitions ---
#define CS 		p3_3
#define ddCS	pd3_3
#define SID		p1_4
#define ddSID	pd1_4
#define SOD		p1_5
#define ddSOD	pd1_5
#define SCLK	p1_6
#define ddSCLK	pd1_6
#define POWER	p6_3
#define ddRPOWER	pd6_3

//--- Standard definitions for LCD ---
#define LCD_HOME_L1	0x80
#define LINE1	0
/*
//HD44780
#define LINE2	LINE1+0x40
#define LINE3	LINE1+0x14
#define	LINE4 	LINE2+0x14
*/
//KS0073/SSD1803(A)
#define LINE2	LINE1+0x20
#define LINE3	LINE1+0x40
#define	LINE4 	LINE1+0x60

#define DISPLAY_ON 	0x04
#define DISPLAY_OFF 0x03
#define CURSOR_ON	0x02
#define CURSOR_OFF	0x05
#define BLINK_ON	0x01
#define BLINK_OFF	0x06


#define TOPVIEW		0x05
#define BOTTOMVIEW	0x06
#define ROMA		0x00
#define ROMB		0x04
#define ROMC		0x0C

#define DOUBLEHEIGHT_TOP 	0x1E
#define DOUBLEHEIGHT_MID 	0x16
#define DOUBLEHEIGHT_BOT 	0x12
#define DOUBLEHEIGHT_DOUBLE	0x1A
#define DOUBLEHEIGHT_OFF	0x38

	

void initDispl(void);


void WriteChar		(char character);
void WriteString	(_far char * string);
void SetPostion		(char pos);
void DisplLines		(unsigned char lines);
void DisplayOnOff	(char data);
void DefineCharacter(unsigned char postion, unsigned char *data);
void ClrDisplay		(void);
void SetContrast	(unsigned char contr);
void SetView		(unsigned char view);
void SetROM			(unsigned char rom);
#define GETCURSORADDR()	CheckBusy()


//Normally you don't need these functions outside this module
static void WriteIns		(char ins);
static void WriteData		(char data);

unsigned char CheckBusy		(void);
static void   SPI_put 		(unsigned char byte);

#endif