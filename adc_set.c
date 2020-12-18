#include"adc_set.h"
#include <stdint.h>
#include <xc.h>
#include <sys/attribs.h>
#include <stdlib.h>


void set_adc(uint8_t operation_mode){
        
    // Disable JTAG interface as it uses a few ADC ports
    DDPCONbits.JTAGEN = 0;

    AD1CON1bits.FORM = 0; // Integer 16 bit output format
    AD1CON1bits.SSRC = 7; // = 7: Internal counter ends sampling and starts conversion (AUTO-CONVERT))
                          // = 0: Clearing SAMP bit ends sampling and starts conversion
    AD1CON1bits.CLRASAM = 1; //=1: Stop conversion when 1st A/D converter interrupt is generated and clears ASAM bit automatically
                             //=0: Normal operation, buffer contents will be overwritten by the next conversion sequence
    //if (AD1CON1bits.DONE == 1); //A/D conversion is done 
    
    AD1CON2bits.VCFG = 0;   // VR+=AVdd; VR-=AVss
    AD1CON2bits.OFFCAL = 0; // The inputs are controlled by AD1CHS or AD1CSSL
    AD1CON2bits.BUFM = 0;   // ADRES split into 2x8 word buffers
    //AD1CON2bits.BUFS == 1; // STATUS bit only if BUFM=1 -> BUFS==1: filling buffer 0x8 to 0xF BUFS ==0:0x0 to 0x7 
    AD1CON2bits.ALTS = 0;   // Always use MUX A 
    
    AD1CON3bits.ADRC = 1;   // ADC uses internal RC clock
    AD1CON3bits.SAMC = 16;  // Sample time is 16TAD ( TAD = 100ns)
    AD1CON3bits.ADCS = 0;   // TAD = 2*PBCLOCK*(ADCS <7:0> +1)
    
    AD1CHSbits.CH0NA = 0;  // Negative input bit is VR- (=1: USE AN1 as negative for UNIPOLAR DIFFERENTIAL mode)
    
    if (operation_mode == 0){
        AD1CON2bits.CSCNA = 0;  // DISABLE SCAN inputs for CH0+ SHA input for mux A
        // Set AN0 as input
        AD1CON2bits.SMPI = 0;   // Number (+1) of consecutive samples/conversions per interrupt BUF <F:0>

        AD1CHSbits.CH0SA0 = 0;  // Positive input bit is AN0
        AD1PCFGbits.PCFG0 = 0; // Analog mode input pin for AN0
        TRISBbits.TRISB0 = 1; // Set AN0 to input mode        
        
    }else{
        //// SCAN MODE ////
        // When scan mode is enabled the positive input of MUX A is controlled by the content of AD1CSSL register
        // When Scan mode in enabled,CH0SA bits are ignored
        AD1CON2bits.SMPI = 1;   // Number (+1) of consecutive samples/conversions per interrupt BUF <F:0>
        AD1CON2bits.CSCNA = 1;   // ENABLE SCAN inputs for CH0+ SHA input for mux A
        //AD1CON2bits.ALTS = 1;    // Use MUX A and MUX B ?????????
        // Set AN0 and AN1 and AN2 as inputs
        AD1CSSLbits.CSSL0 = 1;   // ADC input pin scan selection bit: =1: select AN0 to input Scan
        AD1CHSbits.CH0SA0 = 0;  // Positive input bit AN0
        AD1PCFGbits.PCFG0 = 0; // Analog mode input pin for AN0
        TRISBbits.TRISB0 = 1; // Set AN0 to input mode
        
        AD1CSSLbits.CSSL1 = 1;   // ADC input pin scan selection bit: =1: select AN1 to input Scan
        AD1CHSbits.CH0SA1 = 0;  // Positive input bit AN1
        AD1PCFGbits.PCFG1 = 0; // Analog mode input pin for AN1
        TRISBbits.TRISB1 = 1; // Set AN1 to input mode
    }
    
    // Enable module
    AD1CON1bits.ON = 1; // Enable A/D module (This must be the ***last instruction of configuration phase***)     
}