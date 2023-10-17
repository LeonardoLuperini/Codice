#include<stdio.h>

int main() {
	int a = 5;

	int* aPtr = &a;

	printf("a:%d\naPtr:%p\naptr:%ld\n", a, (void *)aPtr, (long unsigned int)aPtr);
}
