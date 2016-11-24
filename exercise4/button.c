#include "LPC11xx.h"
#include "setport.h"                      
#include "clk_init.h"
#define TEST_TIMER_NUM 0
#define set_key Set_Dir(2,6,0)//set port2_6 input
#define KEY_DOWN  LPC_GPIO2->DATA&(1<<6)//port 2_6 press
extern volatile uint32_t timer16_0_counter;
extern volatile uint32_t timer16_1_counter;
void button(int port_number,int bit_postition,int short_click_time,int flash_time,int off_time){ 
	int short_click_mode;
	clk_init();
	set_key;
	Set_Dir(port_number,bit_postition,1); //set port ?_? output
	while (1)                                
  { 
		if((KEY_DOWN)==0){//port 2_6 press down
         timer16_0_counter = 0;
         while((KEY_DOWN)==0) {                               
    if((timer16_0_counter>0)&&(timer16_0_counter<=short_click_time)){	/*short click*/	
		short_click_mode=1;	
		}
		else if(timer16_0_counter>short_click_time){ /*long click*/
		 timer16_0_counter = 0;
		while((LPC_GPIO2->DATA&(1<<6))==0) { 
		if((timer16_0_counter>0)&&(timer16_0_counter<=flash_time)){		
		Set_Value(port_number,bit_postition,0);//LED ON		
		}else if((timer16_0_counter>flash_time)&&(timer16_0_counter<=flash_time+off_time)){
    Set_Value(port_number,bit_postition,1);//LED OFF    
		}else if((timer16_0_counter>flash_time+off_time)){
            timer16_0_counter = 0;  
        }if((KEY_DOWN)!=0){ /*port 2_6 don't press down */
          Set_Value(port_number,bit_postition,1);} /*LED OFF*/                            
	       }
      }
    }    if(short_click_mode==1){
      { LED_change(port_number,bit_postition);//port ?_? LED change mode 
             }      	
	        }
       }
	}
}