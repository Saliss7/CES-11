/* Matheus Felipe Ramos Borges             */
/* Turma 4                                 */
/* Exercício 3: Ordenacao                  */
/*                                         */
/* Programa compilado com CLion 2024.2.0.1 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef char tipoelemento[52];
int contador = 0;
int quantidadeStrings;

int compara (const char * a, const char * b) {
    contador ++;
    return strcmp (a, b);
}

/**
 * Dado um vetor V e dadas duas posicoes ini e fim.
 * A metade da esquerda desse trecho ja´ esta´ ordenada
 * e a metade da direita  desse trecho ja´ esta´ ordenada.
 * Fazer intercalacao (merge) e obter V ordenado.
 */
void Merge (tipoelemento *v, int inicio, int fim) {
    static tipoelemento *temporario = (tipoelemento *) malloc(quantidadeStrings*sizeof(tipoelemento)); // temporario
    int media,
            i,     // percorre T
    j,     // percorre lado esquerdo de v
    k;     // percorre lado direito  de v
    media = (inicio + fim)/2;
    j = inicio;
    k = media + 1;
    i = inicio;

    /**
     * Percorrer selecionando os menores
     */
    while (j<=media && k<=fim) {
        if (compara (v[j], v[k]) <= 0) {
            strcpy(temporario[i], v[j]);
            j++;
        }
        else {
            strcpy(temporario[i], v[k]);
            k++;
        }
        i++;
    }

    /**
     * se sobrou algo `a esquerda, copiar para temporario
     */
    while (j <= media) {
        strcpy(temporario[i], v[j]);
        j++;
        i++;
    }

    /**
     * se sobrou algo `a direita, copiar para temporario
     */
    while (k <= fim) {
        strcpy(temporario[i], v[k]);
        k++;
        i++;
    }

    /**
     * v recebe temporario
     */
    for (i = inicio; i <= fim ; i++){
        strcpy(v[i], temporario[i]);
    }
}

void MergeSort (tipoelemento *v, int inicio, int fim) {

    int media;
    if (inicio < fim) {
        media = (inicio + fim)/2;             // dividir ao meio
        MergeSort (v, inicio, media);     // ordenar lado esquerdo
        MergeSort (v, media + 1, fim);  // ordenar lado direito
        Merge(v, inicio,fim);                 // mesclar as duas metades
    }
}

int main() {

    tipoelemento *v;
    clock_t inicio_t, fim_t;
    float delta_t;
    int i;
    FILE *Entrada;
    FILE *SaidaMerge;
    Entrada = fopen("entrada3.txt", "r");
    SaidaMerge = fopen("Lab3_Matheus_Felipe_Ramos_Borges_merge.txt", "w");

    fscanf(Entrada, "%d", &quantidadeStrings);

    v = (tipoelemento *) malloc(quantidadeStrings*sizeof(tipoelemento));

    for (i = 0; i < quantidadeStrings; i++) {
        fscanf(Entrada, "%s", v[i]);
    }

    contador = 0;

    inicio_t = clock();
    MergeSort (v, 0, quantidadeStrings - 1);
    fim_t = clock();

    delta_t = (fim_t - inicio_t) / (float) CLOCKS_PER_SEC;

    fprintf(SaidaMerge, "Algoritmo: Merge-Sort\n\nTamanho da entrada: %d\n", quantidadeStrings);
    fprintf(SaidaMerge, "Comparações feitas: %d\n", contador);
    fprintf(SaidaMerge, "Tempo de execução : %.3f segundos\n\n", delta_t);
    fprintf(SaidaMerge, "--------------------------------------------------\n");

    for (i = 0; i < quantidadeStrings; i++) {
        fprintf(SaidaMerge, "%s\n", v[i]);
    }

    fclose(Entrada);
    fclose(SaidaMerge);
    return 0;
}
