/*
 * hd44780_i2c.c
 *
 *  Created on: 9 sty 2020
 *      Author: Macias
 */
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <avr/pgmspace.h>

#include "../i2c/i2c.h"
#include "hd44780_i2c.h"

uint8_t led = 0;

void lcd_writecommand(uint8_t byte) //ok!
{
	uint8_t buf[2];
	buf[0] = byte & 0xF0;
	buf[1] = ((byte<<4) & 0xF0);

	i2c_write_lcd(LCD_ADDRESS, 2, buf);

}

void lcd_writechar(uint8_t ch) //!ok
{
	uint8_t buf[2];
	buf[0] = (ch & 0xF0);
	buf[1] = ((ch<<4) & 0xF0);

	i2c_write_lcd_char(LCD_ADDRESS, 2, buf);

}

void i2c_writebyte_lcd(uint8_t slave_adr, uint8_t byte)
{
	i2c_start();
	i2c_write(slave_adr);
	i2c_write(E | led);
	i2c_write(byte | E | led);
	i2c_write(0x00 | led);
	i2c_stop();
	_delay_us(120);
}

void i2c_write_lcd(uint8_t slave_adr, uint8_t len, uint8_t *buf)
{
	i2c_start();
	i2c_write(slave_adr);
	while(len--)
	{
		i2c_write(E | led);
		i2c_write(*buf | E | led);
		i2c_write(led);
		buf++;
	}
	i2c_stop();
	_delay_us(120);
}

void i2c_write_lcd_char(uint8_t slave_adr, uint8_t len, uint8_t *buf)
{
	i2c_start();
	i2c_write(slave_adr);
	while(len--)
	{
		i2c_write(E | RS | led);
		i2c_write(*buf | RS | E | led);
		i2c_write(led | RS);
		buf++;
	}
	i2c_stop();
}

void clr_scr(void)
{
	lcd_writecommand(LCDC_CLR_SCR);
	_delay_ms(10);
}

inline void lcd_off(void)
{
	led = 0;
	lcd_writecommand(0);
}

inline void lcd_on(void)
{
	led = LCD_LED;
	lcd_writecommand(0);
}

inline void home(void)
{
	lcd_writecommand(LCDC_CUR_HOME);
}

void gotoxy(uint8_t y, uint8_t x)
{
	if(y==1)
		y = 0x40;
	lcd_writecommand(0x80 + x + y);
}

void lcd_str(char * str)
{
	register char znak;
	while ( (znak=*(str++)) ) lcd_writechar( znak );
}

void lcd_str_P(const char * str)
{
	register char znak;
	while ( (znak=pgm_read_byte(str++)) ) lcd_writechar( znak );
}

void lcd_int(int val)
{
	char bufor[17];
	lcd_str( itoa(val, bufor, 10) );
}

void lcd_hex(int val)
{
	char bufor[17];
	itoa(val, bufor, 2);
	if((bufor[0] == '0') && (bufor[1] == '\0'))
	{
		bufor[1] = '0';
		bufor[2] = '\0';
	}
	lcd_str( bufor );
}

void lcd_init(void)
{
	i2c_init();
	_delay_ms(15);
	i2c_writebyte_lcd(LCD_ADDRESS, 0x30);
	_delay_us(4100);
	i2c_writebyte_lcd(LCD_ADDRESS, 0x30);
	_delay_us(100);
	i2c_writebyte_lcd(LCD_ADDRESS, 0x30);
	_delay_us(100);
	i2c_writebyte_lcd(LCD_ADDRESS, 0x20);
	_delay_us(100);
	lcd_writecommand(LCDC_FUNC | LCDC_2L | LCDC_5X10);
	lcd_writecommand(LCDC_DISP | LCDC_CUR_OFF | LCDC_DISP_ON);
	lcd_writecommand(LCDC_LCD_MODE | LCDC_CUR_WIN_R);
	led = LCD_LED;
	clr_scr();
}
