//-----------------------------------------------------
//File: timer.c
//Auth: ELECTRONIC ASSEMBLY JM
//DATE: 08-07-2012
//-----------------------------------------------------

//---Includes---
#include "sfr_r825.h"

#include "timer.h"

unsigned int time_cnt=0;
//--- module global varibles ---
unsigned int ms_cnt=0;
//-----------------------------------------------------
//Func: initTimerRA()
//Desc: Init Timer RA with CLOCKPULS
//-----------------------------------------------------
void initTimerRA (void)
{
	traic = 0x00; 			//interrupt off
	tstart_tracr = 0; 		//stop cpunting
	
	while(tcstf_tracr == 1);	// Warten auf Stop des Timers

	
    trapre = 100 - 1; //Prescaler Register
    tra = (unsigned char)(((f1_CLK_SPEED/1)*CLOCKPULS)/100 - 1); //Timer register

    tramr = 0x00;	//b0:b2    TMOD0,TMOD1,TMOD2  Timer RA operating mode select bits
				    //b3                          Set to 0
				    //b4:b6    TCK0,TCK1,TCK2     Timer RA count source select bits
				    //b7       TCKCUT             Timer RA count source cutoff bit

    traioc = 0x00;	//b0       TEDGSEL      TRAIO polarity sw itch bit
			        //b1       TOPCR        TRAIO output control bit
			        //b2       TOENA        TRAO output enable bit
			        //b3       TIOSEL       ~INT1/TRAIO select bit
			        //b4       TIPF0        TRAIO input filter select bits
			        //b5       TIPF1        TRAIO input filter select bits
			        //b7:b6                 Set to 0

   /* The recommended procedure for writing an Interrupt Priority Level is shown
      below (see R8C datasheets under 'Interrupts' for details). */

    /* disable irqs before setting irq registers - macro defined in rskR8C25def.h */
    asm("FCLR I");	//Interrupt disable

    /* TRA  interrupt priority level */
    traic = 0x03;

    /* start timer */
    tstart_tracr = 1;
}

//-----------------------------------------------------
//Func: Delay(ms)
//Desc: wait function
//-----------------------------------------------------
void Delay (unsigned int ms)
{
		ms_cnt=ms;
	while (ms_cnt); 
}

//-----------------------------------------------------
//Func: tra_irq()
//Desc: 1ms timer interrupt
//-----------------------------------------------------
void tra_irq (void)
{
	if (ms_cnt)
		ms_cnt--;

}