
/* Uniform Distribution histogram */

#include <stdio.h>
#include <time.h>
#define NRANSI
#include "nr.h"
/* interval */
#define N 100
/* sample num */
#define NPTS 100000
#define ISCAL 400
#define LLEN 50

int main(void)
{
	char words[LLEN+1];
	int i,j,k,klim,dist[N+1];
	long idum = time(NULL);
	float dd,x;
	
	for (j=0;j<=N;j++) dist[j]=0;
	for (i=1;i<=NPTS;i++) {
		x = 0.2 * N * ran1(&idum);
		j=(int)(x > 0 ? x+0.5 : x-0.5);
		++dist[j];
	}
	printf("Uniformly distributed deviate of %6d points\n",NPTS);
	printf ("%5s %10s %9s\n","x","p(x)","graph:");
	for (j=0;j<=N;j++) {
		dd=(float) dist[j]/NPTS;
		for (k=1;k<=LLEN;k++) words[k]=' ';
		klim=(int) (ISCAL*dd);
		if (klim > LLEN)  klim=LLEN;
		for (k=1;k<=klim;k++) words[k]='*';
		printf("%8.4f %8.4f  ", (j / (0.2 * N)-3), dd);
		for (k=1;k<=LLEN;k++) printf("%c",words[k]);
		printf("\n");
	}
	return 0;
}

#undef NRANSI
