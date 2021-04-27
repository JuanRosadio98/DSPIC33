/*
 * File:   newmainXC16.c
 * Author: USERINT
 *
 * Created on 21 de abril de 2021, 05:42 PM
 */


#include "reloj.h"
#include <xc.h>

#include "libpic30.h"
#include "p33fj32mc202.h"
#include "config.h"

void PWM_init(void);

int main(void) {
    AD1PCFGL = 0xFFFF;
    PWM_init();
    
    while(1){
        
    }
    return 0;
}

void PWM_init(void){
    
    PTCONbits.PTOPS = 0;    //1:1 PWM Time Base Output Postscale Select bits
    PTCONbits.PTCKPS = 0;   //1:1 PWM time base input clock period is TCY
    PTCONbits.PTMOD = 0b10 ;//PWM time base operates in a Continuous Up/Down Count mode
    
    PTMR = 0;       //Valor del contador PWM comenzara en 0
    PTPER = 19999;  //Registro del periodo PWM - T=20ms f=50Hz
    
    PWMCON1bits.PMOD2 = 0; //Par de pines I/O PWM en Modo Independiente
    PWMCON1bits.PEN2H = 1; //PWM2H pin is enabled for PWM output
    PWMCON1bits.PEN2L = 1; //PWM2L pin is enabled for PWM output
    
    PDC2 = 20000;       //Registro de DutyCicle 40000->100%
    PTCONbits.PTEN =1; //Habilito el periferico PWM
    
    
}