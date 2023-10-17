#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 1000

char* product(char* str, int k);

int main() {
	char str[N];
	int k;

	scanf("%s", str);
	scanf("%d", &k);
	
	printf("%s", product(str, k));

	return 0;
}

char* product(char* str, int k) {
	char* ns = (char*)malloc(k*strlen(str));
	for(int i = 0; i < k; i++) ns = strcat(ns, str);
	return ns;
}
