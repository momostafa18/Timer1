/******************************************************************************
 *
 * Module: Timer1
 *
 * File Name: Timer1.h
 *
 * Description: Header file for the Timer 1
 *
 * Author: Mohamed Mostafa
 *
 *******************************************************************************/
#ifndef TIMER1_H_
#define TIMER1_H_
#include "std_types.h"
/*******************************************************************************
 * 							Configuration Struct
 *******************************************************************************/
typedef enum {
	TIMER1_NOCLK = 0,
	TIMER1_FCPU_1 = 1,
	TIMER1_FCPU_8 = 2,
	TIMER1_FCPU_64 = 3,
	TIMER1_FCPU_256 = 4,
	TIMER1_FCPU_1024 = 5
} Timer1_PrescalerType;
typedef enum {
	TIMER1_COMPARE = 0, TIMER1_NORMAL = 1
} Timer1_ModeType;
typedef struct {
	uint16 initial_value;
	uint16 compare_value;
	Timer1_PrescalerType Timer1_Prescaler;
	Timer1_ModeType Timer1_Mode;
} Timer1_ConfigType;
/*******************************************************************************
 * 							Function Definitions
 *******************************************************************************/
/**
 *This function Initializes Timer1 according to the settings given in the
 *configuration struct
 */
void Timer1_init(const Timer1_ConfigType *config);
/**
 * This Function deinitializes Timer1 and stop its operarion
 */
void Timer1_deinit(void);
/*
 * This function  sets the callback function that is callled when the timer
 * interrupt occurs
 * @param callbackptr
 */
void Timer1_setCallBack(void (*callbackptr)(void));
/*
 * This function is used to count specific number of seconds depends on the
 * compare value where if the compare value is equal to 1 second then this
 * function is used to count no of seconds in terms of one second
 * */
void Timer1CountSECOND(uint8 seconds);
#endif /* TIMER1_H_ */
