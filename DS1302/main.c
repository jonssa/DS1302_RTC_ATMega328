/*
 * main.c
 *
 *  Created on: 22 kwi 2020
 *      Author: Macias
 */

#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>

#include "hd44780_i2c/hd44780_i2c.h"
#include "DS1302.h"

int main(void)
{
	lcd_init();
	DS1302_init();
	_delay_ms(1000);

	while(1)
	{
		clock_burst_read(&datatime);
		show_time(&datatime, 0, 0);

		_delay_ms(500);
	}
}
