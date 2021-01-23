#include <math.h>
#include <stdio.h>
#define MAXIT 100

int In_Bound(float a, float b, float x) {//���� [a,b]�� x�� �����ϸ� 1 ��ȯ �ƴϸ� 0
	return x > a && x < b ? 1 : 0;
}

float rtmull(float(*func)(float), float x1, float x2, float xacc, int *iter_num) {
	float p0, p1, p2, fp0, fp1, fp2,a,b,c,d,error,rtn,dd;//���Ҽ����� �ƴ� �Ǳٸ� ã���Ƿ� float������ �����ص� ������
	p0 = x1;
	p1 = x2;
	p2 = (x1 + x2) / 2;
	
	for (int i = 1; i < MAXIT; i++) {
		(*iter_num)++;
		//�� ���� �Լ���
		fp0 = func(p0);
		fp1 = func(p1);
		fp2 = func(p2);

		//������ �̿��� a,b,c���� ����
		a = ((p1 - p2)*(fp0 - fp2) - (p0 - p2)*(fp1 - fp2))
			/ ((p0 - p2)*(p1 - p2)*(p0 - p1));
		b = ((p0 - p2)*(p0 - p2)*(fp1 - fp2) - (p1 - p2)*(p1 - p2)*(fp0 - fp2))
			/ ((p0 - p2)*(p1 - p2)*(p0 - p1));
		c = fp2;
		//�� �� ��error�� �� �������� ����. 
		if ((b + sqrtf(b*b - 4 * a*c)) - (b - sqrtf(b*b - 4 * a*c)) > 0.0) {
			d = b + sqrtf(b*b - 4 * a*c);
			dd = b - sqrtf(b*b - 4 * a*c);
		}
		else {
			d = b - sqrtf(b*b - 4 * a*c);
			dd = b + sqrtf(b*b - 4 * a*c);
		}

		error = -1 * 2 * c / d;
		rtn = p2 + error;
		//���õ� ���� [x1,x2]�� �������������� �ٸ����� ����
		if (In_Bound(x1, x2, rtn) != 1) {
			error = -1 * 2 * c / dd;
			rtn = p2 + error;
		}
		if (In_Bound(x1, x2, rtn) != 1) {//�� �� ��� ������ ��� ���
			printf("Out of Bound!  /");
			return 0.0;
		}
		if (fabs(error) < xacc) return rtn;//Error < xacc�̸� �ٻ��� rtn�� ��ȯ
		p0 = p1;
		p1 = p2;
		p2 = rtn;
	}
	printf("OVER MAXIT\n");//�ִ� iteratinȽ���� MAXIT�� �ʰ�
	return 0.0;
}
#undef MAXIT