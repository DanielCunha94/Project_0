#ifndef TIMERS_SET_H    /* Guard against multiple inclusion */
#define TIMERS_SET_H

#include <stdint.h>
#include <xc.h>
/*Functions Prototypes*/
void setTimer(uint8_t timerRequested, uint16_t preScaler, uint32_t constantDivider);

#endif