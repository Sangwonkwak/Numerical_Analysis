
/* Driver for routine svbksb, which calls routine svdcmp */
#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#define NRANSI
#include "nr.h"
#include "nrutil.h"

#define NP 20
#define MP 20
#define MAXSTR 80

int main(void)
{
	int k,l,m,n;
	float wmax,wmin,*w,*x,*b,*c;
	float **a,**u,**v;
	
	FILE *fp;
	char file_name[3][20] = { {"lineq1.dat"},{"lineq2.dat"},{"lineq3.dat"} };

	w=vector(1,NP);
	x=vector(1,NP);
	b=vector(1, NP);
	c=vector(1,NP);
	a=matrix(1,NP,1,NP);
	u=matrix(1,NP,1,NP);
	v=matrix(1,NP,1,NP);

	for (int i = 0; i < 3; i++){
		if ((fp = fopen(file_name[i], "r")) == NULL) nrerror("Data file not found\n");
		printf("-------%s-------\n", file_name[i]);
		fscanf(fp,"%d %d ",&n,&m);
		for (k=1;k<=n;k++) for (l=1;l<=n;l++) fscanf(fp,"%f ",&a[k][l]);
		for (k=1;k<=n;k++) fscanf(fp,"%f ",&b[k]);
		
		/* copy a into u */
		for (k=1;k<=n;k++)
			for (l=1;l<=n;l++) u[k][l]=a[k][l];
		/* decompose matrix a */
	
		svdcmp(u,n,n,w,v);
		/* find maximum singular value */
		wmax=0.0;
		for (k=1;k<=n;k++)
			if (w[k] > wmax) wmax=w[k];
		/* define "small" */
		wmin=wmax*(1.0e-6);
		/* zero the "small" singular values */
		for (k=1;k<=n;k++)
			if (w[k] < wmin) w[k]=0.0;
		/* backsubstitute for each right-hand side vector */
		svbksb(u, w, v, n, n, b, x);
		printf(" solution vector is:\n");
		for (k = 1; k <= n; k++) printf("%12.6f", x[k]);
		printf("\n\n");
		fclose(fp);
	}
	
	free_matrix(v,1,NP,1,NP);
	free_matrix(u,1,NP,1,NP);
	free_matrix(a,1,NP,1,NP);
	free_vector(b, 1, NP);
	free_vector(c,1,NP);
	free_vector(x,1,NP);
	free_vector(w,1,NP);
	return 0;
}
#undef NRANSI
