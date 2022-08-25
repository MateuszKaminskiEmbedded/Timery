#include <xc.h>
#include <stdio.h>
#include "DeviceConfig.h"
#include "timer.h"
#include "UART.h"

void __attribute__((vector(_TIMER_2_VECTOR), interrupt(ipl3soft), nomips16)) timer2_handler(){
	IFS0bits.T2IF = 0;	// Clear interrupt flag for timer 2
//    float time;
//    time = (1000.0* 256 * TMR2)/SYS_FREQ;
//    printf("Czas: %2.3f s\n\r", time/1000);
//    TMR2 = 0x0;
//    TMR3 = 0x0;
    
    if(LATFbits.LATF0 == 0){
        LATFbits.LATF0 = 1;
    }else
        LATFbits.LATF0 = 0;
}

void main(){
	// Set ports as digital
    ANSELA = 0;
    ANSELB = 0;
    ANSELC = 0;
    ANSELE = 0;
    ANSELG = 0;
    TRISFbits.TRISF1 = 1;   // button
    TRISFbits.TRISF0 = 0;   // signal output
    TRISEbits.TRISE15 = 0;  // signal output UART
    CNPDFbits.CNPDF1 = 1;   // Pull down resistor for F1 pin
    
    // Set up PPS for UART 5
	//U5RXR = 0b1100; // RF0 = U5RX
	RPE15R = 0b01011; // RC9 = U5TX

    // Set up PPS for Timer2 Gate
    T2CKR = 0b1011; //F1
    
	Set_MaxSpeed_Mode();
	UART_Init();
//	Timer23Gated_Init();
    Timer2_Init(1000);
    
	while (1){
        
    }
}

