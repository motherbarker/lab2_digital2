/* 
 * File:   main.c
 * Device: PIC16F887
 * Author: Carlos Daniel Valdez Coreas - 21976
 *Compiler: XC8 (v2.41)
 * 
 * Program: 
 * Hardware:
 * 
 * Created: 24 de julio del 2023
 * Last updated:
 */

/*--------------------------------- LIBRARIES --------------------------------*/
#include <xc.h>
#include <PIC16F887.h>
#include "adcconfig.h"
#include "lcdconfig.h"
#include "map.h"


/*---------------------------- CONFIGURATION BITS ----------------------------*/
// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)




/*----------------------- GLOBAL VARIABLES & CONSTANTS -----------------------*/
#define _XTAL_FREQ 8000000  //Constante para delay

uint16_t adc_value; 
uint16_t mapped_value;    //lectura del ADC
float k;

uint8_t b, c, d, e, f, g;     
        
/*-------------------------------- PROTOTYPES --------------------------------*/
void setup(void);

/*----------------------------- INTERRUPT VECTOR -----------------------------*/

/*--------------------------- INTERRUPT SUBROUTINES --------------------------*/

/*---------------------------------- TABLES ----------------------------------*/

/*----------------------------------- SETUP ----------------------------------*/
void setup(void){
   //entradas y salidas
    ANSEL = 0;  //PORTA digital
    ANSELH= 0b00100000; 
    TRISA = 0;  
    TRISC = 0;  
    PORTC = 0;  
    TRISD = 0;  
    PORTD = 0;  
    TRISE = 0;  
    PORTE = 0;  
    PORTA = 0;
    
    //OSCILLATOR CONFIG
    OSCCONbits.IRCF = 0b111;  //8MHz
    SCS = 1;
    
    //iocb_init(0x0F); // IOCB
    adc_init(1, 0, 8, 0b1101); //configuracion para ADC.
    
}
/*----------------------------------- MAIN -----------------------------------*/
int main(void) {
    setup();
    unsigned int a;
    Lcd_Init();
    Lcd_Clear();
    while(1){       //loop infinito
        
        //toma el valor del potenciometro 
        adc_value = adc_read();            //lee valor del pot
     
        k = MAP(0x1, 0x3FE, 0x00, 0x1F4);  //genera un multiplicador que convertira el valor de ADC a voltios
       
        mapped_value = k*adc_value;         //guarda el valor en voltios
        
        //operaciones para separar int en chars
        
        //suponiendo que el valor de mapped_value = 250 
        b = mapped_value / 10;  //  250/10 = 25
        c = mapped_value % 10;  //  250 % 10 = 0 cuarto dígito
        d = b / 10;             //  25/10 = 2
        e = b % 10;             //  25 % 10 = 5 tercer digito
        f = d / 10;             //  2/10 = 0 primer digito
        g = d % 10;             //  2 % 10 = 2segundo digito 
        
        //mostrar resultados en display
        Lcd_Set_Cursor(1,1);            //primera linea
        Lcd_Write_String("VALOR POT");
        Lcd_Set_Cursor(2,1);            //segunda linea
        //Lcd_Write_Char(f + 0x30);
        Lcd_Write_Char(g + 0x30);       //se suma 0x30 que es el 0 en ascii
        Lcd_Write_Char(0x2E);
        Lcd_Write_Char(e + 0x30);
        Lcd_Write_Char(c + 0x30);
        Lcd_Write_Char(0x56);
        
        __delay_ms(300);
   }
    
}
/*-------------------------------- SUBROUTINES -------------------------------*/

