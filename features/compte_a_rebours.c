#include <stdio.h>
#include <unistd.h>
#include "function.h"

void compte_a_rebours(int *chiffre) {
    //int value = chiffre;
    while (*chiffre != 0) {
        if (*chiffre < 6) {
            printf("\033[31m%d\033[0m\n", *chiffre); // A partir de 5 proche de la fin, donc les nombres sont affiché en rouge.
        } else {
            printf("%d\n", *chiffre);
        }

        *chiffre = *chiffre - 1;
        if (*chiffre == 1) {
            printf("\033[32mFIN DU COMPTE À REBOURS !!\033[0m");
        };
        sleep(1);
    }
}