#include "LPC11xx.h"
#include "timer16.h"
#include "clkconfig.h"
#include "setport.h"
#include "deley.h"
#define TEST_TIMER_NUM  0  /* 0 or 1 for 16-bit timers only */
extern volatile uint32_t timer16_0_counter;
extern volatile uint32_t timer16_1_counter;
int main(void){
  Set_Dir(2,7,1);
	Set_Dir(2,6,0);
	LPC_GPIO2->IS |= (1<<6);
	LPC_GPIO2->IE |= (1<<6);
	NVIC_EnableIRQ(EINT2_IRQn);
	while(1);
}	
void PIOINT2_IRQHandler()
{  int i=0,mode;
	
     while((LPC_GPIO2->DATA&(1<<6))==0) {
			 i++;
		 if(i<=500000){
       		  mode=0;
		 }else if(i>500000){
       	while((LPC_GPIO2->DATA&(1<<6))==0) {
				  deley(500000);
					LPC_GPIO2->DATA|=(1<<7);
					deley(500000);
					LPC_GPIO2->DATA&=~(1<<7);
					if((LPC_GPIO2->DATA&(1<<6))!=0){
          LPC_GPIO2->DATA&=~(1<<7);
						break;
					}                             
	       }
				}							 
	 }
    if(mode==0){
     LPC_GPIO2->DATA^=(1<<7);
    }     		 
	 LPC_GPIO2->IC = 0XFFF;
}