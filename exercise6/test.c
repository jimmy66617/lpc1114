#include "LPC11xx.h"
#include "lpcuart.h"
#include "adc.h"
#include "pwm.h"
#include "clk_init.h"

#define test_timer_number  0
extern volatile uint32_t timer0_16bit_counter;
volatile uint8_t UARTBuffer[0x40];
uint8_t recive_buffer;
uint8_t recive_buffer2;

uint8_t ConvertDigital ( uint8_t digital )
{
		uint8_t ascii_char;
		if ( (digital >= 0) && (digital <= 9) ){
				ascii_char = digital +0x30;//0~9 
		}
		else{
				ascii_char = digital - 0x0A;
				ascii_char = ascii_char+0x41;// A~F 
		}
		return ( ascii_char );
}

void init (void)
{
		uint32_t interval;
		LPC_SYSCON->SYSAHBCLKCTRL |= (1<<6);//enable AHB clock to GPIO domain
		interval = SystemAHBFrequency/1000 - 1;
		if ( interval > 0xFFFF ) {
				interval = 0xFFFF;
		}
		init_timer_16bit( test_timer_number, interval);//init timer16
		enable_timer_16bit( test_timer_number);//enable timer16 
		ADC_Init(7);
		UART_init(9600);
}

void UART_IRQHandler (void)
{
		uint32_t IRQ_ID;         // define RX interrupt ID
		uint8_t recive_buffer;    //recive_buffer for recive value
		IRQ_ID = LPC_UART->IIR;   // read interrupt ID
		IRQ_ID =((IRQ_ID>>1) & 0x7);// check bit3:bit1
		if ( IRQ_ID == 0x02 ) { //check the interrupt is made by RX interrupt
				recive_buffer = LPC_UART->RBR;
				if ( recive_buffer == '$' ) { //if recive is '$'
						UART_send_byte(recive_buffer); // send recive to PC
						recive_buffer2=recive_buffer; //PWM status
				}
				if ( recive_buffer == '#' ) {//if recive is '#'
						UART_send_byte(recive_buffer);// send recive to PC
						recive_buffer2=recive_buffer;//check PWM status
				}
		}
}
//send adc_value every 2 second,recive '$' turn on PWM,recive '#' turn off PWM 
int main(void)
{
		uint16_t adc_value;
		uint16_t adc_pwm;
		int x=0, i=0, y=1;
		timer0_16bit_counter = 0;//reset timer
		init();
		LPC_UART->IER = 0x01;  ////enable RX interrupt 
		NVIC_EnableIRQ(UART_IRQn); //enable UART interrupt
		while (1) {
				adc_value = ADC_Read2(7);
				adc_pwm = ADC_Read(7);
				if ( recive_buffer2 == '$' ) { //if recive '$' turn on PWM
						T32B0M0_PWM_Init(1000, adc_pwm);
				}
				x=0;
				y=1;
				for (i=0; i<=10; i++) { //binary to decimal
						if (i != 0) {
								y=y*2;
						}
						if ((adc_value>>i) & 0x1) {
								x=x+y;
						}
				}
				if(timer0_16bit_counter == 2000){//every 2 seconds
						UARTBuffer[0] = ConvertDigital( (uint8_t) (x/1000) );//thousands
						UARTBuffer[1] = ConvertDigital( (uint8_t) (x/100%10) );//hundreds
						UARTBuffer[2] = ConvertDigital( (uint8_t) (x/10%10) );//tens
						UARTBuffer[3] = ConvertDigital( (uint8_t) (x%10) );//ones
						UARTBuffer[4] = '\r';
						UARTBuffer[5] = '\n';
						UART_send((uint8_t *) UARTBuffer, 6);//send UARTBuffer
						timer0_16bit_counter = 0;
				}
		}
}