#define _USE_MATH_DEFINES
#include <math.h>

//fx_N�� N��° ������ f(x)�� �ǹ�
//problem_N�� x�������� f(x)�� ���� f�� ��ȯ, f(x) derivative�� ���� df�� ��ȯ�ϴ� �Լ�


float fx_1(float x) {
	return 10.0*expf(-1.0 * x)*sinf(2.0 * M_PI*x) - 2.0;
}
void problem_1(float x, float* f, float* df) {
	*f = fx_1(x);
	*df = 10.0 * expf(-1.0 * x)*(-1.0*sinf(2.0 * M_PI*x) + 2.0 * M_PI*x*cosf(2.0 * M_PI*x));
}

//problem2�� �߱��� ���°�쿩�� �Լ�2���� �߰���
float fx_2(float x) {
	return  x * x - 2.0 * x*expf(-1.0 * x) + expf(-2.0 * x);
}
void problem_2(float x, float* f, float* df) {
	*f = fx_2(x);
	*df = 2.0 * (1.0 + expf(-1.0 * x))*(x - expf(-1.0 * x));
}
float ux_derivative_2(float x) {//u(x) = f(x)/(f(x) derivative)�϶�, �� �Լ��� u(x) derivative�� �ǹ�
	return 0.5*(1 + expf(-1 * x)*(x - 1 * expf(-1 * x)) / ((1 + expf(-1 * x))*(1 + expf(-1 * x))));
}
void problem_2_extend(float x, float* f, float* df) {//df�� f(x) derivative��� u(x) derivative ���� ��ȯ
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