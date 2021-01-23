//
//Homework#4 problem solving
//

#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>

float E_C(float R) {
	return expf(-0.005*R)*cosf(sqrtf(2000 - 0.01*R*R)*0.05) - 0.01;
}
void problem_EC(float R, float* f, float* df) {
	*f = E_C(R);
	float A = expf(-0.005*R), B = 0.05*sqrtf(2000 - 0.01*R*R);
	*df = -0.005*(*f) + 0.01*R*B*A*sinf(B) / (2000 - 0.01*R*R);
}

float problem8_32(float x) {
	return 4 * M_PI*8.85 * (1.0E-12)*(x*x + 0.9*0.9)*sqrtf(x*x + 0.9*0.9) - (2 * (1.0E-5))*(2 * (1.0E-5))*x;
}

float problem8_36(float T) {
	return ((((1.9520 * (1.0E-14))*T - 9.5838 * (1.0E-11))*T + 9.7215 * (1.0E-8))*T + 1.671 * (1.0E-4))*T + 0.99403 - 1.2;
}