#include "../CKCommon/ConfigBits/config_bits.h" 
#include "timers_set.h"
#include "adc_set.h"
#include "thermocouple.h"
#include "powerControl.h"
#include "uart.h"
#include "projeto0.h"
#include "config_bits.h"
#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include <sys/attribs.h>
#include <stdio.h>
#include <stdlib.h>

float tmpCalculation1;
double res1, res2, dutycycle;
unsigned char a;
int b;
int print = 9;
int set_temp =0;
char temp[10];
double Error = 0;
double Error_Integral = 0;
double Error_Derivative = 0;
int PID_Output;
double K_proportional =7.5;
double K_integral = 2.48;
double K_derivative = 0.016;
double Previous_Error = 0;
int temperature_read;
double voltageThermocouple;
double THETA;
double LMTHETA;
double temperature;
int nints=0;
int reset = 1;
int duty_cycle;
int nints_on;
int nints_off;

int main(){
    b=0;   
   ///// UART /////
   //void init_uart() // Redirect stdin/stdout/stderr to UART1 
    if(UartInit(PBCLOCK, 9600) != UART_SUCCESS) {
        PORTAbits.RA3 = 1;            // If Led active error initializing UART
        while(1);
    }
    __XC_UART = 1;                     // Redirect stdin/stdout/stderr to UART1/ 
       
   ///// TIMERS /////
   //scale();                         // This timmer(3) is used for the input and depends of freq
   setTimer(3, 7, 65000);             // timmer (3) used for input (2.48Hz)
   setTimer(2, 7, 32500);             // timmer (2) used for output (5Hz)
   //IEC0bits.T2IE = 0;               // Disable Interrupt

   /////// CONFIGURE ADC MODULE ///////
   set_adc(1);                        // 0: normal mode AN0; 1: Scan Mode AN0 and AN1
    
   configuration();
   // ADC INTERRUPT //
   // ENABLE INTERRUPTS
    INTCONSET = _INTCON_MVEC_MASK;    // Set Interrupt Controller for multi-vector mode
    __builtin_enable_interrupts();    // Enable Interrupt Exceptions
                                      // set the CP0 status IE bit high to turn on interrupts globall
    
    while (1) {
        
        if(reset == 1){
            printf("set temperature \n\r");
            set();
            printf("temperature set to: %d\n\r", set_temp);
            nints = 0;
            reset = 0;
        }
       
        while(nints < nints_on ){
            PORTEbits.RE2 = 1;
        }
        nints = 0;
        
        while(nints < nints_off){
          PORTEbits.RE2 = 0;
        }
        nints = 0;
    }
    return (EXIT_SUCCESS);
}

void __ISR(12, IPL4AUTO) termoRead(void){
    
    IFS1bits.AD1IF = 0;                 // Reset interrupt flag
    AD1CON1bits.ASAM = 1;               // Start conversion (AUTO-SAMPLE MODE))
        // if AD1CON1bits.DONE == 1 -> conversion is done  
    while (IFS1bits.AD1IF == 0);    // Wait for EOC 
        // Convert to 0..3.3V 
         res1 = (ADC1BUF0 * 3.3)/1023;
         res2 = (ADC1BUF1 * 3.3)/1023;
        
         voltageThermocouple = removeGain(res1, 270);
         THETA = NIST_K_inv_poly(voltageThermocouple *1000);
         LMTHETA = coldJunctionTemp (res2);
         temperature = compensation( THETA, LMTHETA);
         temperature_read = (int) temperature;
         PID();
         nints_on = PID_Output/10;
         nints_off = 20 - nints_on;
         IFS0bits.T3IF = 0;
}

void __ISR(8, IPL3AUTO) zeroCrossDetection(void){
    
    if(reset == 0){
         printf("Temperature set to : %d :: Temperature read: %d ::cycles on %d\n\r",set_temp, temperature_read, nints_on);
         //printf("cicles on: %d\n\r",nints_on);
    }
    
    if(temperature_read > set_temp){
         duty_cycle = (temperature_read - set_temp)*5;
            if(duty_cycle <0 ){
                duty_cycle = 0;
            }
            if(duty_cycle > 100){
                duty_cycle = 100;
            }   
    }
    
    else{
        duty_cycle = 0;
    }
        tmpCalculation1 = ((32500 + 1)* duty_cycle) / 100;
        OC1RS = (int)tmpCalculation1;
        IFS0bits.T2IF = 0;
}

void __ISR (_EXTERNAL_1_VECTOR, IPL2AUTO) ExtInt1ISR(void)
{
    nints = nints + 1;
    IFS0bits.INT1IF = 0; // Reset interrupt flag
}

void __ISR (_EXTERNAL_2_VECTOR, IPL1AUTO) ExtInt2ISR(void)
{
    reset = 1; 
    IFS0bits.INT2IF = 0; // Reset interrupt flag
}
