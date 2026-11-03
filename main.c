#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h> // Pour false & true
#include <string.h> // Pour comparer deux chaîne de caractère

bool accessAuthorized = false;
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
        printf("\033[32mConnexion réussie !\033[0m\n");
        return 1;
    } else {
        printf("\033[31mNom d'utilisateur invalide !\033[0m\n");
        printf("Veuillez réessayer.\n");
        alreadyTry = true;
        validUsername = false;
        return 0;
    }
}

int main(void)
{
    while (!accessAuthorized) {
        accessAuthorized = connect();
    }

    return 0;
}