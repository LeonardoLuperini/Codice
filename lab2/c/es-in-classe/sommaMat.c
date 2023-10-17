#include<stdio.h>

int** leggiMatriceDyn(int* r, int* c);
//void sum(int m1[][], int m2[][], int m3[][]);
int readInt(){
	int r;
	scanf("%d",r);
	if 
	
}


int main() {
	int r1 = 0,c1 = 0, r2 = 0, c2 = 0;
	
	int** m1 = leggiMatriceDyn(&r1, &c1);
	int** m2 = leggiMatriceDyn(&r2, &c2);
	
	if ((r1 == r2) && (c1 == c2)){
		
	}

	//int m3[r1][c1] = sum(m1, m2,m3);
	
	return 0;
}

int** leggiMatriceDyn(int* r, int* c) {
	int** m;
	*r = readInt();
	*c = readInt();
	m = (int**)malloc((*r)*sizeof(int*));
	if (m == NULL){
		printf("Memoria esaurita");
		exit(1);
	}
	for (int i = *r; i < *r; i++){
		

	}
	

	return m;

}


//void sum(int m1[][], int m2[][], int m3[][]) {}
