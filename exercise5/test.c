#include "LPC11xx.h"
#include "pwm.h"
#include "adc.h"

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