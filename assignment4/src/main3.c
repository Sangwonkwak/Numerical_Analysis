#include <stdio.h>
#include "function.h"

//routine을 가리키기위한 pointer to function
typedef float(*rtMethod_1)(float(*)(float), float, float, float, int*);
typedef float(*rtMethod_2)(void(*)(float, float*, float*), float, float, float, int*);

int main() {
	//root finding routine을 담을 pointer to function. argument의 구성에 따라 두 종류로 나뉨
	rtMethod_1 proper_routine[4];
	rtMethod_2 another[2];
	float root[6];// root는 해를 담을 변수
	int a[6] = { 0, }, i;//a는 routine의 iteration횟수를 저장할 변수
	float xacc = 1.0E-4;//Relative approximate Error(%) 크기
	
	//함수포인터에 함수 담기
	proper_routine[0] = rtbis; proper_routine[1] = rtflsp; proper_routine[2] = rtsec; proper_routine[3] = rtmull;
	another[0] = rtnewt; another[1] = rtsafe;
	
	//root와 iteration_num 구하기
	for (i = 0; i < 4; i++) root[i] = proper_routine[i](E_C, 0, 400.0, xacc, &a[i]);
	for (; i < 6; i++) root[i] = another[i-4](problem_EC, 0.0, 400.0, xacc, &a[i]);

	//결과출력
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
