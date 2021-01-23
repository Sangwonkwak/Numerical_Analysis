#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "nr.h"
#include "nrutil.h"
/* Matrix size */
#define NUM 11

int main() {
	long idum, N, nrot;
	float* d, ** A, ** v;
	N = NUM;
	d = vector(1, N);
	A = matrix(1, N, 1, N);
	v = matrix(1, N, 1, N);

	/* Gaussian distribution�� �̿��� A���� ���� */
	for (int i = 1; i <= N; i++) 
		for (int j = 1; j <= N; j++) {
		idum = time(NULL);
		A[i][j] = gasdev(&idum);
	}
	/* Jacobi transformation�� �̿��� eigenvalue&vector ���ϱ�*/
	jacobi(A, N, d, v, &nrot);

	/* A�� eigenvalues�� descending order�� �����ϱ� */
	eigsrt(d, v, N);

	/* ����ϱ� */
	printf("eigenvalues:\n");
	for (int i = 1; i <= N; i++) {
		printf("%2d��°: %9.6f  ", i, d[i]);
		if (i == 4 || i == 8)printf("\n");
	}
	printf("\n\neigenvector:\n");
	for (int i = 1; i <= N; i++) {
		printf("%2d��°:", i);
		for (int j = 1; j <= N; j++) {
			printf("%10.6f", v[j][i]);
			if (j == 7) printf("\n");
		}
		printf("\n\n");
	}
	
	return 0;
}