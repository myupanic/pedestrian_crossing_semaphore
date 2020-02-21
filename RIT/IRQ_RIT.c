/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_RIT.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    RIT.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include "lpc17xx.h"
#include "RIT.h"
#include "../led/led.h"
#include "../timer/timer.h"

/******************************************************************************
** Function name:		RIT_IRQHandler
**
** Descriptions:		REPETITIVE INTERRUPT TIMER handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/

volatile int down=0;
volatile int down1 = 0;
volatile int down2 = 0;
extern int startTimer;
int e1 = 0;
int e2 = 0;

void RIT_IRQHandler (void)
{					
	
	/* button management */
	if(down!=0){ 
		if((LPC_GPIO2->FIOPIN & (1<<10)) == 0){	/* INT0 pressed */
			down++;				
			reset_timer(0);
			enable_timer(0);
			startTimer = 1;
		}
		else {	/* button released */
			down=0;			
			NVIC_EnableIRQ(EINT0_IRQn);							 /* enable Button interrupts			*/
			LPC_PINCON->PINSEL4    |= (1 << 20);     /* External interrupt 0 pin selection */
		}
	}
	if(down1!=0){
		if((LPC_GPIO2->FIOPIN & (1<<11)) == 0){
			down1++;
			if(startTimer == 1){
				e1++;
			}
		}
		else{
			down1 = 0;
			NVIC_EnableIRQ(EINT1_IRQn);
			LPC_PINCON->PINSEL4 |= (1<<22);
		}
	}
	
	if(down2!=0){
		if((LPC_GPIO2->FIOPIN & (1<<12)) == 0){
			down2++;
			if(startTimer == 1){
				e2++;
			}
		}
		else{
			down2 = 0;
			NVIC_EnableIRQ(EINT2_IRQn);
			LPC_PINCON->PINSEL4 |= (1<<24);
		}
	}
	
  LPC_RIT->RICTRL |= 0x1;	/* clear interrupt flag */
	
  return;
}

int getValue(){
	return e1;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
