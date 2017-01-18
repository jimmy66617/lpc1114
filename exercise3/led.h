#ifndef __LED_H 
#define __LED_H
void led_set( int port_number , int bit_position , int on);
void led_change_mode( int port_number , int bit_position );	
#endif