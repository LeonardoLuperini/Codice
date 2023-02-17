#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, char** argv) {
	if (argc < 3) {
		printf("Parametri insufficenti, insersci la quantità di soldi investiti ogni mese,\nla percentuale mensile attesa e il tempo in mesi!");
	}
	else  {
		float risparmio_mensile = atof(argv[1]); 
		float percentuale = atof(argv[2]);
		int numero_mesi = atoi(argv[3]);
		float res = 0;
		float res_stupido = 0;

		percentuale = (percentuale / (float)100);

		for (int i = 0; i < numero_mesi; i++) {
			res += (res * percentuale) + risparmio_mensile;
			res_stupido -= (res * 0.0016);
			res_stupido += risparmio_mensile;
		}

		printf("Investendo %f al mese con un ritorno mensile dello %f per %d hai guadagneto: %f\n", risparmio_mensile, percentuale, numero_mesi, res);
		printf("Altrimenti avresti avuto %f\n", res_stupido);
	}

	return 0;
}
