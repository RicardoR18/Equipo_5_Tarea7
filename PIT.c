/*
 * PIT.c
 *
 *  Created on: Sep 25, 2021
 *      Author: Ricardo Ruiz.
 *      		Erick Luna.
 */



#include "stdint.h"
#include "MK64F12.h"
#include "PIT.h"
#define Default_SW_status (3)
volatile uint8_t PIT0_user_status_flag = 0;
volatile uint8_t PIT1_user_status_flag = 0;
volatile uint8_t PIT0_total_input = Default_SW_status;


uint8_t PIT0_get_total_input(void){

	return PIT0_total_input;
}
/********************************************************************************************/
void PIT0_IRQHandler(void){
	uint32_t total_input =(((GPIOA -> PDIR) & (0x10))>>4) | (((GPIOC -> PDIR) & (0x40))>>5);
	if(Default_SW_status != total_input){
		PIT0_total_input = total_input;
	}
	PIT->CHANNEL[0].TFLG |= PIT_TFLG_TIF_MASK;
	volatile uint32_t dummyRead = PIT->CHANNEL[0].TCTRL;
}
void PIT1_IRQHandler(void){
	PIT1_user_status_flag = 1;
	PIT->CHANNEL[1].TFLG |= PIT_TFLG_TIF_MASK;
	volatile uint32_t dummyRead = PIT->CHANNEL[1].TCTRL;
}
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 This function configure the PIT to generate a delay base on the system clock.
 	 It is important to note that this strictly is not device driver since everything is
 	 contained in a single function,  in general you have to avoid this practices, this only
 	 for the propose of the homework

 	 \param[in]  pit_timer channel to be used.
	 \param[in]  system_clock system clock use in the K64 (defult = 21e6).
	 \param[in]  delay the amount of time the delay the microcontroller
 	 \return void
 */
void PIT_delay(PIT_timer_t pit_timer, My_float_pit_t system_clock , My_float_pit_t delay){
	//LDVAL trigger = (period / clock period) -1
	//System_cloclk is divided by 2 because PIT works at 10.5Mhz.
	PIT->CHANNEL[pit_timer].LDVAL= ((uint32_t)(delay*system_clock))/2-1;
}

/********************************************************************************************/
/*!
 	 \brief	 This function enable the clock signal of the pit

 	 \param[in]  void.
 	 \return void
 */
void PIT_clock_gating(void){
	SIM->SCGC6 |= SIM_SCGC6_PIT_MASK;
}

/********************************************************************************************/
/*!
 	 \brief	It return the status of the interrupt flag. This flag is a variable created by the programmer.
 	 It is not the flag related with bit TIF in PIT->CHANNEL[0].TFLG |= PIT_TFLG_TIF_MASK, this flag must be clear in the ISR of the PIT

 	 \param[in]  void.
 	 \return uint8_t flag status
 */
uint8_t PIT0_get_interrupt_flag_status(void){

	return PIT0_user_status_flag;
}
uint8_t PIT1_get_interrupt_flag_status(void){

	return PIT1_user_status_flag;
}

/********************************************************************************************/
/*!
 	 \brief	Clears the interrupt flag created by the programmer.
 	 It is not the flag related with bit TIF in PIT->CHANNEL[0].TFLG |= PIT_TFLG_TIF_MASK, this flag must be clear in the ISR of the PIT

 	 \param[in]  void.
 	 \return void
 */
void PIT0_clear_interrupt_flag(void){

	PIT0_user_status_flag = 0;
}
void PIT1_clear_interrupt_flag(void){

	PIT1_user_status_flag = 0;
}

/********************************************************************************************/
/*!
 	 \brief	It enables the PIT

 	 \param[in]  void.
 	 \return void
 */
void PIT_enable(void){
	//Enables the module .
	PIT->MCR = ~PIT_MCR_MDIS_MASK;
}
/********************************************************************************************/
/*!
 	 \brief	It enables Selected Channel timer.

 	 \param[in]  void.
 	 \return void
 */
void PIT_CH_enable(PIT_timer_t pit){
	//Enables the specific module.
	PIT->CHANNEL[pit].TCTRL |= PIT_TCTRL_TEN_MASK ;
}

/********************************************************************************************/
/*!
 	 \brief	It enable de interrupt capabilities of the PIT

 	 \param[in]  void.
 	 \return void
 */
void PIT_enable_interrupt(PIT_timer_t pit){
	PIT->CHANNEL[pit].TCTRL |= PIT_TCTRL_TIE_MASK ;
}

