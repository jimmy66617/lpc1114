#include "LPC11xx.h"
#include "setport.h"
#include "delay.h"
#include "led.h"

#define on_time 1200000
#define off_time 1200000

//Flash port1_8 LED, on for 0.5 sec and off for 0.5 sec.
int main (void) 
{
		set_direction( 1, 8, 1 );//set port1_8 output
		while(1){
				led_set(1, 8, 1);//LED On
				delay(on_time); //LED on for 0.5 sec
				led_set(1, 8, 0);//LED Off
				delay(off_time);//LED off for 0.5 sec
		}
		
}  

