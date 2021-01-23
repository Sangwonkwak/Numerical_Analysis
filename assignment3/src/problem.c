#define _USE_MATH_DEFINES
#include <math.h>

//fx_N은 N번째 문제의 f(x)를 의미
//problem_N은 x값에대해 f(x)의 값을 f에 반환, f(x) derivative의 값을 df에 반환하는 함수


float fx_1(float x) {
	return 10.0*expf(-1.0 * x)*sinf(2.0 * M_PI*x) - 2.0;
}
void problem_1(float x, float* f, float* df) {
	*f = fx_1(x);
	*df = 10.0 * expf(-1.0 * x)*(-1.0*sinf(2.0 * M_PI*x) + 2.0 * M_PI*x*cosf(2.0 * M_PI*x));
}

//problem2는 중근을 갖는경우여서 함수2개를 추가함
float fx_2(float x) {
	return  x * x - 2.0 * x*expf(-1.0 * x) + expf(-2.0 * x);
}
void problem_2(float x, float* f, float* df) {
	*f = fx_2(x);
	*df = 2.0 * (1.0 + expf(-1.0 * x))*(x - expf(-1.0 * x));
}
float ux_derivative_2(float x) {//u(x) = f(x)/(f(x) derivative)일때, 이 함수는 u(x) derivative를 의미
	return 0.5*(1 + expf(-1 * x)*(x - 1 * expf(-1 * x)) / ((1 + expf(-1 * x))*(1 + expf(-1 * x))));
}
void problem_2_extend(float x, float* f, float* df) {//df에 f(x) derivative대신 u(x) derivative 값을 반환
	*f = fx_2(x);
	*df = ux_derivative_2(x);
}


float fx_3(float x) {
	return cosf(x + sqrtf(2.0)) + x * (x / 2.0 + sqrtf(2.0));
}
void problem_3(float x, float *f, float* df) {
	*f = fx_3(x);
	*df = -1.0 * sinf(x + sqrtf(2.0)) + x + sqrtf(2.0);
}


float fx_4(float x) {
	return expf(-2.0 * M_PI*x) + sinf(2.0 * M_PI*x) + cos(2.0 * M_PI*x);
}
void problem_4(float x, float* f, float* df) {
	*f = fx_4(x);
	*df = 2.0 * M_PI*(cosf(2.0 * M_PI*x) - sinf(2.0 * M_PI*x) - expf(-1.0 * 2.0 * M_PI*x));
}