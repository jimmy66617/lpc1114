#include "LPC11xx.h"
#include "setport.h"
#include "delay.h"
#include "blinky.h"
void blink(int port_number,int bit_position,int flash_time,int off_time){
	 Set_Dir( port_number, bit_position, 1 );//set port?_? output
while(1){
	Set_Value(port_number, bit_position,0);/*LED On*/
	delay(flash_time); //LED flash_time
	Set_Value(port_number, bit_position,1);/*LED Off*/
	delay(off_time);//LED off_time
}
}