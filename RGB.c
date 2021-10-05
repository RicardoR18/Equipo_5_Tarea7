/*
 * RGB.c
 *
 *  Created on: 12 sep 2021
 *      Author: Erick Luna y Ricardo Ruiz
 */

#include "MK64F12.h"
#include "RGB.h"
#include "GPIO.h"
#include "Bits.h"


void RGB_color_on(uint32_t color){
	switch(color)
	{
		case RED:
			GPIO_clear_pin(GPIO_B, bit_22);
			break;
		case BLUE:
			GPIO_clear_pin(GPIO_B, bit_21);
			break;
		case GREEN:
			GPIO_clear_pin(GPIO_E, bit_26);
			break;
		case WHITE:
			GPIO_clear_pin(GPIO_B, bit_21);
			GPIO_clear_pin(GPIO_B, bit_22);
			GPIO_clear_pin(GPIO_E, bit_26);
			break;
		case PURPLE:
			GPIO_clear_pin(GPIO_B, bit_21);
			GPIO_clear_pin(GPIO_B, bit_22);
			break;
		case YELLOW:
			GPIO_clear_pin(GPIO_B, bit_22);
			GPIO_clear_pin(GPIO_E, bit_26);
			break;
		default:
			return(FALSE);
			break;
		}
	return(TRUE);
}
void RGB_color_off(uint32_t color){
	switch(color)
	{
		case RED:
			GPIO_set_pin(GPIO_B, bit_22);
			break;
		case BLUE:
			GPIO_set_pin(GPIO_B, bit_21);
			break;
		case GREEN:
			GPIO_set_pin(GPIO_E, bit_26);
			break;
		case WHITE:
			GPIO_set_pin(GPIO_B, bit_21);
			GPIO_set_pin(GPIO_B, bit_22);
			GPIO_set_pin(GPIO_E, bit_26);
			break;
		case PURPLE:
			GPIO_set_pin(GPIO_B, bit_21);
			GPIO_set_pin(GPIO_B, bit_22);
			break;
		case YELLOW:
			GPIO_set_pin(GPIO_B, bit_22);
			GPIO_set_pin(GPIO_E, bit_26);
			break;
		default:
			return (FALSE);
			break;
		}
	return(TRUE);


}

void RGB_off(){

	GPIO_set_pin(GPIO_B, bit_21);
	GPIO_set_pin(GPIO_B, bit_22);
	GPIO_set_pin(GPIO_E, bit_26);

}

