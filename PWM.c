/*
 * File:   PWM.c
 * Author: callu
 *
 * Created on 24 November 2019, 10:53
 */


#include "xc.h"
#include "PWM.h"

#define PWM1_LAT    LATCbits.LATC6
#define PWM2_LAT    LATCbits.LATC7
#define PWM3_LAT    LATCbits.LATC8
#define PWM4_LAT    LATBbits.LATB9 

#define PWM1_TRIS   TRISCbits.TRISC6 
#define PWM2_TRIS   TRISCbits.TRISC7 
#define PWM3_TRIS   TRISCbits.TRISC8
#define PWM4_TRIS   TRISBbits.TRISB9


#define INPUT   1
#define OUTPUT  0


void init_PWM (){
    // Initialising as outputs 
    PWM1_TRIS = OUTPUT  ;
    PWM2_TRIS = OUTPUT  ;
    PWM3_TRIS = OUTPUT  ;
    PWM4_TRIS = OUTPUT  ;
    
    _RP22R = 13 ; //13 = OC1 -> RC6[RP22]
    _RP23R = 14 ; //14 = OC2 -> RC7[RP23]
    _RP24R = 15 ; //15 = OC3 -> RC8[RP24]
    _RP9R  = 16 ; //16 = OC4 -> RB9[RP9]
    
//    OC1RS = 0x004F ;                // Period = 1/40kHz
//    OC1R  = 0x00FF ;                // DC = 50%
//    OC1CON2bits.SYNCSEL = 0x1F ;    // Self Sync
//    OC1CON2bits.OCTRIG = 0;         //sync mode
//    OC1CON1bits.OCTSEL = 0b111;     //FOSC/2
//    OC1CON1bits.OCM = 0b110;        //edge aligned
//    OC1CON2bits.TRIGSTAT = 1;       //manually trigger

    // PWM on RC6 
    OC1RS = 0x0030 ;                // Period = 1/40kHz
    OC1R  = 0x0017 ;                // DC = 50%
    OC1CON2bits.SYNCSEL = 0x1F ;    // Self Sync
    OC1CON2bits.OCTRIG = 0;         //sync mode
    OC1CON1bits.OCTSEL = 0b111;     //FOSC/2
    OC1CON1bits.OCM = 0b110;        //edge aligned
    OC1CON2bits.TRIGSTAT = 1;       //manually trigger
    
    //PWM on RC7 
    OC2RS = 0x0030;                // Second Timer
    OC2R  = 0x0018 ;                // First Timer
    T1CON = 0 ; 
    PR1 = 0x0030 ;
    T1CONbits.TON = 1 ; 
    
    OC2CON1bits.OCTSEL = 0b100;     //TMR1 ---
    OC2CON1bits.OCM =    0b111;       //centre aligned ----
    
    OC2CON2bits.SYNCSEL = 0x01011 ; // tmr1
    OC2CON2bits.OCTRIG = 1;         //sync mode with tmr 1
    OC2CON2bits.TRIGSTAT = 1;       //manually trigger
    OC2CON2bits.OCINV = 1 ;
}   

