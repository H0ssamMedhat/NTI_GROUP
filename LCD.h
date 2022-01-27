/*
 * LCD.h
 *
 * Created: 1/5/2022 1:24:22 PM
 *  Author: Luck
 */ 


#ifndef LCD_H_
#define LCD_H_

#include "STD_TYPES.h"
#include "DIO.h"
#include "REG.h"
#define F_CPU 16000000UL
#include <util/delay.h>

void LCD_INIT(void);
void LCD_WRITE_CHR(u8);
void LCD_WRITE_CMD(u8);
void LCD_WRITE_STR(u8*);
void LCD_WRITE_INT(u32);
void LCD_CLR(void);
void LCD_GO_TO (u8,u8);
void LCD_STOP_WATCH_DISPALY_INIT(void);
void LCD_STOP_WATCH_DISPALY(u8,u8,u8);
extern u32 counter;

#define _4_BIT_MODE       4
#define _8_BIT_MODE       8

#endif /* LCD_H_ */