/******************************************************************************
 *
 * Module: Timer1
 *
 * File Name: Timer1.c
 *
 * Description: Source file for the Timer 1
 *
 * Author: Mohamed Mostafa
 *
 *******************************************************************************/
#include"timer1.h"
#include <avr/io.h>
#include"common_macros.h"
#include<avr/interrupt.h>
static volatile void (*g_callbackptr)(void) = NULL_PTR;
static volatile uint8 num_of_seconds = 200;
static volatile uint8 tick = 0;
static volatile uint8 executionflag = 0;
ISR(TIMER1_OVF_vect) {
	tick++;
	if (tick == num_of_seconds) {
		if (g_callbackptr != NULL_PTR) {
			tick = 0;
			if (executionflag == 1) {
				executionflag = 0;
				g_callbackptr();
			}
		}
	}
}
ISR(TIMER1_COMPA_vect) {
	tick++;
	if (tick == num_of_seconds) {
		if (g_callbackptr != NULL_PTR) {
			tick = 0;
			if (executionflag == 1) {
				executionflag = 0;
				g_callbackptr();
			}
		}
	}
}
void Timer1CountSECOND(uint8 seconds) {
	executionflag = 1;
	tick = 0;
	TCNT1 = 0;
	num_of_seconds = seconds;

}
void Timer1_init(const Timer1_ConfigType *config) {
	/**TCCR1A Initialization**/
	CLEAR_BIT(TCCR1A, COM1A0);
	CLEAR_BIT(TCCR1A, COM1A1);
	CLEAR_BIT(TCCR1A, COM1B0);
	CLEAR_BIT(TCCR1A, COM1B1);
	SET_BIT(TCCR1A, FOC1A);
	SET_BIT(TCCR1A, FOC1B);
	/**TCCR1B Initialization**/
	if (config->Timer1_Mode == TIMER1_NORMAL) {
		CLEAR_BIT(TCCR1A, WGM10);
		CLEAR_BIT(TCCR1A, WGM11);
		CLEAR_BIT(TCCR1B, WGM12);
		CLEAR_BIT(TCCR1B, WGM13);
	} else if (config->Timer1_Mode == TIMER1_COMPARE) {
		CLEAR_BIT(TCCR1A, WGM10);
		CLEAR_BIT(TCCR1A, WGM11);
		SET_BIT(TCCR1B, WGM12);
		CLEAR_BIT(TCCR1B, WGM13);
	}
	/**Clock Selection**/
	TCCR1B = (TCCR1B & 0xf8) | (config->Timer1_Prescaler & 0x07);
	/**Putting the initial Count and the Compare Value**/
	TCNT1 = config->initial_value;
	OCR1A = config->compare_value;
	/**Selecting The Interrupt Mode**/
	//SET_BIT(SREG, 7);
	if (config->Timer1_Mode == TIMER1_NORMAL) {
		CLEAR_BIT(TIMSK, OCIE1A);
		SET_BIT(TIMSK, TOIE1);
	} else if (config->Timer1_Mode == TIMER1_COMPARE) {
		CLEAR_BIT(TIMSK, TOIE1);
		SET_BIT(TIMSK, OCIE1A);
	}

}
void Timer1_deinit(void) {
	/**Clearing all the Timer registers**/
	TCCR1A = 0;
	TCCR1B = 0;
	TIMSK = 0;
	TCNT1 = 0;
	OCR1A = 0;
}
void Timer1_setCallBack(void (*callbackptr)(void)) {
	/**Setting the Callback PTR to the function that is called by the ISR**/
	g_callbackptr = callbackptr;
}

