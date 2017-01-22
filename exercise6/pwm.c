#include "LPC11xx.h" 
#include "pwm.h"
 
void T16B0M0_PWM_Init (float duty, int cycle)
{
		if( (duty>100) && (duty<0) ){// if not in duty cycle
				return;
		}
		LPC_SYSCON->SYSAHBCLKCTRL |= (1<<7);//set TIM16B0 clk    
		LPC_SYSCON->SYSAHBCLKCTRL |= (1<<16);//set IOCON clk	 
		LPC_IOCON->PIO0_8 &= ~0x07;//set port0_8 to MAT0
		LPC_IOCON->PIO0_8 |= 0x02;        
		LPC_SYSCON->SYSAHBCLKCTRL &= ~(1<<16);//clear IOCON clk 
		LPC_TMR16B0->TCR = 0x02;//reset the timer           
		LPC_TMR16B0->PR  = SystemFrequency/1000000-1;//1u sec timer counter+1            
		LPC_TMR16B0->PWMC = (1<<0);//set port0_8 to PWM output               
		LPC_TMR16B0->MCR = 1<<10;//when MR3 match Timer Counter ,reset Timer Counter 
		LPC_TMR16B0->MR3 = cycle;//set the cycle           
		LPC_TMR16B0->MR0 = cycle/100*(100-duty);//set the duty cycle    
		LPC_TMR16B0->TCR = 0x01;//start the timer                 
}
void T16B0M0_PWM_SET(float duty,int cycle)
{
		if( (duty>100) && (duty<0) ){//if not in duty cycle
				return;
		}
		LPC_TMR16B0->MR0 = cycle/100*(100-duty); //set the duty cycle        
}
void T32B0M0_PWM_Init (float duty,int cycle){
		if( (duty>100) && (duty<0) ){// if not in duty cycle
				return;
		}
		LPC_SYSCON->SYSAHBCLKCTRL |= (1<<9);
		LPC_SYSCON->SYSAHBCLKCTRL |= (1<<16);
		LPC_IOCON->PIO1_6 &= ~0x07;
		LPC_IOCON->PIO1_6 |= 0x02;
		LPC_SYSCON->SYSAHBCLKCTRL &= ~(1<<16);
		LPC_TMR32B0->TCR = 0x02;//reset the timer           
		LPC_TMR32B0->PR  = SystemFrequency/1000000-1;//1u sec timer counter+1            
		LPC_TMR32B0->PWMC= (1<<0);//set port1_6 to PWM output               
		LPC_TMR32B0->MCR = 1<<10;//when MR3 match Timer Counter ,reset Timer Counter 
		LPC_TMR32B0->MR3 = cycle;//set the cycle           
		LPC_TMR32B0->MR0 = cycle/100*(100-duty);//set the duty cycle    
		LPC_TMR32B0->TCR = 0x01;//start the timer 
}	
void T32B0M0_PWM_SET(float duty,int cycle)
{
		if( (duty>100) && (duty<0) ) {//if not in duty cycle
				return;
		}
		LPC_TMR32B0->MR0 = cycle/100*(100-duty); //set the duty cycle        
}