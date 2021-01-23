#include <stdio.h>
#include "function.h"

void user_func(float x, float* f, float*df);//x값에 대해 bessel function J0의 값을 f에,
                                            //J0 derivative(-J1)의 값을 df에 반환하는 함수.rtnewt과 rtsafe에 쓰임
void problem_1(float x, float* f, float* df);
void problem_2(float x, float* f, float* df);
void problem_3(float x, float* f, float* df);
void problem_4(float x, float* f, float* df);


//routine을 가리키기위한 pointer to function
typedef float(*rtMethod_1)(float(*)(float), float, float, float, int*);
typedef float(*rtMethod_2)(void(*)(float, float*, float*), float, float, float, int*);

int main() {
	//root finding routine을 담을 pointer to function. argument의 구성에 따라 두 종류로 나뉨
	rtMethod_1 proper_routine;
	rtMethod_2 another;
	float xb1[100],xb2[100], root;// xb1, xb2는 Incremental search에서 해가 있다고 찾은 구간의 시작점, 끝점을 각각 저장(Index1부터 저장). root는 해를 담을 변수
	int a, b,n;//a는 routine의 iteration횟수를 저장할 변수. b는 찾을 해의 개수. n은 Incremental search에서 나눌 구간의 수
	float xacc = 1.0E-6;//Error 크기

	
	n = 20;
	b = 10;//이후 Incremental search(zbrak)을 통해 값이 변할 수 있음
	
	//Incremental search로 해가 존재하는 구간 구하기
	zbrak(bessj0,1.0, 10.0, n, xb1, xb2, &b);//[1.0,10.0]을 n개의 구간으로 나눔. b에 해가 존재하는 구간의 개수가 저장됨
	if (b == 0) {//n개로 구간을 나눠 살펴봤을때 해를 찾을 수 없는 경우
		printf("구간 개수 다시 정하시오.\n");
		return 0;
	}
	
	
	
	//Bracketing or Open method로 근사해서 root구하기
	//사용하고싶은 method에따라 "proper_routine" or "another" 이용


	for (int i = 1; i <= b; i++) {//proper_routine
		a = 0;
		proper_routine = rtmull;//rtbis, rtflsp, rtmull, rtsec 중 하나 선택
		root = proper_routine(bessj0, xb1[i], xb2[i], xacc, &a);
		printf("%d번째root:%e   //  iter_num:%d\n", i, root, a);
	}
	

	/*
	for (int i = 1; i <= b; i++) {//another
		a = 0;
		another = rtsafe;//rtnewt, rtsafe중 하나 선택
		root = another(problem_2_extend, xb1[i], xb2[i], xacc, &a);
		printf("%d번째 root:%e   //   iter_num:%d\n", i, root, a);
	}
	*/

	return 0;
}

void user_func(float x, float* f, float* df) {
	*f = bessj0(x);
	*df = -bessj1(x);//bessel function J0 = -J1을 이용
}