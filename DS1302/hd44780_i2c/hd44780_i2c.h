/*
 * hd44780_i2c.h
 *
 *  Created on: 9 sty 2020
 *      Author: Macias
 */

#ifndef HD44780_I2C_HD44780_I2C_H_
#define HD44780_I2C_HD44780_I2C_H_

#define RS			(1<<0)
#define RW			(1<<1)
#define E			(1<<2)
#define LCD_LED		(1<<3)
#define DB4_PIN		4
#define DB5_PIN		5
#define DB6_PIN		6
#define DB7_PIN		7

#define LCDC_FUNC	(1<<5)
#define LCDC_8BIT	(1<<4)
#define LCDC_4BIT	(0<<4)
#define LCDC_2L		(1<<3)
#define LCDC_1L		(0<<3)
#define LCDC_5X10	(1<<2)
#define LCDC_5X7	(0<<2)

#define LCDC_CUR		(1<<4)
#define LCDC_MOVE_WIN	(1<<3)
#define	LCDC_MOVE_CUR	(0<<3)
#define	LCDC_CUR_R		(1<<2)
#define	LCDC_CUR_L		(0<<2)

#define	LCDC_DISP		(1<<3)
#define	LCDC_DISP_ON	(1<<2)
#define	LCDC_DISP_OFF	(0<<2)
#define	LCDC_CUR_ON		(1<<1)
#define	LCDC_CUR_OFF	(0<<1)
#define	LCDC_BLINK_ON	(1<<0)
#define	LCDC_BLINK_OFF	(0<<0)

#define	LCDC_LCD_MODE	(1<<2)
#define	LCDC_CUR_WIN_R	(1<<1)
#define	LCDC_CUR_WIN_L	(0<<1)
#define	LCDC_MOVE_WIN_	(1<<0)
#define	LCDC_MOVE_CUR_	(0<<0)

#define	LCDC_CUR_HOME	(1<<1)

#define	LCDC_CLR_SCR	(1<<0)

#define LCD_ADDRESS	0x4E

void lcd_writechar(uint8_t ch);
void lcd_writecommand(uint8_t byte);
void i2c_writebyte_lcd(uint8_t slave_adr, uint8_t byte);
void i2c_write_lcd(uint8_t slave_adr, uint8_t len, uint8_t *buf);
void i2c_write_lcd_char(uint8_t slave_adr, uint8_t len, uint8_t *buf);
void lcd_init(void);
void clr_scr(void);
void lcd_off(void);
void lcd_on(void);
void home(void);
void gotoxy(uint8_t x, uint8_t y);
void lcd_str(char * str);
void lcd_str_P(const char * str);
void lcd_int(int val);
void lcd_hex(int val);


#endif /* HD44780_I2C_HD44780_I2C_H_ */
