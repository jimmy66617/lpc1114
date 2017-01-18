#ifndef __SETPORT_H 
#define __SETPORT_H
void set_direction (int port_number, int bit_position, int direction);
void set_value ( int port_number, int bit_position,int bit_value );
void led_change_mode (int port_number, int bit_position);
#endif
