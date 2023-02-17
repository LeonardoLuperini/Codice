#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 100

int binserach(char* str, size_t n, char** arr);

int main() {
	size_t n; scanf("%zu", &n);
	char* arr[n];
	char s[N];
	int c;

	//Carico l'array
	for (int i = 0; i < n; i++) {
		arr[i] = malloc(N * sizeof(char));
		if (arr[i] == NULL) { printf("Memoria esaurita!\n"); exit(1); }
		scanf("%s", arr[i]);
	}

	// Loop per binserach 
	while (1) {
		scanf("%d", &c);
		if (c != 1) break;
		scanf("%s", s);
		printf("%d\n", binserach(s, n, arr));
	}
	
	//Libero faccio il free della memoria dinamica 
	for (int i = 0; i < n; i++) free(arr[i]);

	return 0;
}

int binserach(char* str, size_t n, char** arr) {
	size_t s = 0, e = n, k = n/2;
	int res;

	while (1) {
		res = strcmp(str, arr[k]);
		
		if (res == 0) return k;
		else if (res < 0) e = k;
		else s = k;

		if( k == (s+e)/2) break;
		else k = (s+e)/2;
		
	}
	
	return -1;
}
