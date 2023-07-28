
#include "lcdconfig8.h"

/* 
 * File: LCD.c  
 * Se utiliz? y se adaptaron las librer?as de Ligo George 
 * de la p?gina www.electrosome.com
 * Enlace: https://electrosome.com/lcd-pic-mplab-xc8/
 * Revision history: 
 */

//LCD Functions Developed by electroSome

void Lcd_Port(char a) {
    PORTD = a;
}

void Lcd_Cmd(char a) {
    RS = 0; // => RS = 0 // Dato en el puerto lo va interpretar como comando
    Lcd_Port(a);
    EN = 1; // => E = 1
    __delay_ms(4);
    EN = 0; // => E = 0
}

void ac(void){
    EN = 1; // => E = 1
    __delay_ms(4);
    EN = 0; // => E = 0
}

void Lcd_Clear(void) {
    Lcd_Cmd(0x01);
    __delay_ms(3);
}

/*void Lcd_Set_Cursor(char Address) {
    //  valid addresses are for line one 0x80 and line two are 0xC0   
    if ((Address >= 0x80 && Address <= 0xA8) || (Address >= 0xC0 && Address <= 0xE8))
    {
       Lcd_Cmd(Address);
        //return 1;
    }
    //else
      //  return 0;
}*/

void Lcd_Set_Cursor(char a, char b) {
    char temp, z, y;
    if (a == 1) {
        temp = 0x80 + b - 1;
        //z = temp >> 4;
        //y = temp & 0x0F;
        Lcd_Cmd(temp);
        //Lcd_Cmd(y);
    } else if (a == 2) {
        temp = 0xC0 + b - 1;
        //z = temp >> 4;
        //y = temp & 0x0F;
        //Lcd_Cmd(z);
        Lcd_Cmd(temp);
    }
}

void Lcd_Init(void) {
//    EN = 0;
    RS = 0;
    Lcd_Port(0x00);
    __delay_ms(40);
    Lcd_Cmd(0x30);
    __delay_ms(10);
    Lcd_Cmd(0x30);
    __delay_ms(5);
    Lcd_Cmd(0x30);
    /////////////////////////////////////////////////////
    Lcd_Cmd(0x38);
    Lcd_Cmd(0x0C);
    Lcd_Cmd(0x01);
    Lcd_Cmd(0x06);
}

void Lcd_Write_Char(char a) {
    RS = 1;
    Lcd_Port(a);
    EN = 1;
    __delay_us(40);
    EN = 0;
    //ac();
}

void Lcd_Write_String(char *a) {
    int i;
    for (i = 0; a[i] != '\0'; i++)
        Lcd_Write_Char(a[i]);
}

void Lcd_Shift_Right(void) {
    Lcd_Cmd(0x1C);
}

void Lcd_Shift_Left(void) {
    Lcd_Cmd(0x18);
}


