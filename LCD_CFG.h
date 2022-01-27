/*
 * LCD_CFG.h
 *
 * Created: 1/5/2022 1:24:33 PM
 *  Author: Luck
 */ 


#ifndef LCD_CFG_H_
#define LCD_CFG_H_


//Your options are -> _8_BIT_MODE or _4_BIT_MODE
#define LCD_MODE       _4_BIT_MODE

#define LCD_DATA_PIN_4        PA3
#define LCD_DATA_PIN_5        PA4
#define LCD_DATA_PIN_6        PA5
#define LCD_DATA_PIN_7        PA6
#define LCD_RS_PIN            PA1
#define LCD_EN_PIN            PA2

#define LCD_DATA_PORT          A

#endif /* LCD_CFG_H_ */