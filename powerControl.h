#ifndef POWERCONTROL
#define POWERCONTROL

#include <stdint.h>
#include <xc.h>
extern double Error;
extern double Error_Integral;
extern double Error_Derivative;
extern int PID_Output;
extern double K_proportional;
extern double K_integral;
extern double K_derivative;
extern int temperature_read;
extern int set_temp;
extern double Previous_Error;

void PID();

#endif