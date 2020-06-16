/*
 * DS1302.h
 *
 *  Created on: 28 kwi 2020
 *      Author: Macias
 */

#ifndef DS1302_H_
#define DS1302_H_

#define DDR_DS1302	DDRD
#define PORT_DS1302	PORTD
#define DATA_PIN	PIND

#define CLK_DS1302	(1<<PD3)
#define DATA_DS1302	(1<<PD2)
#define RST_DS1302	(1<<PD1)

#define CLK_OUTPUT	DDR_DS1302 |= CLK_DS1302
#define RST_OUTPUT	DDR_DS1302 |= RST_DS1302

#define DATA_OUTPUT	DDR_DS1302 |= DATA_DS1302
#define DATA_INPUT	DDR_DS1302 &= ~DATA_DS1302
#define DATA_PULLUP	DATA_PIN |= DATA_DS1302
#define DATA_HIZ	DATA_PIN &= ~(DATA_DS1302)

#define DATA_HIGH 	PORT_DS1302 |= DATA_DS1302
#define DATA_LOW 	PORT_DS1302 &= ~(DATA_DS1302)

#define CLK_HIGH 	PORT_DS1302 |= CLK_DS1302
#define CLK_LOW		PORT_DS1302 &= ~(CLK_DS1302)

#define RST_HIGH 	PORT_DS1302 |= RST_DS1302
#define RST_LOW 	PORT_DS1302 &= ~(RST_DS1302)

struct DataTime {
	uint8_t	seconds;
	uint8_t	minutes;
	uint8_t	hour;
	uint8_t	date;
	uint8_t	month;
	uint8_t	day;
	uint8_t	year;
};

void clock_burst_write(struct DataTime *data);
void clock_burst_read(struct DataTime *data);
void show_time(struct DataTime *data,  int y, int x);
void DS1302_writebyte(uint8_t byte);
uint8_t DS1302_readbyte(void);
static void reset(void);
void DS1302_init(void);
static uint8_t dec_to_bcd(uint8_t byte);
static uint8_t bcd_to_dec(uint8_t byte);

extern struct DataTime datatime;

#endif /* DS1302_H_ */
