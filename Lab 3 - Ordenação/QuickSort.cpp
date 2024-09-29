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
    clock_t inicio_t, fim_t;
    float delta_t;
    int i;
    FILE *Entrada;
    FILE *SaidaQuick;
    Entrada = fopen("entrada3.txt", "r");
    SaidaQuick = fopen("Lab3_Matheus_Felipe_Ramos_Borges_quick.txt", "w");

    fscanf(Entrada, "%d", &quantidadeStrings);

    v = (tipoelemento *) malloc(quantidadeStrings*sizeof(tipoelemento));

    for (i = 0; i < quantidadeStrings; i++) {
        fscanf(Entrada, "%s", v[i]);
    }

    contador = 0;

    inicio_t = clock();
    QuickSort(v, 0, quantidadeStrings - 1);
    fim_t = clock();

    delta_t = (fim_t - inicio_t) / (float) CLOCKS_PER_SEC;

    fprintf(SaidaQuick, "Algoritmo: Quick-Sort\n\nTamanho da entrada: %d\n", quantidadeStrings);
    fprintf(SaidaQuick, "Comparações feitas: %d\n", contador);
    fprintf(SaidaQuick, "Tempo de execução : %.3f segundos\n\n", delta_t);
    fprintf(SaidaQuick, "--------------------------------------------------\n");

    for (i = 0; i < quantidadeStrings; i++) {
        fprintf(SaidaQuick, "%s\n", v[i]);
    }

    fclose(Entrada);
    fclose(SaidaQuick);
    return 0;
}
