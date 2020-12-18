#include "powerControl.h"

void PID(){
    Error = (double)(set_temp - temperature_read);
    
    Error_Integral = Error_Integral + Error;
	if(Error_Integral > 50)
		Error_Integral = 50;
	else if(Error_Integral < -50)
		Error_Integral = -50;

	Error_Derivative = Error - Previous_Error;
	Previous_Error = Error;
    PID_Output = (int)((K_proportional*Error) + (K_integral*Error_Integral) + (K_derivative*Error_Derivative));
    
    if(PID_Output > 200)
		PID_Output = 200;
	else if(PID_Output < 0)
		PID_Output = 0;    
}