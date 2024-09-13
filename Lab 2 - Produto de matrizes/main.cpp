/* Matheus Felipe Ramos Borges             */
/* Turma 4                                 */
/* Exercício 2: Produto de matrizes        */
/*                                         */
/* Programa compilado com CLion 2024.2.0.1 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int minimoMultiplicacoes(int i, int j, int *quantidadeLinhas, int *quantidadeColunas, int *contador, int **melhorCorte) {

    (*contador)++;
    int k, minimo, auxiliar;

    if (i == j) {
        return 0;
    } else {
        minimo = minimoMultiplicacoes(i, i, quantidadeLinhas, quantidadeColunas, contador, melhorCorte) +
                 minimoMultiplicacoes(i + 1, j, quantidadeLinhas, quantidadeColunas, contador, melhorCorte) +
                 quantidadeLinhas[i] * quantidadeColunas[i] * quantidadeColunas[j];
        melhorCorte[i][j] = i;
        for (k = i + 1; k < j; k++) {
            auxiliar = minimoMultiplicacoes(i, k, quantidadeLinhas, quantidadeColunas, contador, melhorCorte) +
                     minimoMultiplicacoes(k + 1, j, quantidadeLinhas, quantidadeColunas, contador, melhorCorte) +
                     quantidadeLinhas[i] * quantidadeColunas[k] * quantidadeColunas[j];
            if (minimo > auxiliar) {
                minimo = auxiliar;
                melhorCorte[i][j] = k;
            }
        }
        return minimo;
    }
}

void melhorCaminho (int i, int j, int **melhorCorte) {

    if (melhorCorte[i][j] == i && j - i == 1)
        printf ("     %d x  %d\n", i, j);
    if (j == i)
        return;

    melhorCaminho(i, melhorCorte[i][j], melhorCorte);
    melhorCaminho(melhorCorte[i][j] + 1, j, melhorCorte);

    if (melhorCorte[i][j] == i && j - i > 1) {
        printf ("     %d x  %d- %d\n", i, i+1, j);
    }
    else if (melhorCorte[i][j] == j-1 && j - i > 1) {
        printf ("  %d- %d x  %d\n", i, j - 1, j);
    }
    else if (j - i > 1) {
        printf (" %d- %d x  %d- %d\n", i, melhorCorte[i][j], melhorCorte[i][j] + 1, j);
    }
}

int main() {

    int quantidadeMatrizes;
    int *quantidadeLinhas;
    int *quantidadeColunas;
    int **melhorCorte;
    int contador = 0;
    char linha[70];
    int i;
    FILE *Entrada;
    FILE *Saida;
    Entrada = fopen("entrada2.txt", "r");
    Saida = fopen("saida2.txt", "w");

    /**
     * Pular as 5 primeiras linhas do arquivo de entrada
     */
    for (i = 0; i < 5; i++) {
        fgets(linha, sizeof(linha), Entrada);
    }

    /**
     * Armazenar a quantidade de matrizes
     */
    fscanf(Entrada, "%d", &quantidadeMatrizes);

    quantidadeLinhas = (int *) malloc((quantidadeMatrizes+1)*sizeof(int));
    quantidadeColunas = (int *) malloc((quantidadeMatrizes+1)*sizeof(int));
    melhorCorte = (int **) malloc((quantidadeMatrizes+1)*sizeof(int *));

    for (i = 0; i <= quantidadeMatrizes; i++)
        melhorCorte[i] = (int *)malloc((quantidadeMatrizes+1) * sizeof(int));

    /**
     * Pular mais 3 linhas do arquivo de entrada
     */
    for (i = 0; i < 3; i++) {
        fgets(linha, sizeof(linha), Entrada);
    }

    /**
     * Armazenar a a quantidade de linhas e colunas de cada matriz
     */
    for (i = 1; i <= quantidadeMatrizes; i++)
        fscanf(Entrada, "%d %d", &(quantidadeLinhas[i]), &(quantidadeColunas[i]));

    printf("%d\n", minimoMultiplicacoes(1, quantidadeMatrizes, quantidadeLinhas, quantidadeColunas, &contador, melhorCorte));
    printf("%d", contador);

    printf("\n");
    for (i = 1; i <= quantidadeMatrizes; i++) {
        for (int j = 1; j <= quantidadeMatrizes; j++) {
            printf("%d ", melhorCorte[i][j]);
        }
        printf("\n");  // Nova linha após imprimir todos os elementos de uma linha
    }

    melhorCaminho (1, quantidadeMatrizes, melhorCorte);

    fclose(Entrada);
    fclose(Saida);
    return 0;
}