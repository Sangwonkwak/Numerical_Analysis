#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NRANSI
#include "nr.h"
#include "nrutil.h"

void A_cal(float** A, float** be, int N);
void b_cal(float** be, float** af, float* b1, float* b2, int N);

int main() {
	FILE* file;
	/* N은 데이터 개수, A 및 b1,b2는 보고서 참조, before는 x,y 페어저장, after는 x',y' 페어저장 */
	int N, * indx;
	float** A, * b1, *b2, ** before, ** after, p;
	char* file_name[3];

	indx = ivector(1, 3);
	A = matrix(1, 3, 1, 3);
	before = matrix(1, 2, 1, 150);
	after = matrix(1, 2, 1, 150);
	b1 = vector(1, 3);
	b2 = vector(1, 3);
	//파일 이름 저장
	for (int i = 0; i < 3; i++) {
		file_name[i] = (char*)malloc(sizeof(char) * 10);
		sprintf(file_name[i], "fitdata%d.dat", i + 1);
	}
	
	for (int k = 0; k < 3; k++) {
		file = fopen(file_name[k], "r");

		/* 파일 읽기 */
		N = 0;
		for (int i = 1;;i++) {
			fscanf(file, "%f %f %f %f", &before[1][i], &before[2][i], &after[1][i], &after[2][i]);
			N++;
			if (feof(file)) {
				N -= 1;
				break;
			}
		}
		/* A,b1,b2 전부 0으로 초기화 */
		for (int i = 1; i <= 3; i++) memset(A[i], 0, sizeof(A[i]) * 3);
		memset(b1, 0, sizeof(b1) * 3);
		memset(b2, 0, sizeof(b2) * 3);

		/* A와 b구하기 */
		A_cal(A, before, N);
		b_cal(before, after, b1, b2, N);
		
		/* ludcmp및 lubksb으로 set of a(a1,a2,a3,a4,a5,a6) 구하기 */
		ludcmp(A, 3, indx, &p);
		lubksb(A, 3, indx, b1);
		lubksb(A, 3, indx, b2);
		
		/* 결과출력 */
		printf("------%s------\nSet of a:\n", file_name[k]);
		for (int i = 1; i <= 3; i++) printf("a%d : %10.5f\n", i, b1[i]);
		for (int j = 1; j <= 3; j++) printf("a%d : %10.5f\n", j + 3, b2[j]);
		printf("\n\n");
		fclose(file);
	}
	/*for (int i = 0; i < 3; i++)  free(file_name[i]);
	free_ivector(indx,1,3);
	free_vector(b1,1,3);
	free_vector(b2,1,3);
	free_matrix(A,1,3,1,3);
	free_matrix(before,1,2,1,150);
	free_matrix(after,1,2,1,150);*/ 
	return 0;
}

void A_cal(float** A, float** be, int N) {
	int x, y;
	for (int i = 1; i <= N; i++) {
		x = be[1][i], y = be[2][i];
		A[1][1] += x * x;
		A[1][2] += x * y;
		A[1][3] += x;
		A[2][1] += x * y;
		A[2][2] += y * y;
		A[2][3] += y;
		A[3][1] += x;
		A[3][2] += y;
		A[3][3] += 1.0;
	}
}

void b_cal(float** be, float** af, float* b1, float* b2, int N) {
	int x, y, x_, y_;
	for (int i = 1; i <= N; i++) {
		x = be[1][i], y = be[2][i], x_ = af[1][i], y_ = af[2][i];
		b1[1] += x_ * x;
		b1[2] += x_ * y;
		b1[3] += x_;
		b2[1] += y_ * x;
		b2[2] += y_ * y;
		b2[3] += y_;
	}
}