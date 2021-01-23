#include <stdio.h>
#include <math.h>
#define JMAX 40

float rtbis(float (*func)(float),float x1,float x2,float xacc,int* iter_num)
{
	int j;
	float dx,f,fmid,xmid,rtb;

	f=(*func)(x1);
	fmid=(*func)(x2);
	if (f*fmid >= 0.0) {
		printf("Root must be bracketed for bisection in rtbis  /");
		return 0.0;
	}
	rtb = f < 0.0 ? (dx=x2-x1,x1) : (dx=x1-x2,x2);
	for (j=1;j<=JMAX;j++) {
		(*iter_num)++;
		fmid=(*func)(xmid=rtb+(dx *= 0.5));
		if (fmid <= 0.0) rtb=xmid;
		if (fabs(dx) < xacc || fmid == 0.0) return rtb;
	}
	printf("Too many bisections in rtbis  /");
	return 0.0;
}
#undef JMAX
