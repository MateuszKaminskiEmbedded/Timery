#include <xc.h>
#include <stdio.h>
#include "DeviceConfig.h"
#include "delay.h"
#include "UART.h"

void Timer23Gated_Init(void){
    T2CON = 0x0;    // Stops any Timer2 operation
    T3CON = 0x0;    // Stops any Timer3 operation
    T2CONbits.T32 = 1;// TMRx and TMRy form a 32-bit timer
    T2CONbits.TGATE = 1;    // Gated time accumulation is enabled
    T2CONbits.TCS = 0;  // Internal peripheral clock
    T2CONbits.TCKPS = 0b000;    // 0 prescale value
    TMR2 = 0x0;
    TMR3 = 0x0;
    PR2 = 0xFFFFFFFF;
    PR3 = 0xFFFFFFFF;
    
    IEC0bits.T2IE = 1;	// Disable Timer 2 Interrupt
    IFS0bits.T2IF = 0;	// Clear interrupt flag for timer 2
    IPC2bits.T2IP = 3; 	// Interrupt priority 3
    IPC2bits.T2IS = 1; 	// Sub-priority 1
    IEC0bits.T2IE = 1;	// Enable Timer 2 Interrupt
    
    T2CONbits.ON = 1;   // Module is enabled
}

void __attribute__((vector(_TIMER_2_VECTOR), interrupt(ipl3soft), nomips16)) timer2_handler(){
	IFS0bits.T2IF = 0;	// Clear interrupt flag for timer 2
    int x;
    x = (TMR2 * 8)/1000000;
    printf("%d i w msec: %d\n\r", TMR2, x);
    TMR2 = 0x0;
    TMR3 = 0x0;
//    if(LATFbits.LATF0 == 0){
//        LATFbits.LATF0 = 1;
//    }else
//        LATFbits.LATF0 = 0;
}

void main(){
	// Ustaw porty jako cyfrowe
    ANSELA = 0;
    ANSELB = 0;
    ANSELC = 0;
    ANSELE = 0;
    ANSELG = 0;
    TRISFbits.TRISF1 = 1;
    TRISFbits.TRISF0 = 0;
    
    // Set up PPS for UART 5
	U5RXR = 0b1100; // RF0 = U5RX
	RPE15R = 0b01011; // RC9 = U5TX

    // Set up PPS for Timer2 Gate
    T2CKR = 0b1011;
    
	Set_MaxSpeed_Mode();
    
	UART_Init();

	Timer23Gated_Init();
	while (1){
        
    }
}

