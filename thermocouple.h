#ifndef TERMO_H    
#define TERMO_H
#include <math.h>
#include <stddef.h>

double NIST_K_d[];
double NIST_K_inv_poly(double voltage);
double compensation(double tempThermo, double tempAmb);
double coldJunctionTemp (double voltage);
double removeGain(double voltage, double gain);


#endif
