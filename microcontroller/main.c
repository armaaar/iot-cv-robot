/*
 * main.c
 *
 *  Created on: Mar 4, 2018
 *      Author: ahmedsafwat
 */

#include <avr/io.h>
#include <util/delay.h>
#include "PWM.h"
#include "TWI.h"

#define SPEED 100

void MotorBR_forward(unsigned char speed);
void MotorBR_backward(unsigned char speed);
void MotorBL_forward(unsigned char speed);
void MotorBL_backward(unsigned char speed);


void MotorFR_forward(unsigned char speed);
void MotorFR_backward(unsigned char speed);
void MotorFL_forward(unsigned char speed);
void MotorFL_backward(unsigned char speed);

void Move_right(unsigned char speed);
void Move_left(unsigned char speed);
void Move_backward(unsigned char speed);
void Move_forward(unsigned char speed);

void Move_up_right(unsigned char speed);
void Move_up_left(unsigned char speed);
void Move_down_right(unsigned char speed);
void Move_down_left(unsigned char speed);

void Stop();


int main(){
	unsigned char data_TWI = 0;
	DDRD = 0xff;
	DDRB = 0xff;
	//PORTD = 0xff;

	//DDRC = 0xff;

	//Move_stop();



	while(1)
	{

		//Move_stop();
		/*Move_left(100);
		_delay_ms(4000);

		Stop();
		_delay_ms(20);
		_delay_ms(2000);
*/

		/*

		MotorBL_forward(100);
		MotorBR_forward(100);
		MotorFR_forward(100);
		MotorFL_forward(100);
		_delay_ms(20);
		/*MotorBL_backward(100);
		MotorBR_backward(100);
		MotorFL_backward(100);
		MotorFR_backward(100);
		_delay_ms(6000);*/
		TWI_init_slave(33);
		TWI_listen();

		//data_TWI = TWI_recieve();
		data_TWI = TWI_recieve_data_ACK();

		//PORTC ^= (1 << 2);
		//_delay_ms(500);



		/*TWI_init();
		TWI_address(33);
		data_TWI = TWI_recieve_data_ACK();*/
		//data_TWI = TWI_recieve_data_NACK();
		//data_TWI = TWI_recieve();

		if(data_TWI == 8){
			//PORTD ^= (1 << PD4);
			//PORTC ^= (1 << 2);
			Move_forward(SPEED);
			//_delay_ms(20);
		}
		else if(data_TWI == 6) {
			//PORTD ^= (1 << PD5);
			Move_right(SPEED);
			//_delay_ms(20);
		}
		else if(data_TWI == 5) {
			//PORTD ^= (1 << PD6);
			Stop();
			//_delay_ms(20);
		}
		else if(data_TWI == 4) {
			//PORTD ^= (1 << PD7);
			Move_left(SPEED);
			//PORTC ^= (1 << 2);
			//_delay_ms(20);
		}
		else if(data_TWI == 2) {

			Move_backward(SPEED);
			//PORTC ^= (1 << 2);
			//_delay_ms(20);
		}
		else if(data_TWI == 9) {
			Move_up_right(SPEED);
		}

		else if(data_TWI == 7) {
			Move_up_left(SPEED);
		}

		else if(data_TWI == 3) {
			Move_down_right(SPEED);
		}

		else if(data_TWI == 1) {
			Move_down_left(SPEED);
		}


		else{
			Stop();
		}


	}
	return 0;
}



void MotorBR_backward(unsigned char speed){
	DDRD |= (1 << PD3);
	PORTD &= ~(1 << PD3);
	PWM_init_OC0();
	PWM_Duty_Cycle_OC0(speed);
}
void MotorBR_forward(unsigned char speed){
	DDRD |= (1 << PD3);
	PORTD |= (1 << PD3);
	PWM_init_OC0();
	PWM_Duty_Cycle_OC0(speed);
}
// Back left functions
void MotorBL_forward(unsigned char speed){
	DDRD |= (1 << PD2);
	PORTD &= ~(1 << PD2);
	PWM_init_OC1A();
	PWM_Duty_Cycle_OC1A(speed);
}
void MotorBL_backward(unsigned char speed){
	DDRD |= (1 << PD2);
	PORTD |= (1 << PD2);
	PWM_init_OC1A();
	PWM_Duty_Cycle_OC1A(speed);
}

// Front Right functions
void MotorFR_backward(unsigned char speed){
	DDRD |= (1 << PD1);
	PORTD &= ~(1 << PD1);
	PWM_init_OC1B();
	PWM_Duty_Cycle_OC1B(speed);
}
void MotorFR_forward(unsigned char speed){
	DDRD |= (1 << PD1);
	PORTD |= (1 << PD1);
	PWM_init_OC1B();
	PWM_Duty_Cycle_OC1B(speed);
}

// Front Left functions
void MotorFL_forward(unsigned char speed){
	DDRD |= (1 << PD0);
	PORTD &= ~(1 << PD0);
	PWM_init_OC2();
	PWM_Duty_Cycle_OC2(speed);
}
void MotorFL_backward(unsigned char speed){
	DDRD |= (1 << PD0);
	PORTD |= (1 << PD0);
	PWM_init_OC2();
	PWM_Duty_Cycle_OC2(speed);
}

void Move_forward(unsigned char speed){
	MotorBL_forward(speed);
	MotorBR_forward(speed);
	MotorFR_forward(speed);
	MotorFL_forward(speed);
}

void Move_backward(unsigned char speed){
	MotorBL_backward(speed);
	MotorBR_backward(speed);
	MotorFR_backward(speed);
	MotorFL_backward(speed);
}

void Move_right(unsigned char speed){
	MotorBL_forward(speed);
	MotorBR_backward(speed);
	MotorFR_backward(speed);
	MotorFL_forward(speed);
}

void Move_left(unsigned char speed){
	MotorBL_backward(speed);
	MotorBR_forward(speed);
	MotorFR_forward(speed);
	MotorFL_backward(speed);
}

void Stop(){
	/*PWM_Duty_Cycle_OC2(0);
	PWM_Duty_Cycle_OC1B(0);
	PWM_Duty_Cycle_OC1A(0);
	PWM_Duty_Cycle_OC0(0);*/

	TCCR2 = 0;
	TCCR0 = 0;
	TCCR1B = 0;
	TCCR1A = 0;
	PORTD &= ~( (1 << PD4) | (1 << PD5) | (1 << PD7) );

	PORTB &= ~(1 << PB3);
}

void Move_up_right(unsigned char speed){
	MotorBL_forward(speed + 60);
	MotorBR_forward(speed - 60);
	MotorFR_forward(speed- 60);
	MotorFL_forward(speed + 60);
}

void Move_up_left(unsigned char speed){
	MotorBL_forward(speed - 60);
	MotorBR_forward(speed + 60);
	MotorFR_forward(speed + 60);
	MotorFL_forward(speed - 60);
}

void Move_down_right(unsigned char speed){
	MotorBL_backward(speed + 60);
	MotorBR_backward(speed - 60);
	MotorFR_backward(speed- 60);
	MotorFL_backward(speed + 60);
}

void Move_down_left(unsigned char speed){
	MotorBL_backward(speed - 60);
	MotorBR_backward(speed + 60);
	MotorFR_backward(speed + 60);
	MotorFL_backward(speed - 60);
}






