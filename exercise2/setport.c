#include "LPC11xx.h" 
#include "setport.h"

volatile uint32_t GPIOShadowPort0;
volatile uint32_t GPIOShadowPort1;
volatile uint32_t GPIOShadowPort2;
volatile uint32_t GPIOShadowPort3;
void Set_Dir(int port_number,int bit_position,int direction){
   switch ( port_number )
  {
	case 0:
	  if ( !(LPC_GPIO0->DIR & (0x1<<bit_position)) && (direction == 1) )
		LPC_GPIO0->DIR |= (0x1<<bit_position);//set port0_?output
	  else if ( (LPC_GPIO0->DIR & (0x1<<bit_position)) && (direction == 0) )
		LPC_GPIO0->DIR &= ~(0x1<<bit_position);//set port0_? input	  
	break;
 	case 1:
	  if ( !(LPC_GPIO1->DIR & (0x1<<bit_position)) && (direction == 1) )
		LPC_GPIO1->DIR |= (0x1<<bit_position);//set port1_? output
	  else if ( (LPC_GPIO1->DIR & (0x1<<bit_position)) && (direction == 0) )
		LPC_GPIO1->DIR &= ~(0x1<<bit_position);//set port1_? input	  
	break;
	case 2:
	  if ( !(LPC_GPIO2->DIR & (0x1<<bit_position)) && (direction == 1) )
		LPC_GPIO2->DIR |= (0x1<<bit_position);//set port2_? output
	  else if ( (LPC_GPIO2->DIR & (0x1<<bit_position)) && (direction == 0) )
		LPC_GPIO2->DIR &= ~(0x1<<bit_position);//set port2_? input	  
	break;
	case 3:
	  if ( !(LPC_GPIO3->DIR & (0x1<<bit_position)) && (direction == 1) )
		LPC_GPIO3->DIR |= (0x1<<bit_position);//set port3_? output
	  else if ( (LPC_GPIO3->DIR & (0x1<<bit_position)) && (direction == 0) )
		LPC_GPIO3->DIR &= ~(0x1<<bit_position);//set port3_? input	  
	break;
	default:
	  break;
  }
  return;
}
void Set_Value( int port_number,int bit_position,int bit_value )
{
  
  switch (  port_number )
  {
	case 0:
	  if(bit_value)
		GPIOShadowPort0 |= (1<<bit_position);//set port0_? off					 
	  else
		GPIOShadowPort0 &= ~(1<<bit_position);//set port0_? on 
	 LPC_GPIO0->DATA = GPIOShadowPort0;
	break;
 	case 1:
	 if(bit_value)
		 GPIOShadowPort1 |= (1<<bit_position);//set port1_? off
	 else
		 GPIOShadowPort1 &= ~(1<<bit_position);//set port1_? on

	 LPC_GPIO1->DATA = GPIOShadowPort1;
	break;
	case 2:
	 if(bit_value)
		 GPIOShadowPort2 |= (1<<bit_position);//set port2_? off
	 else
		 GPIOShadowPort2 &= ~(1<<bit_position);//set port2_? on

	 LPC_GPIO2->DATA = GPIOShadowPort2;
	break;
	case 3:
	 if(bit_value)
		 GPIOShadowPort3 |= (1<<bit_position);//set port3_? off
	 else
		 GPIOShadowPort3 &= ~(1<<bit_position);//set port3_? on

	 LPC_GPIO3->DATA = GPIOShadowPort3;
	break;
	default:
	  break;
  }
  return;
}          

void LED_change(int port_number,int bit_position){
	if(port_number==0){
		LPC_GPIO0->DATA^=(1<<(bit_position));
	}else if(port_number==1){
		LPC_GPIO1->DATA^=(1<<(bit_position));
	}else if(port_number==2){
		LPC_GPIO2->DATA^=(1<<(bit_position));
	}else if(port_number==3){
		LPC_GPIO3->DATA^=(1<<(bit_position));
	}
}