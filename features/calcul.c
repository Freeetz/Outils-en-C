#include <stdio.h>
#include <string.h> // Pour comparer deux chaîne de caractère
#include "function.h"

void calcul(char choix[]) { 

    if (strcmp(choix, "addition") == 0 || strcmp(choix, "soustraction") == 0 || strcmp(choix, "multiplication") == 0 || strcmp(choix, "reste") == 0) {
        int number1;
        int number2;
        int resultat;

        printf("\033[33mPremier nombre : \033[0m");
        scanf("%d", &number1);
        printf("\033[33mSecond nombre : \033[0m");
        scanf("%d", &number2);

        if (strcmp(choix, "multiplication") == 0) {
            resultat = number1 * number2;
            printf("Résultat de %d * %d es %d\n", number1, number2, resultat);
        } else if (strcmp(choix, "addition") == 0) {
            resultat = number1 + number2;
            printf("Résultat de %d + %d es %d\n", number1, number2, resultat);
        } else if (strcmp(choix, "soustraction") == 0) {
            resultat = number1 - number2;
            printf("Résultat de %d - %d es %d\n", number1, number2, resultat);
        } else if (strcmp(choix, "reste") == 0) {
            resultat = number1 % number2;
            printf("Résultat de %d modulo %d es %d\n", number1, number2, resultat);
        }
    } else if (strcmp(choix, "division") == 0) {
        double number1;
        double number2;
        double resultat;

        printf("\033[33mPremier nombre : \033[0m"); 
        scanf("%lf", &number1);
        printf("\033[33mSecond nombre : \033[0m");
        scanf("%lf", &number2);

        if (number2 != 0) {
            resultat = number1 / number2;
            printf("Résultat de %.2f / %.2f = %.2f\n", number1, number2, resultat);
        } else {
            printf("Division par zéro pas possible.");
        }
    } else {
        printf("Commande inconnu");
    }
}