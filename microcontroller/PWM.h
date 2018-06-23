
#ifndef PWM_H_
#define PWM_H_

#include <avr/io.h>

void PWM_init_OC0(void);
void PWM_init_OC2(void);
void PWM_init_OC1A(void);
void PWM_init_OC1B(void);

void PWM_Duty_Cycle_OC1A(unsigned char Duty_Cycle);
void PWM_Duty_Cycle_OC1B(unsigned char Duty_Cycle);
void PWM_Duty_Cycle_OC0(unsigned char Duty_Cycle);
void PWM_Duty_Cycle_OC2(unsigned char Duty_Cycle);





#endif /* PWM_H_ */
