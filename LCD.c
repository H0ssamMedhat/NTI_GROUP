/*
 * LCD.c
 *
 * Created: 1/5/2022 1:24:11 PM
 *  Author: Luck
 */ 

#include "LCD.h"
#include "LCD_CFG.h"
#include "LED.h"

void LCD_INIT(void)
{
	#if LCD_MODE    ==     _8_BIT_MODE
	PORT_MODE(LCD_DATA_PORT,OUTPUT);
	PIN_MODE(LCD_RS_PIN,OUTPUT);
	PIN_MODE(LCD_EN_PIN,OUTPUT);
	/***_THIS_COMMAND_TO_ACTIVE_8_BIT_MODE_***/
	LCD_WRITE_CMD(0x38);
	LCD_WRITE_CMD(0x0C);   /***_THIS_COMMAND_TO_TURN_ON_DISPLAY_AND_TURN_OFF_CURSOR_***/
	LCD_WRITE_CMD(0x01);   /***_THIS_COMMAND_TO_CLEAR_LCD_*****************************/
	LCD_WRITE_CMD(0x06);   /***_THIS_COMMAND_TO_MOVE_CURSOR_FROM_LEFT_TO_RIGHT_********/
	LCD_WRITE_CMD(0x02);   /***_THIS_COMMAND_TO_RETURN_HOME_***************************/
	#elif LCD_MODE   ==   _4_BIT_MODE
	PIN_MODE(LCD_DATA_PIN_4,OUTPUT);
	PIN_MODE(LCD_DATA_PIN_5,OUTPUT);
	PIN_MODE(LCD_DATA_PIN_6,OUTPUT);
	PIN_MODE(LCD_DATA_PIN_7,OUTPUT);
	
	PIN_MODE(LCD_RS_PIN,OUTPUT);
	PIN_MODE(LCD_EN_PIN,OUTPUT);
	/***_THIS_COMMAND_TO_ACTIVE_4_BIT_MODE_***/
	LCD_WRITE_CMD(0x33);
	LCD_WRITE_CMD(0x32);
	LCD_WRITE_CMD(0x28);
	
	LCD_WRITE_CMD(0x0C);   /***_THIS_COMMAND_TO_TURN_ON_DISPLAY_AND_TURN_OFF_CURSOR_***/
	LCD_WRITE_CMD(0x01);   /***_THIS_COMMAND_TO_CLEAR_LCD_*****************************/
	LCD_WRITE_CMD(0x06);   /***_THIS_COMMAND_TO_MOVE_CURSOR_FROM_LEFT_TO_RIGHT_********/
	LCD_WRITE_CMD(0x02);   /***_THIS_COMMAND_TO_RETURN_HOME_***************************/
	#endif
}
void LCD_WRITE_CHR(u8 character)
{
	#if LCD_MODE    ==     _8_BIT_MODE
	PIN_WRITE(LCD_RS_PIN,HIGH);
	PORT_WRITE(LCD_DATA_PORT,character);
	PIN_WRITE(LCD_EN_PIN,HIGH);
	_delay_ms(1);
	PIN_WRITE(LCD_EN_PIN,LOW);
	_delay_ms(5);
	#elif LCD_MODE    ==     _4_BIT_MODE
	PIN_WRITE(LCD_RS_PIN,HIGH);
	/*to send first half byte*/
	PORT_WRITE(LCD_DATA_PORT,(((character >> 1) & 0b01111000) | (PORT_READ(LCD_DATA_PORT) & 0b10000111)));
	PIN_WRITE(LCD_EN_PIN,HIGH);
	_delay_ms(1);
	PIN_WRITE(LCD_EN_PIN,LOW);
	_delay_ms(5);
	/*to send second half byte*/
	PORT_WRITE(LCD_DATA_PORT,(((character << 3) & 0b01111000) | (PORT_READ(LCD_DATA_PORT) & 0b10000111)));
	PIN_WRITE(LCD_EN_PIN,HIGH);
	_delay_ms(1);
	PIN_WRITE(LCD_EN_PIN,LOW);
	_delay_ms(5);
	#endif
}
void LCD_WRITE_CMD(u8 command)
{
	#if LCD_MODE    ==     _8_BIT_MODE
	PIN_WRITE(LCD_RS_PIN,LOW);
	PORT_WRITE(LCD_DATA_PORT,command);
	PIN_WRITE(LCD_EN_PIN,HIGH);
	_delay_ms(1);
	PIN_WRITE(LCD_EN_PIN,LOW);
	_delay_ms(5);
	#elif LCD_MODE    ==     _4_BIT_MODE
	PIN_WRITE(LCD_RS_PIN,LOW);
	/*to send first half byte*/
	PORT_WRITE(LCD_DATA_PORT,(((command >> 1) & 0b01111000) | (PORT_READ(LCD_DATA_PORT) & 0b10000111)));
	PIN_WRITE(LCD_EN_PIN,HIGH);
	_delay_ms(1);
	PIN_WRITE(LCD_EN_PIN,LOW);
	_delay_ms(5);
	/*to send second half byte*/
	PORT_WRITE(LCD_DATA_PORT,(((command << 3) & 0b01111000) | (PORT_READ(LCD_DATA_PORT) & 0b10000111)));
	PIN_WRITE(LCD_EN_PIN,HIGH);
	_delay_ms(1);
	PIN_WRITE(LCD_EN_PIN,LOW);
	_delay_ms(5);
	#endif
}
void LCD_WRITE_STR(u8*p)
{
	u8 i = 0;
	while(p[i] != '\0')
	{
		LCD_WRITE_CHR(p[i]);
		i++;
	}
}

void LCD_WRITE_INT(u32 num)
{
// 	u8 buff[16]; /* String to hold the ascii result */
// 	itoa(data,buff,10); /* 10 for decimal */
// 	LCD_WRITE_CHR(buff);

	u32 rem = 0;
	u8 arr [16];
	s8 i = 0;
	
	if (num == 0)
	{
		LCD_WRITE_CHR('0');
	}
	else
	{
		
	while (num != 0)
	{
		rem = num % 10;
		arr[i] = rem + 48;
		i++;
		num = num / 10;
	}
	
	i--;
	
	while (i > -1)
	{
		LCD_WRITE_CHR(arr[i]);
		i--;
	}
}

}

void LCD_GO_TO (u8 row,u8 col)
{
	u8 Loc[2] = {0x80 , 0xC0};
	LCD_WRITE_CMD(Loc[row] + col);
}

void LCD_CLR(void)
{
	LCD_WRITE_CMD(0x01);
}

void LCD_STOP_WATCH_DISPALY_INIT()
{
	LCD_GO_TO(0,4);
	LCD_WRITE_STR("00:00:00");
}


void LCD_STOP_WATCH_DISPALY(u8 sec,u8 min,u8 hr)
{
	LCD_GO_TO(0,6);
	LCD_WRITE_STR(":");
	LCD_GO_TO(0,9);
	LCD_WRITE_STR(":");
	u8 min1,min2,hr1,hr2 = 0;
	
	min1 = min / 10;
	min2 = min % 10;
	
	hr1 = hr / 10;
	hr2 = hr % 10;
	
	if (sec >= 60)
	{
		min ++;
		sec = 0;
	}
	
	if (min >= 60)
	{
		hr++;
		min = 0;
	}
	
	
	if (sec<10)
	{
		LCD_GO_TO(0,10);
		
		LCD_WRITE_CHR('0');
		//LCD_WRITE_INT(sec);
		LCD_GO_TO(0,11);
		LCD_WRITE_INT(sec);
	}
	else
	{
		LCD_GO_TO(0,10);
		LCD_WRITE_INT(sec);
	}
	
	
	
	LCD_GO_TO(0,8);
	LCD_WRITE_INT(min2);
	LCD_GO_TO(0,7);
	LCD_WRITE_INT(min1);
	
	LCD_GO_TO(0,5);
	LCD_WRITE_INT(hr2);
	LCD_GO_TO(0,4);
	LCD_WRITE_INT(hr1);
	
	//LCD_CLR();
	
	
}