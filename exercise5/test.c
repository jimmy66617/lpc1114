#include "LPC11xx.h"
#include "pwm.h"
#include "adc.h"
//adjust the voltage fed into the ADC and control the brightness of the LED¡APWM channel output to control brightness of the LED 
int main(void)
{  
		float duty;
		T16B0M0_PWM_Init(duty,1000);
		ADC_Init(7);
		while (1) {      
		duty=ADC_Read(7);
		T16B0M0_PWM_SET(duty,1000);//cycle 10Hz			
		}
}
