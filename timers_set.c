#include "timers_set.h"

void setTimer(uint8_t timerRequested, uint16_t preScaler, uint32_t constantDivider){
    // T32 bit timer and TCKPS are available only in even type B timmers (2 and 4)
    // IFS0: TxIF (x = 0:5)
    // IEC0: TxIE (x = 0:5)
    // IPCx.TxIP (x = 0:5)
    // IPCx.TxIS (x = 0:5)

    if (timerRequested == 1){
        // Type A
        T1CONbits.ON = 0;           // Stop Timer
        T1CONbits.TCKPS = preScaler;        // Prescaler 3->256;2->64;1->8;0->1
        T1CONbits.TCS = 0;          // Internal Peripheral Clock
        // When TCS = 1
        //T1CONbits.TSYNC = 0;      // External clock input is not syncronized
        PR1 = constantDivider;      // 16 bit period match
        TMR1 = 0;                   // Clear Timmer Register
        
        IPC1bits.T1IP = 5;          // Interrupt Priority
        IPC1bits.T1IS = 2;          // Interrupt Subpriority
        IFS0bits.T1IF = 0;          // Reset interrupt flag
        IEC0bits.T1IE = 1;          // Enable Interrupt
        
        T1CONbits.TON = 1;          // Enable Timmer
        
    }else if(timerRequested == 2){
        // Type B even
        T2CONbits.ON = 0;           // Stop timer
        T2CONbits.TCKPS = preScaler;    // Prescaler 7->256;6->64;5->32;4->16;3->8;2->4;1->2;0->1
        T2CONbits.T32 = 0;          // TMRX and TMRY form separate 16 bit timmer (=1: form 32 bit timmer)
        T2CONbits.TCS = 0;          // Internal Peripheral Clock

        PR2 = constantDivider;      // 16 bit period match
        TMR2 = 0;                   // Clear Timmer Register

        IPC2bits.T2IP = 3;          // Interrupt Priority
        IPC2bits.T2IS = 3;          // Interrupt Subpriority
        IFS0bits.T2IF = 0;          // Reset interrupt flag
        IEC0bits.T2IE = 1;          // Enable Interrupt

        T2CONbits.TON = 1;          // Enable Timmer
        
    }else if (timerRequested == 3){
        // Type B odd
        T3CONbits.ON = 0;           // Stop timer
        T3CONbits.TCKPS = preScaler;    // Prescaler 7->256;6->64;5->32;4->16;3->8;2->4;1->2;0->1
        T3CONbits.TCS = 0;          // Internal Peripheral Clock
        PR3 = constantDivider;      // 16 bit period match
        TMR3 = 0;                   // Clear Timmer Register
        
        IPC3bits.T3IP = 4;          // Interrupt Priority
        IPC3bits.T3IS = 4;
        IFS0bits.T3IF = 0;          // Reset interrupt flag
        IEC0bits.T3IE = 1;          // Enable Interrupt

        T3CONbits.TON = 1;          // Enable Timmer
        
    }else if (timerRequested == 4){
        // Type B even
        T4CONbits.ON = 0;           // Stop timer
        T4CONbits.TCKPS = preScaler;    // Prescaler 7->256;6->64;5->32;4->16;3->8;2->4;1->2;0->1
        T4CONbits.T32 = 0;          // TMRX and TMRY form separate 16 bit timmer (=1: form 32 bit timmer)
        T4CONbits.TCS = 0;          // Internal Peripheral Clock
        PR4 = constantDivider;      // 16 bit period match
        TMR4 = 0;                   // Clear Timmer Register

        IPC4bits.T4IP = 5;          // Interrupt Priority
        IPC4bits.T4IS = 2;          // Interrupt Subpriority
        IFS0bits.T4IF = 0;          // Reset interrupt flag
        IEC0bits.T4IE = 1;          // Enable Interrupt

        T4CONbits.TON = 1;          // Enable Timmer
        
    }else{
        // Type B odd
        T5CONbits.ON = 0;            // Stop timer
        T5CONbits.TCKPS = preScaler;    // Prescaler 7->256;6->64;5->32;4->16;3->8;2->4;1->2;0->1
        T5CONbits.TCS = 0;          // Internal Peripheral Clock
        PR5 = constantDivider;      // 16 bit period match
        TMR5 = 0;
        
        IPC5bits.T5IP = 5;          // Interrupt Priority
        IPC5bits.T5IS = 2;          // Interrupt Subpriority
        IFS0bits.T5IF = 0;          // Reset interrupt flag
        IEC0bits.T5IE = 1;          // Enable Interrupt

        T5CONbits.TON = 1;          // Enable Timmer   
    }
}