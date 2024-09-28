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

void BubbleSort (tipoelemento *v) {

    int i, j;
    tipoelemento aux;

    for (j = 0; j < quantidadeStrings; j++){
            for (i = 0; i < quantidadeStrings - j - 1; i++){
                if (compara(v[i], v[i+1]) > 0) {
                    strcpy(aux, v[i]);
                    strcpy(v[i], v[i+1]);
                    strcpy(v[i+1], aux);
                }
            }
    }
}

/**
 * Dado um vetor V e dadas duas posicoes ini e fim.
 * A metade da esquerda desse trecho ja´ esta´ ordenada
 * e a metade da direita  desse trecho ja´ esta´ ordenada.
 * Fazer intercalacao (merge) e obter V ordenado.
 */
void Merge (tipoelemento *v, int inicio, int fim) {
    tipoelemento *temporario = (tipoelemento *) malloc(quantidadeStrings*sizeof(tipoelemento)); // temporario
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
    free(temporario);
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

/**
 * Dado um vetor v com elementos em qualquer ordem,
 * escolher um elemento para ser pivo
 * e entao dividir os elementos de V em duas partes:
 * a esquerda: menores que o pivo
 * a direita:  maiores ou iguais ao pivo
 */

int Partition(tipoelemento *v, int inicio, int fim) {
    tipoelemento pivo, aux;
    int esquerda, direita;

    strcpy(pivo, v[inicio]);  //Aqui o pivo e o primeiro da esquerda
    esquerda = inicio + 1;
    direita = fim;

    do {

        /**
         * percorrer da esquerda para a direita. encontrar alguem >= pivo
         */
        while (esquerda < fim && compara(v[esquerda], pivo) < 0) {
            esquerda++;
        }

        /**
         * percorrer da direita para a esquerda. encontrar alguem < pivo
         */
        while (inicio < direita && compara(pivo, v[direita]) <= 0) {
            direita--;
        }

        /**
         * se achou um a esquerda e outro a direita
         */
        if (esquerda < direita) {

            /**
             * permutar
             */
            strcpy(aux, v[esquerda]);
            strcpy(v[esquerda], v[direita]);
            strcpy(v[direita], aux);
        }

        /**
         * caso contrario, terminara a repeticao
         */
    } while (esquerda < direita);


    /**
     * trocar o pivo com o elemento que "divide" os subvetores
     */
    strcpy(v[inicio], v[direita]);
    strcpy(v[direita], pivo);


    /**
     *  retornar a posicao da "divisa"
     */
    return direita;
}

void QuickSort (tipoelemento *v, int inicio, int fim) {
    int particao;
    if (inicio < fim) {
        particao = Partition(v, inicio, fim);
        QuickSort(v, inicio, particao - 1);
        QuickSort(v, particao + 1, fim);
    }
}


int main() {

    tipoelemento *v;
    tipoelemento *auxiliar;
    clock_t inicio_t, fim_t;
    float delta_t;
    int i;
    FILE *Entrada;
    FILE *SaidaBubble;
    FILE *SaidaMerge;
    FILE *SaidaQuick;
    Entrada = fopen("entrada3.txt", "r");
    SaidaBubble = fopen("Lab3_Matheus_Felipe_Ramos_Borges_bubble.txt", "w");
    SaidaMerge = fopen("Lab3_Matheus_Felipe_Ramos_Borges_merge.txt", "w");
    SaidaQuick = fopen("Lab3_Matheus_Felipe_Ramos_Borges_quick.txt", "w");

    fscanf(Entrada, "%d", &quantidadeStrings);

    v = (tipoelemento *) malloc(quantidadeStrings*sizeof(tipoelemento));
    auxiliar = (tipoelemento *) malloc(quantidadeStrings*sizeof(tipoelemento));

    for (i = 0; i < quantidadeStrings; i++) {
        fscanf(Entrada, "%s", v[i]);
    }

    for (i = 0; i < quantidadeStrings; i++) {
        strcpy(auxiliar[i], v[i]);
    }

    contador = 0;

    inicio_t = clock();
    BubbleSort(v);
    fim_t = clock();

    delta_t = (fim_t - inicio_t) / (float) CLOCKS_PER_SEC;

    fprintf(SaidaBubble, "Algoritmo: Bubble-Sort\n\nTamanho da entrada: %d\n", quantidadeStrings);
    fprintf(SaidaBubble, "Comparações feitas: %d\n", contador);
    fprintf(SaidaBubble, "Tempo de execução : %.10f segundos\n\n", delta_t);
    fprintf(SaidaBubble, "--------------------------------------------------\n");

    for (i = 0; i < quantidadeStrings; i++) {
        fprintf(SaidaBubble, "%s\n", v[i]);
    }

    for (i = 0; i < quantidadeStrings; i++) {
        strcpy(v[i], auxiliar[i]);
    }

    contador = 0;

    inicio_t = clock();
    MergeSort (v, 0, quantidadeStrings - 1);
    fim_t = clock();

    delta_t = (fim_t - inicio_t) / (float) CLOCKS_PER_SEC;

    fprintf(SaidaMerge, "Algoritmo: Merge-Sort\n\nTamanho da entrada: %d\n", quantidadeStrings);
    fprintf(SaidaMerge, "Comparações feitas: %d\n", contador);
    fprintf(SaidaMerge, "Tempo de execução : %.10f segundos\n\n", delta_t);
    fprintf(SaidaMerge, "--------------------------------------------------\n");

    for (i = 0; i < quantidadeStrings; i++) {
        fprintf(SaidaMerge, "%s\n", v[i]);
    }

    for (i = 0; i < quantidadeStrings; i++) {
        strcpy(v[i], auxiliar[i]);
    }

    contador = 0;

    inicio_t = clock();
    QuickSort(v, 0, quantidadeStrings - 1);
    fim_t = clock();

    delta_t = (fim_t - inicio_t) / (float) CLOCKS_PER_SEC;

    fprintf(SaidaQuick, "Algoritmo: Quick-Sort\n\nTamanho da entrada: %d\n", quantidadeStrings);
    fprintf(SaidaQuick, "Comparações feitas: %d\n", contador);
    fprintf(SaidaQuick, "Tempo de execução : %.10f segundos\n\n", delta_t);
    fprintf(SaidaQuick, "--------------------------------------------------\n");

    for (i = 0; i < quantidadeStrings; i++) {
        fprintf(SaidaQuick, "%s\n", v[i]);
    }

    fclose(Entrada);
    fclose(SaidaBubble);
    fclose(SaidaMerge);
    fclose(SaidaQuick);
    return 0;
}
