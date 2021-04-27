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
void PWM_update(int pwm);

//0°->1ms->2000
//90°->1.5ms->3000
//180°->2ms->4000

int main(void) {
    AD1PCFGL = 0xFFFF;
    PWM_init();
    
    int i=0;
    
    while(1){
        
        for(i=2000; i<=4000; i=i+100){
           PWM_update(i);
           __delay_ms(500);
        }
        i=2000;
        PWM_update(i);
        __delay_ms(500);
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
    
    PDC2 = 0;           //Registro de DutyCicle 40000->100%
    PTCONbits.PTEN =1; //Habilito el periferico PWM
    
    
}

void PWM_update(int pwm){
    
    PDC2 = pwm;       //Registro de DutyCicle 40000->100%
    
}