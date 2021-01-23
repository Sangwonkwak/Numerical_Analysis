#include <stdio.h>
#include <math.h>
#define JMAX 20

float rtnewt(void (*funcd)(float,float*,float*),float x1,float x2,float xacc,int *iter_num)
{
	int j;
	float df,dx,f,rtn;

	rtn=0.5*(x1+x2);
	for (j=1;j<=JMAX;j++) {
		(*iter_num)++;
		(*funcd)(rtn,&f,&df);
		dx=f/df;
		rtn -= dx;
		if ((x1 - rtn)*(rtn - x2) < 0.0) {
			printf("Jumped out of brackets in rtnewt  /");
			return 0.0;
		}
		if (fabs(dx) < xacc) return rtn;
	}
	printf("Maximum number of iterations exceeded in rtnewt  /");
	return 0.0;
}
#undef JMAX
