#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h> // Pour false & true
#include <string.h> // Pour comparer deux chaîne de caractère
#include <termios.h> // Gérer le comportement du terminal
#include <unistd.h>
#include "config.h"

bool accessAuthorized = false;
bool hasMdp = false;
bool alreadyTry = false;
bool cine = false;
char username[50];

int connect(void) {
    bool validUsername = false;
    if (!alreadyTry) {
        printf("Bienvenue sur notre outil.\n");
    }
    printf("Veuillez insérez votre \033[31mnom d'utilisateur\033[0m : ");
    scanf("%49s", username);

    if (strcmp(username, USERNAME) == 0) {
        validUsername = true;
        accessAuthorized = true;
        printf("\033[32mNom d'utilisateur valide !\033[0m\n");
        return 1;
    } else {
        printf("\033[31mNom d'utilisateur invalide !\033[0m\n");
        printf("Veuillez réessayer.\n");
        alreadyTry = true;
        validUsername = false;
        return 0;
    }
}

int connectMDP(void) {
    char mdp[50];
    bool validMdp = false;
    struct termios old, new; // termios -> permet de controler le comportement du terminal | struct -> déclare une structure

    printf("Veuillez insérez votre \033[36mMot de Passe :\033[0m ");
    fflush(stdout); // stdout -> Sortie standard : ce qui s'affiche dans le terminal | fflush -> force l'affichage du printf

    tcgetattr(STDIN_FILENO, &old); // tcgetattr -> récupère les attributs du terminal | STDIN_FILENO -> entrée standard (le clavier)
    new = old;
    new.c_lflag &= ~ECHO; // c_lflag -> paramètre locaux du terminal // ~ECHO faire en sorte que ce que tu tape ne s'affiche pas / Cet ligne conserve tout les paramètre et désactive simplement le ECHO.

    tcsetattr(STDIN_FILENO, TCSANOW, &new); // TCSANOW -> appliquer les modif immédiatement 
    scanf("%49s", mdp);
    tcsetattr(STDIN_FILENO, TCSANOW, &old); // Retour à la config initial

    if (strcmp(mdp, PASSWORD) == 0) {
        printf("\n\033[32mMot de passe valide, connexion autorisé !\033[0m \n");
        // sleep(2);
        system("clear");
        validMdp = true;
        hasMdp = true;
        return 1;
    } else {
        printf("\n\033[31mMot de passe invalide, connexion refusé !\033[0m\n");
        return 0;
    }
}

void calcul(char choix[]) { 

    if (strcmp(choix, "addition") == 0 || strcmp(choix, "soustraction") == 0 || strcmp(choix, "multiplication") == 0) {
        int number1;
        int number2;
        int resultat;

        printf("\033[33mPremier nombre : \033[0m");
        scanf("%d", &number1);
        printf("\033[33mSecond nombre : \033[0m");
        scanf("%d", &number2);

        if (strcmp(choix, "multiplication") == 0) {
            resultat = number1 * number2;
            printf("Résultat de %d * %d es %d", number1, number2, resultat);
        } else if (strcmp(choix, "addition") == 0) {
            resultat = number1 + number2;
            printf("Résultat de %d + %d es %d", number1, number2, resultat);
        } else if (strcmp(choix, "soustraction") == 0) {
            resultat = number1 - number2;
            printf("Résultat de %d / %d es %d", number1, number2, resultat);
        } else if (strcmp(choix, "reste") == 0) {
            resultat = number1 % number2;
            printf("Résultat de %d modulo %d es %d", number1, number2, resultat);
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

int cinematic() {
    printf("⏳ - \033[33mInitialisation du programme\033[0m\n");
    sleep(3);

    printf("💻 - \033[35mConnexion à votre espace...\033[0m\n");
    sleep(2);

    printf("🔋 - \033[32mEspace synchronisé, bienvenue %s\033[0m !\n", username);
    sleep(3);

    system("clear");
    return 0;
}

int main(void)
{
    while (!accessAuthorized && !hasMdp) {
        accessAuthorized = connect();
        hasMdp = connectMDP();
    }

    while (accessAuthorized && hasMdp) {
        
        if (cine) {
            char action[50];
            printf("💡 Tips: utilisez \033[31mexit\033[0m pour quitter.\n");
            printf("Quel action voulez-vous éxécuter : ");
            scanf("%49s", action);

            if (strcmp(action, "exit") == 0) {
                exit(0);
            } else if (strcmp(action, "calculatrice") == 0) {
                system("clear");
                
                char choix[50];
                printf("Indiquez un type de calcule (division, multiplication, addition, soustraction, reste) : ");
                scanf("%49s", choix);
                calcul(choix);
            } else if (strcmp(action,"compte-a-rebours") == 0) { 
                system("clear");

                int chiffre;
                printf("Indiquez un chiffre de départ : ");
                scanf("%d", &chiffre);
                if (chiffre > 0) {
                    compte_a_rebours(&chiffre);
                } else {
                    printf("\033[31mVous ne pouvez pas indiquer une valeur inférieur à 0.\033[0m\n");
                }
            } else if (strmcp(action, "clear")) {
                system("clear");
            } else {
                printf("\033[31mCommande inexistante\033[0m\n");
            }
        } else {
            cinematic();
            cine = true;
        }
    }
    return 0;
}