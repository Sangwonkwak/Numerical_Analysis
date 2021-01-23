#pragma once
//주어진 함수
void gaussj(float **a, int n, float **b, int m,int* sin);
void ludcmp(float **a, int n, int *indx, float *d);
void lubksb(float **a, int n, int *indx, float b[],int *sin);
void svdcmp(float **a, int m, int n, float w[], float **v);
void svbksb(float **u, float w[], float **v, int m, int n, float b[], float x[]);
void mprove(float **a, float **alud, int n, int indx[], float b[], float x[], int* sin);

//사용자 정의 함수
int change_to_int(FILE* fp);
float change_to_float(FILE* fp);
void inverse(float **a, int n, int *indx, float **a_inverse);