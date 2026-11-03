#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h> // Pour false & true
#include <string.h> // Pour comparer deux chaîne de caractère
#include <termios.h>
#include <unistd.h>

bool accessAuthorized = false;
bool hasMdp = false;
bool alreadyTry = false;

int connect(void) {
    char username[50];
    bool validUsername = false;
    if (!alreadyTry) {
        printf("Bienvenue sur notre outil.\n");
    }
    printf("Veuillez insérez votre \033[31mnom d'utilisateur\033[0m : ");
    scanf("%49s", username);

    if (strcmp(username, "user") == 0) {
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
    struct termios old, new;

    printf("Veuillez insérez votre \033[36mMot de Passe :\033[0m ");
    fflush(stdout);

    tcgetattr(STDIN_FILENO, &old);
    new = old;
    new.c_lflag &= ~ECHO;

    tcsetattr(STDIN_FILENO, TCSANOW, &new);
    scanf("%49s", mdp);
    tcsetattr(STDIN_FILENO, TCSANOW, &old);

    if (strcmp(mdp, "password") == 0) {
        printf("\nMot de passe valide, connexion autorisé !\n");
        validMdp = true;
        hasMdp = true;
        return 1;
    } else {
        printf("\n\033[31mMot de passe invalide, connexion refusé !\033[0m\n");
        return 0;
    }

    return 0;
}

int addition(void) {
    // voir la création de table, détection auto du nombre de chiffre etc..
    return 0;
}

int main(void)
{
    while (!accessAuthorized && !hasMdp) {
        accessAuthorized = connect();
        hasMdp = connectMDP();
    }

    while (accessAuthorized && hasMdp) {
        char action[50];
        printf("Quel action voulez-vous éxécuter : ");
        scanf("%49s", action);

        if (strcmp(action, "exit") == 0) {
            exit(0);
        } else if (strcmp(action, "addition")) {
            addition();
        } else {
            printf("Commande inexistante");
        }
    }
    return 0;
}