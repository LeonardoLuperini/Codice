#include "selezionaPrimi.h"

int isPrime(long int x) {
    for (long int i = 2; i <= sqrt(x); i++) {
        if (x % i == 0)
            return 0;
    }
    return 1;
}
