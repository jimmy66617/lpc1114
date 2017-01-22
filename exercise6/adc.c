#include "LPC11xx.h"
#include "adc.h"

void ADC_Init (uint8_t Channel)
{
		if(Channel>7){ 
				return;
		}
		LPC_SYSCON->PDRUNCFG &= ~(0x1<<4);//ADC powered		 
		LPC_SYSCON->SYSAHBCLKCTRL |= (1<<13);//enables ADC clock     
		LPC_SYSCON->SYSAHBCLKCTRL |= (1<<16);//enables IO configuration block clock   
		switch(Channel)
		{
				case 0://set channel 0 
						LPC_IOCON->JTAG_TDI_PIO0_11 &= ~0x07;//clear        
						LPC_IOCON->JTAG_TDI_PIO0_11 |= 0x02;//set port0_11 to AD0      
						LPC_IOCON->JTAG_TDI_PIO0_11 &= ~(3<<3) ;//clear pull-down/pull-up resistor  
						LPC_IOCON->JTAG_TDI_PIO0_11 &= ~(1<<7) ;//set port0_11 to analog input  
						break;
				case 1://set channel 1			
						LPC_IOCON->JTAG_TMS_PIO1_0&= ~0x07;//clear              
						LPC_IOCON->JTAG_TMS_PIO1_0 |= 0x02;//set port1_0 to AD1               
						LPC_IOCON->JTAG_TMS_PIO1_0 &= ~(3<<3) ;//clear pull-down/pull-up resistor             
						LPC_IOCON->JTAG_TMS_PIO1_0 &= ~(1<<7) ;//set port1_0 to analog input         
						break;
				case 2://set channel 2 
						LPC_IOCON->JTAG_TDO_PIO1_1 &= ~0x07;//clear             
						LPC_IOCON->JTAG_TDO_PIO1_1 |= 0x02;//set port1_1 to AD2                
						LPC_IOCON->JTAG_TDO_PIO1_1 &= ~(3<<3) ;//clear pull-down/pull-up resistor            
						LPC_IOCON->JTAG_TDO_PIO1_1 &= ~(1<<7) ;//set port1_1 to analog input          
						break;
				case 3://set channel 3  
						LPC_IOCON->JTAG_nTRST_PIO1_2 &= ~0x07;//clear             
						LPC_IOCON->JTAG_nTRST_PIO1_2 |= 0x02;//set port1_2 to AD3                
						LPC_IOCON->JTAG_nTRST_PIO1_2 &= ~(3<<3) ;//clear pull-down/pull-up resistor             
						LPC_IOCON->JTAG_nTRST_PIO1_2 &= ~(1<<7) ;//set port1_2 to analog input           
						break;
				case 4://set channel 4  
						LPC_IOCON->ARM_SWDIO_PIO1_3 &= ~0x07;//clear           
						LPC_IOCON->ARM_SWDIO_PIO1_3 |= 0x02;//set port1_3 to AD4     
						LPC_IOCON->ARM_SWDIO_PIO1_3 &= ~(3<<3) ;//clear pull-down/pull-up resistor   
						LPC_IOCON->ARM_SWDIO_PIO1_3 &= ~(1<<7) ;//set port1_3 to analog input          
						break;
				case 5://set channel 5  
						LPC_IOCON->PIO1_4 &= ~0x07;//clear              
						LPC_IOCON->PIO1_4 |= 0x01;//set port1_4 to AD5                
						LPC_IOCON->PIO1_4 &= ~(3<<3) ;//clear pull-down/pull-up resistor             
						LPC_IOCON->PIO1_4 &= ~(1<<7) ;//set port1_4 to analog input           
						break;
				case 6://set channel 6  
						LPC_IOCON->PIO1_10 &= ~0x07;//clear              
						LPC_IOCON->PIO1_10 |= 0x01;//set port1_10 to AD6			
						LPC_IOCON->PIO1_10 &= ~(3<<3) ;//clear pull-down/pull-up resistor             
						LPC_IOCON->PIO1_10 &= ~(1<<7) ;//set port1_10 to analog input           
						break;
				case 7://set channel 7  
						LPC_IOCON->PIO1_11 &= ~0x07;//clear             
						LPC_IOCON->PIO1_11 |= 0x01;//set port1_11 to AD7                
						LPC_IOCON->PIO1_11 &= ~(3<<3) ;//clear pull-down/pull-up resistor             
						LPC_IOCON->PIO1_11 &= ~(1<<7) ;//set port1_11 to analog input          
						break;
				default:
						break;
		}
		LPC_SYSCON->SYSAHBCLKCTRL &= ~(1<<16);//clear IO configuration block clock    
		LPC_ADC->CR = (1<<Channel)|(24<<8);//  
}

uint16_t ADC_Read (uint8_t Channel)
{
		float adc_value;
		LPC_ADC->CR |= (1<<24);//start transform
    while( ( LPC_ADC->DR[Channel] & 0x80000000 ) == 0){
			
		};
		adc_value = (LPC_ADC->DR[Channel]>>6)&0x3FF;
		adc_value = (adc_value/1024)*100;//turn to voltage
		return adc_value;        
}

uint16_t ADC_Read2 (uint8_t Channel)
{
		float adc_value;
		LPC_ADC->CR |= (1<<24);//start transform
    while( ( LPC_ADC->DR[Channel] & 0x80000000 ) == 0){
			
		};
		adc_value = (LPC_ADC->DR[Channel]>>6)&0x3FF;
		//adc_value = (adc_value/1024)*100;
		return adc_value;
}