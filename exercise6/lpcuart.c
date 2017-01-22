#include "LPC11xx.h"
#include "lpcuart.h"

void UART_init (uint32_t baudrate)
{
		uint32_t DL_value;
	  uint32_t Clear=Clear;   
    LPC_SYSCON->SYSAHBCLKCTRL |= (1<<16); 
    LPC_IOCON->PIO1_6 &= ~0x07;
    LPC_IOCON->PIO1_6 |= 0x01;//set P1.6 for RX
    LPC_IOCON->PIO1_7 &= ~0x07;
    LPC_IOCON->PIO1_7 |= 0x01;//set P1.7 for TX
    LPC_SYSCON->SYSAHBCLKCTRL &= ~(1<<16); 
    LPC_SYSCON->UARTCLKDIV = 0x1;//UART_PCLK clock divider values,divide by 1.  
    LPC_SYSCON->SYSAHBCLKCTRL |= (1<<12);//enables clock for UART
    LPC_UART->LCR = 0x83;//8-bit character length,access to divisor latches.   
    DL_value = SystemAHBFrequency/16/baudrate ;  
    LPC_UART->DLM = DL_value / 256;   
    LPC_UART->DLL = DL_value % 256;   
    LPC_UART->LCR = 0x03; //DLAB set 0  
    LPC_UART->FCR = 0x07;//Enable FIFO.clear all bytes in UART TX FIFO and RX.    
    Clear = LPC_UART->LSR;  
}

uint8_t UART_recive (void)
{
		while(! ( LPC_UART->LSR & (1<<0) ) ){
		 
		};
		return( LPC_UART->RBR );                
}

void UART_send_byte (uint16_t byte)
{
		LPC_UART->THR = byte;
		while (! ( LPC_UART->LSR & (1<<5) ) ){
			
		};
		
}

void UART_send(uint8_t *BufferPtr, uint32_t Length)
{  
		while ( Length != 0 )
		{	  
				LPC_UART->THR = *BufferPtr;
				BufferPtr++;
				Length--;
		}
		return;
}