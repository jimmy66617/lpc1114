#include "LPC11xx.h"                        
#include "timer16.h"
#include "clkconfig.h"
#define TEST_TIMER_NUM 0
void clk_init(){
	uint32_t interval;
	SystemInit();
	 /* Config CLKOUT, mostly used for debugging. */
  CLKOUT_Setup( CLKOUTCLK_SRC_MAIN_CLK );
  LPC_IOCON->PIO0_1 &= ~0x07; 
  LPC_IOCON->PIO0_1 |= 0x01;  /* CLK OUT */

  /* Enable AHB clock to the GPIO domain. */
  LPC_SYSCON->SYSAHBCLKCTRL |= (1<<6);

  /* TEST_TIMER_NUM is either 0 or 1 for 16-bit timer 0 or 1. */
  interval = SystemAHBFrequency/1000 - 1;
  if ( interval > 0xFFFF )
  {
 interval = 0xFFFF;
  }
  init_timer16(TEST_TIMER_NUM, interval);
  enable_timer16(TEST_TIMER_NUM);
}	