#include "statistic.h"

double arraysum(double numbers[], size_t len) {
	double res = 0;
	for(int i = 0; i < len; i++)
		res += numbers[i];	
	return res;
}

void sqarray(double numbers[], size_t len) {
	for(int i = 0; i < len; i++) {
		numbers[i] *= numbers[i];
	}
}

void subtoarray(double numbers[], size_t len, double num) {
	for(int i = 0; i < len; i++) {
		numbers[i] -= num;
	}
}

double avg(double numbers[], size_t len) {
	if (!(len)) return 0;
	return arraysum(numbers, len)/len;
}

double* deepcopy(double numbers[], size_t len) {
	double* copy = malloc(len * sizeof(double));
	if (copy == NULL) exit(EXIT_FAILURE);

	for (int i = 0; i < len; i++) {
		copy[i] = numbers[i];
	}
	
	return copy;
}

double std(double numbers[], size_t len) {
	if (len < 2) return 0;
	
	double* temp = deepcopy(numbers, len);
	
	double average = avg(numbers, len);
	subtoarray(temp, len, average);
	sqarray(temp, len);
	double res = sqrt(arraysum(temp, len)/len);	
	
	free(temp);
	return res;	
}
