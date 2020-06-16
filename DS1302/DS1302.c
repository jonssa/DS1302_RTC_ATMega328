/*
 * DS1302.c
 *
 *  Created on: 28 kwi 2020
 *      Author: Macias
 */
#include <avr/io.h>
#include <util/delay.h>

#include "hd44780_i2c/hd44780_i2c.h"
#include "DS1302.h"

struct DataTime datatime = {0};		//time structure initialization

void DS1302_writebyte(uint8_t byte)
{
	DATA_OUTPUT;

	for(int i=0; i<8; ++i)
	{
		CLK_LOW;
		_delay_us(1);

		DATA_LOW;
		if(byte & (1<<i))
			DATA_HIGH;
		_delay_loop_1(1);
		CLK_HIGH;
		_delay_us(1);
	}
	_delay_us(5);
}

uint8_t DS1302_readbyte(void)
{
	uint8_t byte = 0;
	DATA_INPUT;
	DATA_PULLUP;

	for(int i=0; i<8; ++i)
	{
		CLK_LOW;
		_delay_us(1);
		if(DATA_PIN & DATA_DS1302)
			byte |= 1<<i;
		CLK_HIGH;
		_delay_us(1);
	}
	return byte;
}

static inline void reset(void)
{
	CLK_LOW;
	RST_LOW;
	RST_HIGH;
}

static inline uint8_t dec_to_bcd(uint8_t byte)
{
	return ((byte/10) << 4) | (byte%10);
}

static inline uint8_t bcd_to_dec(uint8_t byte)
{
	return (((byte & 0x70) >> 4) * 10 + (byte & 0x0f));
}

void clock_burst_write(struct DataTime *data)
{
	reset();
	DS1302_writebyte(0x8E);
	DS1302_writebyte(0);	//disable Write Protection

	DS1302_writebyte(0xBE);
	DS1302_writebyte(dec_to_bcd(data->seconds));
	DS1302_writebyte(dec_to_bcd(data->minutes));
	DS1302_writebyte(dec_to_bcd(data->hour));
	DS1302_writebyte(dec_to_bcd(data->date));
	DS1302_writebyte(dec_to_bcd(data->month));
	DS1302_writebyte(dec_to_bcd(data->day));
	DS1302_writebyte(dec_to_bcd(data->year));
	DS1302_writebyte(0x80);
	reset();
}

void clock_burst_read(struct DataTime *data)
{
	reset();

	DS1302_writebyte(0xBF);
	data->seconds = bcd_to_dec(DS1302_readbyte());
	data->minutes = bcd_to_dec(DS1302_readbyte());
	data->hour = bcd_to_dec(DS1302_readbyte());
	data->date = bcd_to_dec(DS1302_readbyte());
	data->month = bcd_to_dec(DS1302_readbyte());
	data->day = bcd_to_dec(DS1302_readbyte());
	data->year = bcd_to_dec(DS1302_readbyte());
	DS1302_readbyte();
	reset();
}

void show_time(struct DataTime *data, int y, int x)
{
	gotoxy(y,x);
	if(data->hour < 10)
		lcd_writechar('0');
	lcd_int(data->hour);
	lcd_writechar(':');
	if(data->minutes < 10)
		lcd_writechar('0');
	lcd_int(data->minutes);
	lcd_writechar(':');
	if(data->seconds < 10)
		lcd_writechar('0');
	lcd_int(data->seconds);
}

void DS1302_init(void)
{
	CLK_OUTPUT;
	RST_OUTPUT;
	reset();
	DS1302_writebyte(0x8E);
	DS1302_writebyte(0);
	reset();
}
