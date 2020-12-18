#include "thermocouple.h"

double  NIST_K_d[] = {
        0.000000E+00,
        2.508355E+01,
        7.860106E-02,
        -2.503131E-01,
        8.315270E-02,
        -1.228034E-02,
        9.804036E-04,
        -4.413030E-05,
        1.057734E-06,
        -1.052755E-08
};

/* Order of NIST polynomial */
const int count=10;


/*
 * Computes temperature by a polynomial
 */
double NIST_K_inv_poly(double voltage)
{
  double Theta=0;
  size_t i; 
  
  for (i = 0; i < count; i++) {
    Theta +=  NIST_K_d[i]*pow(voltage,i);
  }

  return Theta;

}

double compensation(double tempThermo, double tempAmb)
{

    double temperature;
    
    temperature = tempThermo + tempAmb;
    
    return temperature;

}

double coldJunctionTemp (double voltage){
    double temp = voltage/0.01;
    return temp-273.15;
}


double removeGain(double voltage, double gain){
    double voltage_termocouple;
    voltage_termocouple = voltage/gain;
    
    return voltage_termocouple;
    
}