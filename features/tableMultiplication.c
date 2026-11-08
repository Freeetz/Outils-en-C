#include <stdio.h>
#include "function.h"

void tableMultiplication(void) {
    int table, multiple;
    printf("Quelle table souhaitez-vous afficher ? ");
    scanf("%d", &table);
    printf("Jusqu'à quelle multiple ? ");
    scanf("%d", &multiple);

    for (int i = 0; i <= multiple; i++) {
        printf("\033[36m%d\033[0m x \033[36m%d\033[0m = \033[1;31m%d\033[0m\n", table, i, table * i);
    }
}