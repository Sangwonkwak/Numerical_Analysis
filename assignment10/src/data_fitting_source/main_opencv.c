#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "nr.h"
#include "nrutil.h"


typedef struct {
	float x;
	float y;
}Point2f;

Point2f* Left, * Right;

int main() {
	FILE* file;
	//H는 hessian matrix, k는 gredient, a는 현재 set of a
	float** H, * k, * a, r, d, before, after;
	int* indx, N;
	char file_name[30];
	indx = ivector(1, 8);
	a = vector(1, 8);
	k = vector(1, 8);
	H = matrix(1, 8, 1, 8);

	//test.txt에서 (x,y,x',y') data 읽기
	sprintf(file_name, "test_bad.txt");
	file = fopen(file_name, "rt");
	fscanf(file, "%d", &N);
	Left = (Point2f*)malloc(sizeof(Point2f) * N);
	Right = (Point2f*)malloc(sizeof(Point2f) * N);
	for (int i = 0; i < N; i++)
		fscanf(file, "%f %f %f %f", &Left[i].x, &Left[i].y, &Right[i].x, &Right[i].y);

	//Levenberg-Marquardt method

	//initial guess a= (1.0, ...)T & initial r set
	for (int i = 0; i < 9; i++) {
		a[i] = 1.0;
		k[i] = 0.0;
	}
	r = 0.001;
	float x, y, x_, y_;
	while (1) {
		//gradient 구하기
		for (int i = 0; i < N; i++) {
			float C, D, E;
			x = Left[i].x, y = Left[i].y, x_ = Right[i].x, y_ = Right[i].y;
			C = (a[1] * x + a[2] * y + a[3]) / (a[7] * x + a[8] * y + 1);
			D = (a[4] * x + a[5] * y + a[6]) / (a[7] * x + a[8] * y + 1);
			E = 1.0 / (a[7] * x + a[8] * y + 1.0);
			k[1] += -2.0 * (x_ - C) * x * E; k[2] += -2.0 * (x_ - C) * y * E; k[3] += -2.0 * (x_ - C) * 1.0 * E;
			k[4] += -2.0 * (y_ - D) * x * E; k[5] += -2.0 * (y_ - D) * y * E; k[6] += -2.0 * (y_ - D) * 1.0 * E;
			k[7] += 2.0 * (x_ - C) * x * E * C + 2.0 * (y_ - D) * x * E * D;
			k[8] += 2.0 * (x_ - C) * y * E * C + 2.0 * (y_ - D) * y * E * D;
		}
		//-1곱하기
		for (int i = 1; i <= 8; i++) k[i] *= -1.0;
		//Hessian 구하기
		for (int i = 0; i < N; i++) {
			float E, temp1[8], temp2[8];//temp1은 x'편미분, temp2는 y'편미분 모아놓음
			x = Left[i].x, y = Left[i].y, x_ = Right[i].x, y_ = Right[i].y;
			E = 1.0f / (a[7] * x + a[8] * y + 1.0f);
			temp1[0] = x * E, temp1[1] = y * E, temp1[2] = E, temp1[3] = temp1[4] = temp1[5] = 0.0;
			temp1[6] = (a[1] * x + a[2] * y + a[3]) * (-x) * E * E, temp1[7] = (a[1] * x + a[2] * y + a[3]) * (-y) * E * E;
			temp2[0] = temp2[1] = temp2[2] = 0.0, temp2[3] = x * E, temp2[4] = y * E, temp2[5] = E;
			temp2[6] = (a[4] * x + a[5] * y + a[6]) * (-x) * E * E, temp2[7] = (a[4] * x + a[5] * y + a[6]) * (-y) * E * E;
			for (int e = 0; e < 8; e++) for (int h = 0; h < 8; h++) H[e + 1][h + 1] = temp1[e] * temp1[h] + temp2[e] * temp2[h];
		}
		//H'구하기
		for (int i = 1; i <= 8; i++) H[i][i] += r;
		//LU decomposition을 이용해 a의 변화량 구하기
		ludcmp(H, 8, indx, &d);
		lubksb(H, 8, indx, k);
		//a에 의해 error가 어떻게 변화했는지 구하고, 상황에 따른 처리
		before = 0.0, after = 0.0;
		for (int i = 0; i < N; i++) {
			x = Left[i].x, y = Left[i].y, x_ = Right[i].x, y_ = Right[i].y;
			before += ((x_ - (a[1] * x + a[2] * x + a[3]) / (a[7] * x + a[8] * y + 1))) * ((x_ - (a[1] * x + a[2] * x + a[3]) / (a[7] * x + a[8] * y + 1)))
				+ ((y_ - (a[4] * x + a[5] * x + a[6]) / (a[7] * x + a[8] * y + 1))) * ((y_ - (a[4] * x + a[5] * x + a[6]) / (a[7] * x + a[8] * y + 1)));
			after += ((x_ - ((a[1] + k[1]) * x + (a[2] + k[2]) * x + (a[3] + k[3])) / ((a[7] + k[7]) * x + (a[8] + k[8]) * y + 1))) * ((x_ - ((a[1] + k[1]) * x + (a[2] + k[2]) * x + (a[3] + k[3])) / ((a[7] + k[7]) * x + (a[8] + k[8]) * y + 1)))
				+ ((y_ - ((a[4] + k[4]) * x + (a[5] + k[5]) * x + (a[6] + k[6])) / ((a[7] + k[7]) * x + (a[8] + k[8]) * y + 1))) * ((y_ - ((a[4] + k[4]) * x + (a[5] + k[5]) * x + (a[6] + k[6])) / ((a[7] + k[7]) * x + (a[8] + k[8]) * y + 1)));
		}
		if (before <= after) r *= 10.0;
		else {
			for (int i = 1; i <= 8; i++) a[i] += k[i];
			r /= 10.0;
		}
		//더 이상 a에 변화가 없을 시에 종료
		if (100 * (after - before) / after < 10E-4) {
			printf("Algorithm end!!\n");
			break;
		}
	}
	printf("------%s------\n", file_name);
	printf("Matching points: %d\n", N);
	printf("Set of a:\n");
	for (int i = 1; i <= 8; i++) printf("a[%d]: %7.3f\n", i,a[i]);
	printf("Error square: %10.5f\n", after);
	fclose(file);
	return 0;
}