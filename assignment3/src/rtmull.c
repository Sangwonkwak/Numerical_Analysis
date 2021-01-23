#include <math.h>
#include <stdio.h>
#define MAXIT 100

int In_Bound(float a, float b, float x) {//구간 [a,b]에 x가 존재하면 1 반환 아니면 0
	return x > a && x < b ? 1 : 0;
}

float rtmull(float(*func)(float), float x1, float x2, float xacc, int *iter_num) {
	float p0, p1, p2, fp0, fp1, fp2,a,b,c,d,error,rtn,dd;//복소수근이 아닌 실근만 찾으므로 float형으로 선언해도 무방함
	p0 = x1;
	p1 = x2;
	p2 = (x1 + x2) / 2;
	
	for (int i = 1; i < MAXIT; i++) {
		(*iter_num)++;
		//세 점의 함수값
		fp0 = func(p0);
		fp1 = func(p1);
		fp2 = func(p2);

		//공식을 이용해 a,b,c값을 구함
		a = ((p1 - p2)*(fp0 - fp2) - (p0 - p2)*(fp1 - fp2))
			/ ((p0 - p2)*(p1 - p2)*(p0 - p1));
		b = ((p0 - p2)*(p0 - p2)*(fp1 - fp2) - (p1 - p2)*(p1 - p2)*(fp0 - fp2))
			/ ((p0 - p2)*(p1 - p2)*(p0 - p1));
		c = fp2;
		//두 근 중error가 더 작은것을 선택. 
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
		//선택된 근이 [x1,x2]에 존재하지않으면 다른근을 선택
		if (In_Bound(x1, x2, rtn) != 1) {
			error = -1 * 2 * c / dd;
			rtn = p2 + error;
		}
		if (In_Bound(x1, x2, rtn) != 1) {//두 근 모두 범위를 벗어난 경우
			printf("Out of Bound!  /");
			return 0.0;
		}
		if (fabs(error) < xacc) return rtn;//Error < xacc이면 근사해 rtn을 반환
		p0 = p1;
		p1 = p2;
		p2 = rtn;
	}
	printf("OVER MAXIT\n");//최대 iteratin횟수인 MAXIT을 초과
	return 0.0;
}
#undef MAXIT