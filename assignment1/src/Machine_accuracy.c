#include <stdio.h>
int get_eps_float();
int get_eps_double();

int main() {
	printf("Machine_accuracy of 'float': ");
	printf("%d\n", get_eps_float());// float의 경우

	printf("-------------------------------------------\n");

	printf("Machine_accuracy of 'double': ");
	printf("%d\n", get_eps_double());// double의 경우

	return 0;
}

int get_eps_float() {
	float data = 1.0; 
	float temp = 1.0, operand = 0.5;// 
	int n = 0;
	while (1) {
		temp *= operand, n++;
		if (data + temp == data) break;
	}
	return n - 1;
}

int get_eps_double() {
	double data = 1.0;
	double temp = 1.0, operand = 0.5;// 
	int n = 0;
	while (1) {
		temp *= operand, n++;
		if (data + temp == data) break;
	}
	return n - 1;
}
