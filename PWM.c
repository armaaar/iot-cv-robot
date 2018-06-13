
#include "PWM.h"

void PWM_init_OC0(void)
 {

	TCCR0 = (1<<WGM00) | (1<<WGM01) | (1<<COM01) | (1<<CS01);//fast PWM
														// Non-inverted
														// Pre-scaler = 8
	TCNT0 = 0;
	OCR0 = 0;
	DDRB |= (1<<PB3);

 }
void PWM_init_OC2(void)
 {

	TCCR2 = (1 << WGM20) | (1 << WGM21) | (1 << COM21) | (1 << CS21);
														//fast PWM with
														// Non-inverted
														// Pre-scaler = 8
	TCNT2 = 0;
	OCR2 = 0;
	DDRD |= (1 << PD7);
 }
void PWM_init_OC1A(void){
	TCCR1B = (1 << WGM12) | (1 << CS11); // presacler = 8
	TCCR1A = (1 << WGM10) | (1 << COM1A1) | (1 << COM1B1);
	TCNT1 = 0;
	DDRD |= (1 << PD5);

}
void PWM_init_OC1B(void){
	TCCR1B = (1 << WGM12) | (1 << CS11); // presacler = 8
	TCCR1A = (1 << WGM10) | (1 << COM1A1) | (1 << COM1B1);
	TCNT1 = 0;
	DDRD |= (1 << PD4);

}


void PWM_Duty_Cycle_OC1A(unsigned char Duty_Cycle)
 {
	OCR1A = Duty_Cycle;

 }

void PWM_Duty_Cycle_OC1B(unsigned char Duty_Cycle)
 {
	OCR1B = Duty_Cycle;

 }


void PWM_Duty_Cycle_OC0(unsigned char Duty_Cycle)
 {
	OCR0 = Duty_Cycle;

 }
void PWM_Duty_Cycle_OC2(unsigned char Duty_Cycle)
 {
	OCR2 = Duty_Cycle;

 }
