#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int** criarMatriz(int l, int c) {
    int** matriz = (int**)malloc(c * sizeof(int*));

    for (int i = 0; i < l; i++) {
        matriz[i] = (int*)malloc(l * sizeof(int));
        for (int j = 0; j < c; j++) {
            matriz[i][j] = rand() % 100;
        }
    }
    return matriz;
}

void printarMatriz(int** matriz, int l, int c) {
    printf("MATRIZ:\n");
    for (int i = 0; i < l; i++) {
        for (int j = 0; j < c; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
}

int** multiplicarMatrizes(int** matrizA, int** matrizB, int l1, int c1, int l2, int c2) {
    int** matrizC = (int**)malloc(c1 * sizeof(int*));

    for (int i = 0; i < l1; i++) {
        matrizC[i] = (int*)malloc(c1 * sizeof(int));
        for (int j = 0; j < l2; j++) {
            matrizC[i][j] = 0;
            for (int k = 0; k < c2; k++) {
                matrizC[i][j] += matrizA[i][k] * matrizB[k][j];
            }
        }
    }
    return matrizC;
}

int main() {
    int linhas1;
    int colunas1;
    int linhas2;
    int colunas2;

    int run = 0;
    while(run == 0){
        printf("Digite o numero de linhas da primeira matriz: ");
        scanf("%d", &linhas1);
        printf("Digite o numero de colunas da primeira matriz: ");
        scanf("%d", &colunas1);
        printf("Digite o numero de linhas da segunda matriz: ");
        scanf("%d", &linhas2);
        printf("Digite o numero de colunas da segunda matriz: ");
        scanf("%d", &colunas2);

        if(colunas1 == linhas2){
            run = 1;
            break;
        } else {
            printf("O numero de colunas da primeira matriz precisa ser igual ao numero de linhas da segunda matriz!\n");
        }
    }

    srand(time(NULL));

    int** matrizA = criarMatriz(linhas1, colunas1);
    int** matrizB = criarMatriz(linhas2, colunas2);
    int** matrizC = multiplicarMatrizes(matrizA, matrizB, linhas1, colunas1, linhas2, colunas2);

    printarMatriz(matrizA, linhas1, colunas1);
    printf("\n");
    printarMatriz(matrizB, linhas2, colunas2);
    printf("Resultado:\n");
    printarMatriz(matrizC, colunas1, linhas2);

    for (int i = 0; i < colunas1; i++) {
        free(matrizA[i]);
        free(matrizB[i]);
        free(matrizC[i]);
    }
    free(matrizA);
    free(matrizB);
    free(matrizC);

    return 0;
}
