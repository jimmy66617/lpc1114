#include "LPC11xx.h"                        
#include "clk_init.h"

#define TEST_TIMER_NUM 0

volatile uint32_t timer0_16bit_counter = 0;
volatile uint32_t timer0_16bit_capture = 0;

void TIMER16_0_IRQHandler ( void )
{  
			if ( LPC_TMR16B0->IR & 0x1 ) {
					LPC_TMR16B0->IR = 1;			/* clear interrupt flag */
					timer0_16bit_counter++;
			}
			if ( LPC_TMR16B0->IR & (0x1<<4) ) {
					LPC_TMR16B0->IR = 0x1<<4;		/* clear interrupt flag */
					timer0_16bit_capture++;
			}
			return;
}

void init_timer_16bit ( uint8_t timer_num, uint32_t TimerInterval ) 
{
		if ( timer_num == 0 ) {
		/* Some of the I/O pins need to be clearfully planned if
		you use below module because JTAG and TIMER CAP/MAT pins are muxed. */
				LPC_SYSCON->SYSAHBCLKCTRL |= (1<<7);
				LPC_IOCON->PIO0_2&= ~0x07;	/*  Timer0_16 I/O config */
				LPC_IOCON->PIO0_2|= 0x02;		/* Timer0_16 CAP0 */
				LPC_IOCON->PIO0_8&= ~0x07;	
				LPC_IOCON->PIO0_8|= 0x02;		/* Timer0_16 MAT0 */
				LPC_IOCON->PIO0_9&= ~0x07;
				LPC_IOCON->PIO0_9|= 0x02;		/* Timer0_16 MAT1 */

				#ifdef __JTAG_DISABLED
						LPC_IOCON->JTAG_TCK_PIO0_10 &= ~0x07;
						LPC_IOCON->JTAG_TCK_PIO0_10 |= 0x03;		/* Timer0_16 MAT2 */
				#endif	
						timer0_16bit_counter = 0;
						timer0_16bit_capture = 0;
						LPC_TMR16B0->MR0 = TimerInterval;
				#if TIMER_MATCH
						LPC_TMR16B0->EMR &= ~(0xFF<<4);
						LPC_TMR16B0->EMR |= ((0x3<<4)|(0x3<<6)|(0x3<<8));
				#else
						/* Capture 0 on rising edge, interrupt enable. */
						LPC_TMR16B0->CCR = (0x1<<0)|(0x1<<2);
				#endif
						LPC_TMR16B0->MCR = 3;				/* Interrupt and Reset on MR0 and MR1 */	
						/* Enable the TIMER0 Interrupt */
						NVIC_EnableIRQ(TIMER_16_0_IRQn);		
				}
		return;
}

void enable_timer_16bit ( uint8_t timer_num )
{
		if ( timer_num == 0 )		{
				LPC_TMR16B0->TCR = 1;
		}
		else
		{
				LPC_TMR16B1->TCR = 1;
		}
		return;
}
