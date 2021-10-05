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

 /* enciende color*/

void RGB_color_on(uint32_t color);

/* apaga color*/

void RGB_color_off(uint32_t color);

/* Apaga todo */
void RGB_off();


#endif /* RGB_H_ */
