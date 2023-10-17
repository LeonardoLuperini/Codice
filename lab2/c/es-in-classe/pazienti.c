#include<stdio.h>

typedef struct {
	float glicemia;
	float peso;
} valDiabete;

typedef struct {
	int pressione;
	int fc;
} valCardio;

typedef union {
	valDiabete vd;
	valCardio vc;
} Valori;

typedef struct {
	int id;
	int diagnosi;
	Valori val;
} Paziente;

int main() {
	
	int n;
	printf("Quanti pazienti hai?\n->");
	scanf("%d", &n);
	Paziente lista[n];

	for (int i = 0; i < n; i++){
		printf("id:");
		scanf("%d", &lista[n].id);
		printf("diagnosi:");
		scanf("%d", &lista[n].diagnosi);
		if (lista[n].diagnosi == 0){
			printf("glicemia:");
			scanf("%f", &lista[n].val.vd.glicemia);
			printf("peso:");
			scanf("%f", &lista[n].val.vd.peso);
		}
		else if (lista[n].diagnosi == 1){
			printf("pressione:");
			scanf("%d", &lista[n].val.vc.pressione);
			printf("fc:");
			scanf("%d", &lista[n].val.vc.fc);
		}

		if (n>=1) {
			for (int j = i; j >= 1; j--) {
				if (lista[j].diagnosi == 0){
					printf("Paziente n:%d id:%d diagnosi:%d glicemia:%f peso:%f", j, lista[j].id, lista[j].diagnosi, lista[j].val.vd.glicemia, lista[j].val.vd.peso);
				}
				else if (lista[j].diagnosi == 1){
					printf("Paziente n:%d id:%d diagnosi:%d pressione:%d fc:%d", j, lista[j].id, lista[j].diagnosi, lista[j].val.vc.pressione, lista[j].val.vc.fc);
				}
				if (lista[j].diagnosi == 0){
					printf("Paziente n:%d id:%d diagnosi:%d", j, lista[j].id, lista[j].diagnosi);
				}
			}
		}
	}

	
	return 0;
}
