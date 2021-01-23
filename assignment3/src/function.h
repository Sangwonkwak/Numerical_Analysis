#ifndef __FUNCTION_H__
#define __FUNCTION_H__
//bessel function ¹× method ¼±¾ð
float bessj0(float);
float bessj1(float);
void zbrak(float(*fx)(float), float x1, float x2, int n, float xb1[], float xb2[], int* nb);
float rtbis(float(*func)(float), float x1, float x2, float xacc,int *iter_num);
float rtflsp(float(*func)(float), float x1, float x2, float xacc,int *iter_num);
float rtsafe(void(*funcd)(float,float*,float*), float x1, float x2, float xacc, int* iter_num);
float rtnewt(void(*funcd)(float, float*, float*), float x1, float x2, float xacc, int *iter_num);
float rtsec(float(*func)(float), float x1, float x2, float xacc, int* iter_num);
float rtmull(float(*func)(float), float x1, float x2, float xacc, int *iter_num);

float fx_1(float x);
float fx_2(float x);
float fx_3(float x);
float fx_4(float x);
void problem_1(float x, float* f, float* df);
void problem_2(float x, float* f, float* df);
void problem_3(float x, float* f, float* df);
void problem_4(float x, float* f, float* df);
float ux_derivative_2(float x);
void problem_2_extend(float x, float* f, float* df);
#endif