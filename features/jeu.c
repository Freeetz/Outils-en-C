#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h> // Pour false & true
#include "function.h"

void jeu() {
    bool hasNumber = false;
    int nombre = rand() % (100 + 1);
    nombre += 1;

    // printf("💡 - \033[33mTips\033[0m: Si vous avez besoin d'un indice, écrivez simplement '\033[33mindice\033[0m' dans le terminal.\n"); // TODO: Système d'indice

    while (!hasNumber) {
        int prediction;

        printf("Choisissez un nombre entre \033[36m1\033[0m et \033[36m100\033[0m : ");

        if (scanf("%d", &prediction) != 1) {
            printf("\033[31mUtilisez des caractères est strictement interdit.\033[0m\n"); 
            getchar();
        }

        if (prediction < 0 || prediction > 100) { 
            printf("\033[31mVous ne pouvez pas donner un nombre inférieur à 0 ou supérieur à 100.\033[0m\n");
        }

        if (prediction < nombre) { 
            printf("C'est plus !\n");
        } else if (prediction > nombre) {
            printf("C'est moins !\n");
        }

        if (prediction == nombre) {
            printf("\033[32mFélicitation ! Vous avez trouver le nombre.\033[0m\n");
            hasNumber = true;
        }
        
    }
}