#include <stdio.h>

#define N 1000

int my_strlen(char* s);

int main() {
	char s[N];
	scanf("%s", s);	
	printf("%d", my_strlen(s));

	return 0;
}

int my_strlen(char* s) {
	size_t l = 0;
	while(s[l]) l++;
	return l;
}
