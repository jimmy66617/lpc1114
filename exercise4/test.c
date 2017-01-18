#include "LPC11xx.h"
#include "setport.h"                      
#include "clk_init.h"
#include "led.h"

#define test_timer_number 0
#define interval  SystemAHBFrequency/1000 - 1
#define short_click_time 500
#define flash_time 250
#define off_time 250

extern volatile uint32_t timer0_16bit_counter;

static __inline void set_button (void){
	set_direction(2,6,0);
}

static __inline int button_click (void){
	return LPC_GPIO2->DATA&(1<<6);
}

int main(void)
{
		LPC_GPIO2->IS |= (1<<6);
		LPC_GPIO2->IE |= (1<<6);
		NVIC_EnableIRQ ( EINT2_IRQn );
		NVIC_SetPriority( EINT2_IRQn, 3 );
		while(1){
		
		};	
}

void PIOINT2_IRQHandler ()	
{ 
		if( (LPC_GPIO2->MIS&(1<<6)) == (1<<6) ) { 
				int short_click_mode;
				init_timer_16bit (test_timer_number, interval);
				enable_timer_16bit (test_timer_number);
				set_button();
				set_direction (2, 7, 1); //set port 2_7 LED output
				while (1) { 
						if ( button_click() == 0 ) {//port 2_6 button click
								timer0_16bit_counter = 0;
								while ( button_click() == 0 ) {                               
										if( (timer0_16bit_counter>0) && (timer0_16bit_counter<=short_click_time) ) {	/*short click*/	
												short_click_mode = 1;	
										}
										else if ( timer0_16bit_counter > short_click_time ) { /*long click*/
												timer0_16bit_counter = 0;
												while ( button_click() == 0 ) { 
														if ( (timer0_16bit_counter>0) && (timer0_16bit_counter <= flash_time) ) {		
																led_set(2, 7, 1);//LED ON		
														}
														else if ( (timer0_16bit_counter > flash_time) && (timer0_16bit_counter <= flash_time + off_time) ) {
																led_set(2, 7, 0);//LED OFF    
														}
														else if ( (timer0_16bit_counter > flash_time+off_time) ) {
																timer0_16bit_counter = 0;  
														}
														if( button_click() != 0 ) { /*port 2_6 don't click */
																led_set(2, 7, 0);/*LED OFF*/
														}                             
												}
										}
								}
								if( short_click_mode == 1 ) { 
										led_change_mode(2, 7);//port 2_7 LED change mode 
								}      		        
						}
				}
				LPC_GPIO2->IC=0xFFF;
		}	
 }
