#pragma warning(disable:4996)
#define NRANSI
#include <stdio.h>
#include <stdlib.h>
#include "nrutil.h"
#include "func.h"
//Matrix �ִ����
#define NP 20

int main() {
	//����1��
	/*
	char temp[30];
	char file_name[3][20] = { {"lineq1.dat"},{"lineq2.dat"},{"lineq3.dat"} };
	//a_~�� a�� decmposition�� ������� ����, b_~�� �� ��� ���Ŀ� solution�� ���
	float **a, **a_lu, *b, **b_gauss, *b_lu, d;
	//sin�� singular�� �Ǻ��ϱ����� ����
	int n,*indx,sin;
	
	//�� matrix �� vector����
	a = matrix(1, NP, 1, NP);
	a_lu = matrix(1, NP, 1, NP);
	b_gauss = matrix(1, NP, 1, 1);
	b = vector(1, NP);
	b_lu = vector(1, NP);
	indx = ivector(1, NP);
	
	
	for (int i = 0; i < 3; i++) {
		FILE *fp = fopen(file_name[i], "r");
		printf("-------%s-------\n",file_name[i]);
		//nũ�� �޾Ƶ��̱�
		n = change_to_int(fp);
		
		//ù ��° ���� �ʿ���� ���� �� �б�
		fgets(temp, 20, fp);
		
		//a�� �� �Է�
		for (int r = 1; r <= n; r++) {
			for (int c = 1; c <= n; c++) {
				a[r][c] = change_to_float(fp);
				a_lu[r][c] = a[r][c];
			}
		}
		
		//b�� �� �Է�
		for (int r = 1; r <= n; r++) {
			b[r] = change_to_float(fp);
			b_gauss[r][1] = b[r];
			b_lu[r] = b[r];
		}
		
		//Ax=b�� �����ϴ� x���ϱ�
		//1.gauss-jordan elimination
		
		printf("<Gauss-Jordan elimination>\n");
		sin = 1;
		//a set of solution�� b_gauss�� ����ȴ�.
		gaussj(a, n, b_gauss,1, &sin);
		//sin�� 1�̸� non singular
		if (sin == 1) {
			printf("solution(x) : ");
			for (int r = 1; r <= n; r++) printf("%9f ", b_gauss[r][1]);
		}

		//2.LU decomposition
		printf("\n<LU Decomposition>\n");
		sin = 1;
		ludcmp(a_lu, n, indx, &d);
		lubksb(a_lu, n, indx, b_lu,&sin);
		if (sin == 1) {
			printf("solution(x) : ");
			for (int r = 1; r <= n; r++) printf("%9f ", b_lu[r]);
		}
		printf("\n\n");
		fclose(fp);
	}
	free_matrix(a, 1, n, 1, n);
	free_matrix(a_lu, 1, n, 1, n);
	free_matrix(b_gauss, 1, n, 1, 1);
	free_vector(b, 1, n);
	free_vector(b_lu, 1, n);
	free_ivector(indx, 1, n);
	
	*/
	//����2
	
	char file_name[3][20] = { {"lineq1.dat"},{"lineq2.dat"},{"lineq3.dat"} };
	float **a, **a_lud, *b, *x, d;
	int *indx, n, sin;
	char temp[20];
	FILE* fp;

	a = matrix(1, NP, 1, NP);
	a_lud = matrix(1, NP, 1, NP);
	b = vector(1, NP);
	x = vector(1, NP);
	indx = ivector(1, NP);

	for (int i = 0; i < 3; i++) {
		fp = fopen(file_name[i], "r");
		printf("-------%s-------\n", file_name[i]);
		//nũ�� �޾Ƶ��̱�
		n = change_to_int(fp);
		//ù ��° ���� �ʿ���� ���� �� �б�
		fgets(temp, 20 , fp);

		for (int r = 1; r <= n; r++)
			for (int c = 1; c <= n; c++) {
				a[r][c] = change_to_float(fp);
				a_lud[r][c] = a[r][c];
			}
		
		//��� b�����
		for (int r = 1; r <= n; r++) {
			b[r] = change_to_float(fp);
			x[r] = b[r];
		}
		
		printf("<iterative improvement>\n");
		sin = 1;
		ludcmp(a_lud, n, indx, &d);
		mprove(a, a_lud, n, indx, b, x, &sin);
		//singular ����Ȯ��
		if (sin == 1) {
			printf("solution(x) : ");
			for (int r = 1; r <= n; r++) printf("%f ", x[r]);
		}
		printf("\n\n\n");
		fclose(fp);
	}
	
	//����3
	/*
	char temp[30];
	char file_name[3][20] = { {"lineq1.dat"},{"lineq2.dat"},{"lineq3.dat"} };
	float **a, **a_inverse, d;
	int *indx, n;
	
	for (int i = 0; i < 3; i++) {
		FILE *fp = fopen(file_name[i], "rt");
		printf("-------%s-------\n", file_name[i]);

		n = change_to_int(fp);
		fgets(temp, 20, fp);
		a = matrix(1, n, 1, n);
		a_inverse = matrix(1, n, 1, n);
		
		for (int r = 1; r <= n; r++) for (int c = 1; c <= n; c++) a[r][c] = change_to_float(fp);
		indx = ivector(1, n);
		ludcmp(a, n, indx, &d);
		//determinant ���ϱ�
		for (int i = 1; i <= n; i++) d *= a[i][i];
		printf("Determinant : %f\n", d);

		//inverse_matrix ���ϱ�
		if ((int)d != 0) {
			inverse(a, n, indx, a_inverse);
			printf("Inverse matrix\n");
			for (int i = 1; i <= n; i++) {
				for (int j = 1; j <= n; j++) printf("%10f ", a_inverse[i][j]);
				printf("\n");
			}
		}
		else printf("Inverse doesn't exist\n");
		printf("\n\n");
		free_matrix(a, 1, n, 1, n);
		free_matrix(a_inverse, 1, n, 1, n);
		free_ivector(indx, 1, n);
		fclose(fp);
	}
	*/
	return 0;
}

