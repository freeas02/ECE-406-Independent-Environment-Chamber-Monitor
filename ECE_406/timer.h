//-----------------------------------------------------
//File: timer.h
//Auth: ELECTRONIC ASSEMBLY JM
//DATE: 08-07-2012
//-----------------------------------------------------
#ifndef TIMER_H
#define TIMER_H

#define f1_CLK_SPEED 20000000
#define CLOCKPULS (1e-3)


void initTimerRA (void);

void Delay (unsigned int ms);

#pragma INTERRUPT tra_irq
void tra_irq (void);

#endif