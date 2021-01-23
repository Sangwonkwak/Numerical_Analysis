#include <stdio.h>
#include <stdlib.h>

void lubksb(float **a, int n, int *indx, float b[],int* sin);

//파일에서 ' '전까지 읽어들인 수를 int or float으로 변환해주는 함수
int change_to_int(FILE* fp) {
	char temp, arr[10];
	int i = 0;
	while (1) {
		temp = fgetc(fp);
		if (temp == '	' || temp == ' ') break;
		arr[i++] = temp;
	}
	arr[i] = '\0';
	return atoi(arr);
}

float change_to_float(FILE* fp) {
	char temp = 1, arr[10];
	int i = 0;
	while (1) {
		temp = fgetc(fp);
		if (temp == ' ' || temp == '	' || temp == '\n') break;
		arr[i++] = temp;
	}
	arr[i] = '\0';
	return (float)atof(arr);
}
//한 열씩 inverse matrix를 구하는 함수
void inverse(float **a, int n, int *indx, float **a_inverse) {
	int i, j,temp;
	float* col = (float*)malloc(sizeof(float)*(n+1));
	
	for (j= 1 ; j <= n; j++) {
		for (i = 1; i <= n; i++) col[i] = 0.0;
		//identity matrix의 한 열씩 가져온다
		col[j] = 1.0;
		lubksb(a, n, indx, col,&temp);
		for (i = 1; i <= n; i++) a_inverse[i][j] = col[i];
	}
	free(col);
}


