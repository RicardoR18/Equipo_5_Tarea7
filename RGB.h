/*
 * RGB.h
 *
 *  Created on: 12 sep 2021
 *      Author: Erick Luna y Ricardo Ruiz
 */

#ifndef RGB_H_
#define RGB_H_

typedef enum{
				RED,
				BLUE,
				GREEN,
				WHITE,
				PURPLE,
				YELLOW,
				BLACK,		// apaga los colores
}color;


/*Funciones para prender color individual para
 *ahorrar tiempo de comparacion de switch case*/

void RGB_RED_ON(void);

void RGB_BLUE_ON(void);

void RGB_GREEN_ON(void);

void RGB_WHITE_ON(void);

void RGB_PURPLE_ON(void);

void RGB_YELLOW_ON(void);

 /* enciende cualquier color*/

void RGB_color_on(uint32_t color);

/* apaga color*/

void RGB_color_off(uint32_t color);

/* Apaga todo */
void RGB_off();


#endif /* RGB_H_ */
