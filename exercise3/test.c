#include "LPC11xx.h"                        
#include "clk_init.h"
#include "setport.h"
#include "led.h"

#define test_timer_number 0  /* 0 or 1 for 16-bit timers only */
#define interval  SystemAHBFrequency/1000 - 1
#define flash_time 1000
#define off_time 250

extern volatile uint32_t timer0_16bit_counter;

int main (void)
{
		init_timer_16bit (test_timer_number, interval);
		enable_timer_16bit (test_timer_number); 
		set_direction ( 2, 7, 1 );//set port ?_? outport 
		while (1) {
				#if test_timer_number
				#else
				/* I/O configuration and LED setting pending. */
						if ( (timer0_16bit_counter > 0) && (timer0_16bit_counter <= flash_time) ) {
								led_set( 2, 7, 1 );//port 2_7 LED on
						}
						if ( (timer0_16bit_counter > flash_time) && (timer0_16bit_counter <= flash_time+off_time) ) {
								led_set( 2, 7, 0 );//port 2_7 LED off
						}
						else if ( timer0_16bit_counter > flash_time+off_time ) {
								timer0_16bit_counter = 0;
						}
				#endif
		}
}
