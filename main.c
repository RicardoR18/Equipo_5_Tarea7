/*
 * main.c
 *
 *  Created on: 04 oct 2021
 *      Author: Erick Luna and Ricardo Ruiz
 *  RGB color sequence controlled with a state machine with 2 push buttons.
 */
#include "MK64F12.h"
#include "GPIO.h"
#include "Bits.h"
#include "RGB.h"

#define GPIO_OFF_CONST (0xFFFFFFFFU)

void RGB_init(void);
void SW_init(void);

typedef enum {
	NO_COLOR,
	YELLOW_SQ1,
	RED_SQ1,
	PURPLE_SQ1,
	GREEN_SQ2,
	RED_SQ2,
	WHITE_SQ2,
	BLUE_SQ3,
	GREEN_SQ3,
	WHITE_SQ3,
}State_name_t;


typedef struct
{
	//uint32_t out;
	void (*FuncPoint)(void);
	uint16_t wait;
	uint8_t next[4];
}State_t;

uint32_t input_port_a = 0, input_port_c = 0, total_input = 0;
const State_t FSM_Moore[10]=
		{
			{&RGB_off		,65000 ,{BLUE_SQ3 , YELLOW_SQ1, GREEN_SQ2,NO_COLOR		}},	/* YELLOW_1 	*/
			{&RGB_YELLOW_ON ,65000 ,{BLUE_SQ3 , RED_SQ1   , GREEN_SQ2, RED_SQ1		}},	/* YELLOW_1 	*/
			{&RGB_RED_ON 	,65000 ,{BLUE_SQ3 , PURPLE_SQ1, GREEN_SQ2, PURPLE_SQ1	}},	/* RED_1 		*/
			{&RGB_PURPLE_ON ,65000 ,{BLUE_SQ3 , YELLOW_SQ1, GREEN_SQ2, YELLOW_SQ1	}},	/* PURPLE_1	*/

			{&RGB_GREEN_ON 	,65000 ,{BLUE_SQ3 , YELLOW_SQ1, RED_SQ2  , RED_SQ2		}},	/* GREEN_2 	*/
			{&RGB_RED_ON 	,65000 ,{BLUE_SQ3 , YELLOW_SQ1, WHITE_SQ2, WHITE_SQ2	}},	/* RED_2 		*/
			{&RGB_WHITE_ON	,65000 ,{BLUE_SQ3 , YELLOW_SQ1, GREEN_SQ2, GREEN_SQ2	}},	/* WHITE_2 	*/

			{&RGB_BLUE_ON	,65000 ,{GREEN_SQ3, YELLOW_SQ1, GREEN_SQ2, GREEN_SQ3	}},	/* BLUE_3 	*/
			{&RGB_GREEN_ON	,65000 ,{WHITE_SQ3, YELLOW_SQ1, GREEN_SQ2, WHITE_SQ3	}},	/* GREEN_3 	*/
			{&RGB_WHITE_ON	,65000 ,{BLUE_SQ3 ,	YELLOW_SQ1, GREEN_SQ2, BLUE_SQ3		}},	/* WHITE_3 	*/

		};

int main(void) {
	State_name_t current_state = NO_COLOR;

	// Turn on all ports needed
	GPIO_clock_gating(GPIO_A);
	GPIO_clock_gating(GPIO_B);
	GPIO_clock_gating(GPIO_C);
	GPIO_clock_gating(GPIO_E);
	//Initialize RGB and Switch button pins.
	RGB_init();
	SW_init();

	for(;;){
		FSM_Moore[current_state].FuncPoint();
		input_port_a = GPIOA -> PDIR;
		input_port_a &=(0x10);
		input_port_c = GPIOC -> PDIR;
		input_port_c &= (0x40);
		input_port_c = input_port_c >> 5;
		input_port_a = input_port_a >> 4;
		total_input = input_port_a | input_port_c;

		current_state = FSM_Moore[current_state].next[total_input];


	}



    return 0 ;
}

void RGB_init(void){
	gpio_pin_control_register_t pcr_gpiob_pin_21 = GPIO_MUX1;//Blue
	gpio_pin_control_register_t pcr_gpiob_pin_22 = GPIO_MUX1;//Red
	gpio_pin_control_register_t pcr_gpioe_pin_26 = GPIO_MUX1;//Greem
	GPIO_pin_control_register(GPIO_B,bit_21,&pcr_gpiob_pin_21);//BLUE
	GPIO_pin_control_register(GPIO_B,bit_22,&pcr_gpiob_pin_22);//RED
	GPIO_pin_control_register(GPIO_E,bit_26,&pcr_gpioe_pin_26);//GREEN

	GPIO_write_port(GPIO_B, GPIO_OFF_CONST);
	GPIO_write_port(GPIO_E, GPIO_OFF_CONST);

	GPIO_data_direction_pin(GPIO_B,GPIO_OUTPUT, bit_21);
	GPIO_data_direction_pin(GPIO_B,GPIO_OUTPUT,bit_22);
	GPIO_data_direction_pin(GPIO_E,GPIO_OUTPUT,bit_26);
}
void SW_init(void){
	gpio_pin_control_register_t pcr_gpioc_pin_6 = GPIO_MUX1|GPIO_PE|GPIO_PS;//sw2
	gpio_pin_control_register_t pcr_gpioa_pin_4 = GPIO_MUX1|GPIO_PE|GPIO_PS;//sw3
	GPIO_pin_control_register(GPIO_C,bit_6,&pcr_gpioc_pin_6);//SW2
	GPIO_pin_control_register(GPIO_A,bit_4,&pcr_gpioa_pin_4);//SW3


	GPIO_data_direction_pin(GPIO_C,GPIO_INPUT, bit_6);
	GPIO_data_direction_pin(GPIO_A,GPIO_INPUT, bit_4);
}
