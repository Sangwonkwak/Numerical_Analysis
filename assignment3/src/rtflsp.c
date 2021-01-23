#include <stdio.h>
#include <math.h>
#define MAXIT 30

float rtflsp(float (*func)(float),float x1,float x2,float xacc,int* iter_num)

{
	
	int j;
	float fl,fh,xl,xh,swap,dx,del,f,rtf;

	fl=(*func)(x1);
	fh=(*func)(x2);
	if (fl*fh > 0.0) {
		printf("Root must be bracketed in rtflsp  /");
		return 0.0;
	}
	if (fl < 0.0) {
		xl=x1;
		xh=x2;
	} else {
		xl=x2;
		xh=x1;
		swap=fl;
		fl=fh;
		fh=swap;
	}
	dx=xh-xl;
	for (j=1;j<=MAXIT;j++) {
		(*iter_num)++;
		rtf=xl+dx*fl/(fl-fh);// one of root sequence
		f=(*func)(rtf);
		if (f < 0.0) {
			del=xl-rtf;
			xl=rtf;
			fl=f;
		} else {
			del=xh-rtf;
			xh=rtf;
			fh=f;
		}
		dx=xh-xl;
		if (fabs(del) < xacc || f == 0.0) return rtf;
	}
	printf("Maximum number of iterations exceeded in rtflsp  /");
	return 0.0;
}
#undef MAXIT
