

#ifndef LCDCONFIG8_H
#define	LCDCONFIG8_H

#define RS RC0
#define EN RC1
#define DATA PORTD
#define _XTAL_FREQ 8000000  //Constante para delay

#include <xc.h>

void Lcd_Port(char a);
void Lcd_Cmd(char a);
void Lcd_Clear(void);
void Lcd_Set_Cursor(char a, char b);
void ac(void);
void Lcd_Init(void);
void Lcd_Write_Char(char a);
void Lcd_Write_String(char *a);
void Lcd_Shift_Right(void);
void Lcd_Shift_Left(void);

#endif	