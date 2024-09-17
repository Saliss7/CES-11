/* Matheus Felipe Ramos Borges             */
/* Turma 4                                 */
/* Exercício 2: Produto de matrizes        */
/*                                         */
/* Programa compilado com CLion 2024.2.0.1 */

#include <stdio.h>
#include <stdlib.h>

int MinimoMultiplicacoes(int i, int j, int *quantidadeLinhas, int *quantidadeColunas, int *contador, int **melhorCorte) {

    (*contador)++;
    int k, minimo, auxiliar;

    /**
     * Retornar 0 caso so tenha uma matriz
     */
    if (i == j) {
        return 0;
    }

    /**
     * Encontrar o minimo e o melhor corte entre todos os cortes possiveis
     */
    else {
        minimo = MinimoMultiplicacoes(i, i, quantidadeLinhas, quantidadeColunas, contador, melhorCorte) +
                 MinimoMultiplicacoes(i + 1, j, quantidadeLinhas, quantidadeColunas, contador, melhorCorte) +
                 quantidadeLinhas[i] * quantidadeColunas[i] * quantidadeColunas[j];
        melhorCorte[i][j] = i;
        for (k = i + 1; k < j; k++) {
            auxiliar = MinimoMultiplicacoes(i, k, quantidadeLinhas, quantidadeColunas, contador, melhorCorte) +
                     MinimoMultiplicacoes(k + 1, j, quantidadeLinhas, quantidadeColunas, contador, melhorCorte) +
                     quantidadeLinhas[i] * quantidadeColunas[k] * quantidadeColunas[j];
            if (minimo >= auxiliar) {
                minimo = auxiliar;
                melhorCorte[i][j] = k;
            }
        }
        return minimo;
    }
}

void MelhorCaminho (int i, int j, int **melhorCorte, FILE *Saida) {

    /**
     * Coso sejam matrizes adjacentes
     */
    if (i == j)
        return;
    if (melhorCorte[i][j] == i && j - i == 1)
        fprintf (Saida, "   %2d x %2d\n", i, j);

    /**
     * Chamada da recursao
     */
    MelhorCaminho(i, melhorCorte[i][j], melhorCorte, Saida);
    MelhorCaminho(melhorCorte[i][j] + 1, j, melhorCorte, Saida);

    /**
     * Cosos intermediarios
     */
    if (j - i > 1) {
        if (melhorCorte[i][j] == i) {
            fprintf(Saida, "   %2d x %2d-%2d\n", i, i + 1, j);
        } else if (melhorCorte[i][j] == j - 1) {
            fprintf(Saida, "%2d-%2d x %2d\n", i, j - 1, j);
        } else {
            fprintf(Saida, "%2d-%2d x %2d-%2d\n", i, melhorCorte[i][j], melhorCorte[i][j] + 1, j);
        }
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

    fprintf(Saida, "Exemplo de arquivo de saida\nExercicio 2\nProduto de Matrizes\n\n");

    /**
     * Printar o minimo de multiplicacoes e quantas vezes a funcao e chamada
     */
    fprintf(Saida, "Total de multiplicacoes escalares = %d\n\n", MinimoMultiplicacoes(1, quantidadeMatrizes, quantidadeLinhas, quantidadeColunas, &contador, melhorCorte));
    fprintf(Saida,"Chamadas aa funcao: %d\n\n", contador);

    fprintf(Saida, "Melhor ordem para realizar o produto:\n");

    /**
     * Printar o melhor caminho
     */
    MelhorCaminho (1, quantidadeMatrizes, melhorCorte, Saida);

    fclose(Entrada);
    fclose(Saida);
    return 0;
}