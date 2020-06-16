/*
 * i2c.h
 *
 *  Created on: 8 sty 2020
 *      Author: Macias
 *
 *  -DODAC TIMEOUTY
 *  -LEPSZE OPISY
 */

#ifndef I2C_I2C_H_
#define I2C_I2C_H_

#define ACK 1
#define NACK 0

#define I2C_FREQ 		100000UL
#define I2C_PRES 		1
#define I2C_TWBR_SET 	((F_CPU/I2C_FREQ)-16UL)/(2UL*I2C_PRES)
#define PRES_MASK 		0xFC

#if I2C_PRES == 1
#define I2C_TWPS	0x00
#endif

#define TWSR_STATUS TWSR
#define TWSR_MASK	0xF8

/* Status codes in register TWSR. If 5 older bits in TWSR register are equal to status codes listed below, operation was success. */
#define	START_ERR			0x08	///<	START status code
#define	REP_START_ERR		0x10	///<	REPEATED START status code
#define	MT_SLA_ACK_ERR		0x18	///<	ACK received status code (after SLA+W transmission for Master Transmitter Mode)
#define	MR_SLA_ACK_ERR		0x40	///<	ACK received status code (after SLA+R transmission for Master Receiver Mode)


void i2c_init(void);
void i2c_read_buf(uint8_t slave_adr, uint8_t slave_mem, uint8_t len, uint8_t *buf);
void i2c_write_buf(uint8_t slave_adr, uint8_t slave_mem, uint8_t len, uint8_t *buf);
void i2c_start(void);
void i2c_stop(void);
void i2c_write(uint8_t byte);
uint8_t i2c_read(uint8_t ack);
void i2c_scan(void);

#endif /* I2C_I2C_H_ */
