#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h> // Pour false & true
#include <string.h> // Pour comparer deux chaîne de caractère
#include <termios.h> // Gérer le comportement du terminal
#include <time.h> 
#include <unistd.h>
#include "config.h"

bool accessAuthorized = false;
bool hasMdp = false;
bool alreadyTry = false;
bool cine = false;
char username[50];
bool Timeout = true;

int checkTimeout() {
    time_t now = time(NULL);
    struct tm *date = localtime(&now);
    FILE *fichier = fopen(".timeout", "r");
    int jour, mois, annee, heure, minute;
    int checkM;

    if (fichier == NULL) { // Le fichier timeout n'existe pas donc l'utilisateur n'as pas de timeout. (Donc oui, il suffirait de suffirait de supprimer le fichier ".timeout" et hop magie on aurais a nouveau accès à l'outil, mais ici le but es d'apprendre pas d'avoir un truc 100% secure, au moment ou j'écris cela, ca fait 6j que j'apprend le C…)
        return 0;
    }

    fscanf(fichier, "%d/%d/%d | %d:%d", &jour, &mois, &annee, &heure, &minute);

    if (jour == date->tm_mday && mois == date->tm_mon && annee == date->tm_year) {
        int minutesTimeout = heure * 60 + minute;
        int minutesNow = date->tm_hour * 60 + date->tm_min;
        int tpsEcouler = minutesNow - minutesTimeout;

        if (tpsEcouler >= 15) {
            fclose(fichier);
            remove(".timeout");
            return 0; // Le timeout es supérieur à 15mn puisqu'il a eu lieu un jour autre qu'aujourd'hui.
        } else {
            printf("\033[31mConnexion impossible\033[0m, veuillez réessayer dans \033[33m%d\033[0m minutes !", 15 - tpsEcouler);
            return 1;
        }
    } else {
        fclose(fichier);
        remove(".timeout");
        return 0; // Le timeout es supérieur à 15mn puisqu'il a eu lieu un jour autre qu'aujourd'hui.
    }
}

int timeout() {
    time_t now = time(NULL);
    struct tm *date = localtime(&now);
    FILE *fichier = fopen(".timeout", "w");
    fprintf(fichier, "%02d/%02d/%02d | %02d:%02d", date->tm_mday, date->tm_mon, date->tm_year, date->tm_hour, date->tm_min);
    fclose(fichier);
    return 0;
}

int connectUser(void) {
    bool validUsername = false;
    int tentative = 3;
    while (validUsername == false) {
        
        if (!alreadyTry) {
            system("clear");
            printf("Bienvenue sur notre outil.\n");
        }
        printf("Veuillez insérez votre \033[31mnom d'utilisateur\033[0m : ");
        scanf("%49s", username);

        if (strcmp(username, USERNAME) == 0) {
            validUsername = true;
            accessAuthorized = true;
            printf("\033[32mNom d'utilisateur valide !\033[0m\n");
            // return 1;
        } else {
            system("clear");
            printf("\n\033[31mNom d'utilisateur invalide !\033[0m\n");
            if (tentative > 1) {
                printf("Veuillez réessayer.\n");
            }
            alreadyTry = true;
            validUsername = false;
            tentative = tentative - 1;
            printf("\033[90m━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\033[0m\n");
            printf("         \033[33m%d\033[0m Tentative restantes !\n", tentative);
            printf("\033[90m━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\033[0m\n");
            // return 0;
        }

        if (tentative == 0) {
            printf("\033[31mTrop de tentative de connexion.\033[0m\n");
            printf("Veuillez \033[33mréessayer plus tard\033[0m (15mn - Délais de sécurité)!");
            timeout();
            exit (0);
        }
    }
    return 1;
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
            printf("Résultat de %d * %d es %d", number1, number2, resultat);
        } else if (strcmp(choix, "addition") == 0) {
            resultat = number1 + number2;
            printf("Résultat de %d + %d es %d", number1, number2, resultat);
        } else if (strcmp(choix, "soustraction") == 0) {
            resultat = number1 - number2;
            printf("Résultat de %d - %d es %d", number1, number2, resultat);
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

void modifMdp() {
    char mdpModifConfirm[50];
    char newMdp[50];
    printf("⚠️  \033[31mACTION DANGEREUSE\033[0m ⚠️\n");
    printf("Veuillez \033[31mconfirmer\033[0m le mot de passe, pour poursuivre : ");
    scanf("%49s", mdpModifConfirm);

    if (strcmp(mdpModifConfirm, PASSWORD) == 0) {
        printf("\033[32mMot de passe valide.\033[0m\n");
        printf("Veuillez indiquer le \033[36mnouveau\033[0m mot de passe : ");
        scanf("%49s", newMdp);
        
        // write directement dans config.c le MDP
        FILE *fichier = fopen("config.c", "w");
        fprintf(fichier,
        "#ifndef CONFIG_H\n"
        "#define CONFIG_H\n\n"
        "const char *USERNAME = \"frtz\";\n"
        "const char *PASSWORD = \"%s\";\n"
        "const char *APP_NAME = \"Programme en C\";\n"
        "const char *APP_VERSION = \"1.0.0\";\n\n"
        "#endif\n", newMdp);
        fclose(fichier);
        printf("🔒 Mot de passe \033[32mmodifier\033[0m avec succès !\n");
    } else {
        printf("\033[31mMot de passe invalide.\033[0m\n");
        printf("Accès \033[31mSUDO bloquer\033[0m sur votre session.\n");
    }
}

int cinematic() {
    time_t now = time(NULL);
    struct tm *date = localtime(&now);

    printf("⏳ - \033[33mInitialisation du programme\033[0m\n");
    sleep(3);

    printf("💻 - \033[35mConnexion à votre espace...\033[0m\n");
    sleep(2);

    printf("🔋 - \033[32mEspace synchronisé, bienvenue %s\033[0m !\n", username);
    sleep(3);

    system("clear");

    printf("\033[36m");
    printf("  ███████╗██████╗ ███████╗███████╗████████╗███████╗\n");
    printf("  ██╔════╝██╔══██╗██╔════╝██╔════╝╚══██╔══╝    ██║\n");
    printf("  █████╗  ██████╔╝█████╗  █████╗     ██║      ██║   \n");
    printf("  ██╔══╝  ██╔══██╗██╔══╝  ██╔══╝     ██║    ██║   \n");
    printf("  ██║     ██║  ██║███████╗███████╗   ██║   ██████║   \n");
    printf("  ╚═╝     ╚═╝  ╚═╝╚══════╝╚══════╝   ╚═╝   ╚═════╝   \n");
    printf("\033[0m");

    printf("\n");
    printf("  \033[1;37mOUTIL INTÉRACTIF EN C | %02d/%02d/%02d \033[0m\n", date->tm_mday, date->tm_mon, date->tm_year+1900);
    printf("  \033[90m━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\033[0m\n");
    printf("     \033[32m●\033[0m Espace synchronisé.\n");
    printf("     \033[36m●\033[0m Bienvenue %s\n", username);
    printf("     \033[33m●\033[0m Accès au commande SUDO : \033[32mautoriser\033[0m\n");
    printf("  \033[90m━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\033[0m\n");
    return 0;
}

int main(void)
{
    srand(time(NULL));

    while (!accessAuthorized || !hasMdp) {
        if (checkTimeout()) {
            exit (0);
        }

        accessAuthorized = connectUser();
        hasMdp = connectMDP();
    }

    while (accessAuthorized && hasMdp) {
        time_t now = time(NULL);
        struct tm *date = localtime(&now);

        if (cine) {
            char action[50];
            printf("    💡 \033[33mTips\033[0m: utilisez \033[31mexit\033[0m pour quitter.\n");
            printf("[\033[36m%02d:%02d:%02d\033[0m] Quel action voulez-vous éxécuter : ", date->tm_hour, date->tm_min, date->tm_sec);
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
            } else if (strcmp(action, "jeu") == 0) {
                system("clear");
                jeu();
            } else if (strcmp(action, "clear") == 0) {
                system("clear");
            } else if (strcmp(action, "mdp") == 0) {
                modifMdp();
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