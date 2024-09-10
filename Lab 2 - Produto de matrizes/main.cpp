/* Matheus Felipe Ramos Borges             */
/* Turma 4                                 */
/* Exercício 2: Produto de matrizes        */
/*                                         */
/* Programa compilado com CLion 2024.2.0.1 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int minimoMultiplicacoes(int i, int j, int *quantidadeLinhas, int *quantidadeColunas, int *contador) {

    int k;
    int minimo;

    if (i == j) {
        (*contador)++;
        return 0;
    } else {
        minimo = minimoMultiplicacoes(i, i, quantidadeLinhas, quantidadeColunas, contador) +
                 minimoMultiplicacoes(i + 1, j, quantidadeLinhas, quantidadeColunas, contador) +
                 quantidadeLinhas[i-1] * quantidadeColunas[i-1] * quantidadeColunas[j-1];
        for (k = i + 1; k < j; k++) {
            if (minimo > minimoMultiplicacoes(i, k, quantidadeLinhas, quantidadeColunas, contador) +
                         minimoMultiplicacoes(k + 1, j, quantidadeLinhas, quantidadeColunas, contador) +
                         quantidadeLinhas[i] * quantidadeColunas[k] * quantidadeColunas[j]) {
                minimo = minimoMultiplicacoes(i, k, quantidadeLinhas, quantidadeColunas, contador) +
                         minimoMultiplicacoes(k + 1, j, quantidadeLinhas, quantidadeColunas, contador) +
                         quantidadeLinhas[i-1] * quantidadeColunas[k-1] * quantidadeColunas[j-1];
            }
        }
        return minimo;
    }
}

int main() {

    int quantidadeMatrizes;
    int *quantidadeLinhas;
    int *quantidadeColunas;
    int contador = 0;
    char linha[70];
    int i = 0;
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

    quantidadeLinhas = (int *) malloc(quantidadeMatrizes*sizeof(int));
    quantidadeColunas = (int *) malloc(quantidadeMatrizes*sizeof(int));

    /**
     * Pular mais 3 linhas do arquivo de entrada
     */
    for (i = 0; i < 3; i++) {
        fgets(linha, sizeof(linha), Entrada);
    }

    /**
     * Armazenar a a quantidade de linhas e colunas de cada matriz
     */
    for (i = 0; i < quantidadeMatrizes; i++)
        fscanf(Entrada, "%d %d", &(quantidadeLinhas[i]), &(quantidadeColunas[i]));

    printf("%d", minimoMultiplicacoes(1, quantidadeMatrizes, quantidadeLinhas, quantidadeColunas, &contador));

    fclose(Entrada);
    fclose(Saida);
    return 0;
}