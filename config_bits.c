#include "config_bits.h"

void configuration(){
    
    /////DIGITAL PORTS////
    TRISEbits.TRISE4 = 1; // E4 as input
    TRISEbits.TRISE2 = 0; // E2 as output
    TRISEbits.TRISE0 = 0; // E4 as output

    /////EXTERNAL INTERRUPTS////
    // Configure Int 1 (vector numbers defined in p32mx795512h.h)
    TRISEbits.TRISE8 = 1; // Set pin as input
    INTCONbits.INT1EP = 0; // Generat interrupts on {rising edge-1 falling edge - 0}
    IFS0bits.INT1IF = 0; // Reset int flag
    IPC1bits.INT1IP = 2; // Set interrupt priority (1..7) *** Set equal to ilpx above
    IEC0bits.INT1IE = 1; // Enable Int1 interrupts
    
    
    // Configure Int 2 (vector numbers defined in p32mx795512h.h)
    TRISEbits.TRISE9 = 1; // Set pin as input
    INTCONbits.INT2EP = 1; // Generat interrupts on {rising edge-1 falling edge - 0}
    IFS0bits.INT2IF = 0; // Reset int flag
    IPC2bits.INT2IP = 1; // Set interrupt priority (1..7) *** Set equal to ilpx above
    IEC0bits.INT2IE = 1; // Enable Int2 interrupts
    
    /// PWM CONFIGURATION ///
    //Fault pin disabled
    OC1CONbits.OCM = 6;          //pin 3
    //Compare Timer 0-Timer2 ; 1-Timer3
    OC1CONbits.OCTSEL = 0;    
    OC1RS = 0;
    OC1CONbits.ON = 1;
}