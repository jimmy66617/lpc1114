#include "LPC11xx.h"
#include "button.h"
int main(void){
	LPC_GPIO2->IS |= (1<<6);
	LPC_GPIO2->IE |= (1<<6);
	NVIC_EnableIRQ(EINT2_IRQn);
	NVIC_SetPriority(EINT2_IRQn, 3);
	while(1);
}	
void PIOINT2_IRQHandler()	
{ if((LPC_GPIO2->MIS&(1<<6))==(1<<6)) 
   { 
		 button(2,7,500,250,250);
	   LPC_GPIO2->IC=0xFFF;
	 }
 }