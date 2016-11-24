#ifndef __SETPORT_H 
#define __SETPORT_H
void Set_Dir(int port_number,int bit_position,int direction);
void Set_Value( int port_number,int bit_position,int bit_value );
void LED_change(int port_number,int bit_position);
#endif
