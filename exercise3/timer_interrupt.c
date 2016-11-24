#include "LPC11xx.h"                        
#include "clk_init.h"
#include "setport.h"
#define TEST_TIMER_NUM  0  /* 0 or 1 for 16-bit timers only */
extern volatile uint32_t timer16_0_counter;
void blink(int port_number,int bit_position,int flash_time,int off_time){
  clk_init(); 
	Set_Dir( port_number, bit_position, 1 );//set port ?_? outport 
  while (1)                                
  {
#if TEST_TIMER_NUM
#else
 /* I/O configuration and LED setting pending. */
 if ( (timer16_0_counter > 0) && (timer16_0_counter <= flash_time) )
 {
   Set_Value( port_number, bit_position, 0 );//port ?_? LED on
 }
 if ( (timer16_0_counter > flash_time) && (timer16_0_counter <= flash_time+off_time) )
 {
   Set_Value( port_number, bit_position, 1 );//port ?_? LED off
 }
 else if ( timer16_0_counter > flash_time+off_time )
 {
   timer16_0_counter = 0;
 }
#endif
  }
}
