/*
 * i2c.c
 *
 *  Created on: 8 sty 2020
 *      Author: Macias
 */
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include "i2c.h"
//#include "../USART/usart.h"

void i2c_init(void)
{
	TWSR = ((TWSR & PRES_MASK) | I2C_TWPS);
	TWBR = (uint8_t)I2C_TWBR_SET;
}

void i2c_read_buf(uint8_t slave_adr, uint8_t slave_mem, uint8_t len, uint8_t *buf)
{
	i2c_start();
	i2c_write(slave_adr);
	i2c_write(slave_mem);
	i2c_start();
	i2c_write(slave_adr + 1);
	while(len--)
		*buf++ = i2c_read(len ? ACK : NACK);
	i2c_stop();
}

void i2c_write_buf(uint8_t slave_adr, uint8_t slave_mem, uint8_t len, uint8_t *buf)
{
	i2c_start();
	i2c_write(slave_adr);
	i2c_write(slave_mem);
	while(len--)
		i2c_write(*buf++);
	i2c_stop();
}

void i2c_start(void)
{
	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
	while(!(TWCR & (1<<TWINT)))
		continue;
}

void i2c_stop(void)
{
	TWCR = (1<<TWINT) | (1<<TWSTO) | (1<TWEN);
	while(!(TWCR & (1<<TWSTO)))
			continue;
}

void i2c_write(uint8_t byte)
{
	TWDR = byte;
	TWCR = (1<<TWINT) | (1<<TWEN);
	while(!(TWCR & (1<<TWINT)))
		continue;
}

uint8_t i2c_read(uint8_t ack)
{
	TWCR = (1<<TWINT) | (1<<TWEN) | (ack<<TWEA);
	while(!(TWCR & (1<<TWINT)))
		continue;
	return TWDR;
}

void i2c_scan(void)
{
	uint8_t i2c_status;
	char buf[10];

	//USART_print("Sprawdzam adresy... \n\r");

	for(int i=1; i<127; i++)
	{
		i2c_start();
		i2c_status = TWSR_STATUS & TWSR_MASK;
		if((i2c_status != START_ERR) & (i2c_status != REP_START_ERR))
		{
			//USART_print("Blad przy wysylaniu komendy START \n\r");
			break;
		}

		i2c_write((i<<1) & 0xFE);	///< need to move address variable to MSB direction due to LSB function (read/write bit - in this case write(LSB=0))
		i2c_status = TWSR_STATUS & TWSR_MASK;
		itoa(i, buf, 16);
		//USART_print("0x");
		//USART_print(buf);

		if((i2c_status != MT_SLA_ACK_ERR) & (i2c_status != MR_SLA_ACK_ERR))
			continue;
			//USART_print("\tACK = 0 - no response\n\r");
		//else
			//USART_print("\tfound I2C adress! ACK = 1\n\r");
	}
	_delay_ms(500);
}
