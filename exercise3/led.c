#include "LPC11xx.h" 

volatile uint32_t value0;
volatile uint32_t value1;
volatile uint32_t value2;
volatile uint32_t value3;

void led_set( int port_number , int bit_position , int on)
{
  
		switch (  port_number ) {
			
				case 0:
						if ( on ) {
								value0 &= ~(1<<bit_position);//set port0_? on		
            }							
						else {
								value0 |= (1<<bit_position);//set port0_? off
						}
						LPC_GPIO0->DATA = value0;
						break;
 	
				case 1:
						if ( on ){
								value1 &= ~(1<<bit_position);//set port1_? on
						}
						else {
								value1 |= (1<<bit_position);//set port1_? off
						}
						LPC_GPIO1->DATA = value1;
						break;
						
				case 2:
						if ( on ) {
								value2 &= ~(1<<bit_position);//set port2_? on
						}
						else {
								value2 |= (1<<bit_position);//set port2_? off
            }
						LPC_GPIO2->DATA =value2;
						break;
						
				case 3:
						if ( on ){
								value3 &= ~(1<<bit_position);//set port3_? on
	          }
						else {
								value3 |= (1<<bit_position);//set port3_? off
            }
						LPC_GPIO3->DATA = value3;
						break;
				default:
						break;
		}
		
		return;		
}
void led_change_mode( int port_number , int bit_position )
{
	
		if ( port_number == 0) {
				LPC_GPIO0->DATA^=(1<<(bit_position));//set port0_? LED change mode
		}
		else if ( port_number == 1) {
				LPC_GPIO1->DATA^=(1<<(bit_position));//set port1_? LED change mode
		}
		else if ( port_number == 2) {
				LPC_GPIO2->DATA^=(1<<(bit_position));//set port2_? LED change mode
		}
		else if ( port_number == 3) {
				LPC_GPIO3->DATA^=(1<<(bit_position));//set port3_? LED change mode
		}
		
}