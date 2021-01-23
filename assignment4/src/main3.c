#include <stdio.h>
#include "function.h"

//routine�� ����Ű������ pointer to function
typedef float(*rtMethod_1)(float(*)(float), float, float, float, int*);
typedef float(*rtMethod_2)(void(*)(float, float*, float*), float, float, float, int*);

int main() {
	//root finding routine�� ���� pointer to function. argument�� ������ ���� �� ������ ����
	rtMethod_1 proper_routine[4];
	rtMethod_2 another[2];
	float root[6];// root�� �ظ� ���� ����
	int a[6] = { 0, }, i;//a�� routine�� iterationȽ���� ������ ����
	float xacc = 1.0E-4;//Relative approximate Error(%) ũ��
	
	//�Լ������Ϳ� �Լ� ���
	proper_routine[0] = rtbis; proper_routine[1] = rtflsp; proper_routine[2] = rtsec; proper_routine[3] = rtmull;
	another[0] = rtnewt; another[1] = rtsafe;
	
	//root�� iteration_num ���ϱ�
	for (i = 0; i < 4; i++) root[i] = proper_routine[i](E_C, 0, 400.0, xacc, &a[i]);
	for (; i < 6; i++) root[i] = another[i-4](problem_EC, 0.0, 400.0, xacc, &a[i]);

	//������
	printf("Relative approximate error : %f\n", xacc);
	printf("<Bracketing Method>\n");
	printf("[Bisection]   root:%e  iteration:%d\n", root[0], a[0]);
	printf("[False-position]   root:%e  iteration:%d\n", root[1], a[1]);

	printf("\n\n\n<Open method>\n");
	printf("[Secant]   root:%e  iteration:%d\n", root[2], a[2]);
	printf("[Muller]   root:%e  iteration:%d\n", root[3], a[3]);
	printf("[Newton-Raphson]   root:%e  iteration:%d\n", root[4], a[4]);
	printf("[Fail-safe]   root:%e  iteration:%d\n", root[5], a[5]);
	
	return 0;
}
