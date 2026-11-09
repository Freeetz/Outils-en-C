#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

void addition() {
    bool go = true;
    int choix;
    int somme = 0;
    while (go) {
        printf("Choisissez un nombre : ");
        scanf("%d", &choix);

        if (choix == 0) {
            go = false;
            printf("Résultat final : %d", somme);
        } else {
            somme = somme + choix;
            printf("Somme total : \033[1;36m%d\033[0m\n", somme);
        }
    }
}