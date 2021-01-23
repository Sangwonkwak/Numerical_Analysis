#include <stdio.h>
#include "function.h"

void user_func(float x, float* f, float*df);//x���� ���� bessel function J0�� ���� f��,
                                            //J0 derivative(-J1)�� ���� df�� ��ȯ�ϴ� �Լ�.rtnewt�� rtsafe�� ����
void problem_1(float x, float* f, float* df);
void problem_2(float x, float* f, float* df);
void problem_3(float x, float* f, float* df);
void problem_4(float x, float* f, float* df);


//routine�� ����Ű������ pointer to function
typedef float(*rtMethod_1)(float(*)(float), float, float, float, int*);
typedef float(*rtMethod_2)(void(*)(float, float*, float*), float, float, float, int*);

int main() {
	//root finding routine�� ���� pointer to function. argument�� ������ ���� �� ������ ����
	rtMethod_1 proper_routine;
	rtMethod_2 another;
	float xb1[100],xb2[100], root;// xb1, xb2�� Incremental search���� �ذ� �ִٰ� ã�� ������ ������, ������ ���� ����(Index1���� ����). root�� �ظ� ���� ����
	int a, b,n;//a�� routine�� iterationȽ���� ������ ����. b�� ã�� ���� ����. n�� Incremental search���� ���� ������ ��
	float xacc = 1.0E-6;//Error ũ��

	
	n = 20;
	b = 10;//���� Incremental search(zbrak)�� ���� ���� ���� �� ����
	
	//Incremental search�� �ذ� �����ϴ� ���� ���ϱ�
	zbrak(bessj0,1.0, 10.0, n, xb1, xb2, &b);//[1.0,10.0]�� n���� �������� ����. b�� �ذ� �����ϴ� ������ ������ �����
	if (b == 0) {//n���� ������ ���� ��������� �ظ� ã�� �� ���� ���
		printf("���� ���� �ٽ� ���Ͻÿ�.\n");
		return 0;
	}
	
	
	
	//Bracketing or Open method�� �ٻ��ؼ� root���ϱ�
	//����ϰ���� method������ "proper_routine" or "another" �̿�


	for (int i = 1; i <= b; i++) {//proper_routine
		a = 0;
		proper_routine = rtmull;//rtbis, rtflsp, rtmull, rtsec �� �ϳ� ����
		root = proper_routine(bessj0, xb1[i], xb2[i], xacc, &a);
		printf("%d��°root:%e   //  iter_num:%d\n", i, root, a);
	}
	

	/*
	for (int i = 1; i <= b; i++) {//another
		a = 0;
		another = rtsafe;//rtnewt, rtsafe�� �ϳ� ����
		root = another(problem_2_extend, xb1[i], xb2[i], xacc, &a);
		printf("%d��° root:%e   //   iter_num:%d\n", i, root, a);
	}
	*/

	return 0;
}

void user_func(float x, float* f, float* df) {
	*f = bessj0(x);
	*df = -bessj1(x);//bessel function J0 = -J1�� �̿�
}