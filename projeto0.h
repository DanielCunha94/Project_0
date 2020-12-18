#ifndef PROJETO0_H
#define PROJETO0_H

#include "../CKCommon/ConfigBits/config_bits.h" 
#include "timers_set.h"
#include "adc_set.h"
#include "thermocouple.h"
#include "powerControl.h"
#include "uart.h"
#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include <sys/attribs.h>
#include <stdio.h>
#include <stdlib.h>

#define SYSCLK  80000000L // System clock frequency, in Hz
#define PBCLOCK 40000000L 

#endif