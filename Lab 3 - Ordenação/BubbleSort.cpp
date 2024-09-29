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

int main() {

    tipoelemento *v;
    tipoelemento *auxiliar;
    clock_t inicio_t, fim_t;
    float delta_t;
    int i;
    FILE *Entrada;
    FILE *SaidaBubble;
    Entrada = fopen("entrada3.txt", "r");
    SaidaBubble = fopen("Lab3_Matheus_Felipe_Ramos_Borges_bubble.txt", "w");

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
    fprintf(SaidaBubble, "Tempo de execução : %.3f segundos\n\n", delta_t);
    fprintf(SaidaBubble, "--------------------------------------------------\n");

    for (i = 0; i < quantidadeStrings; i++) {
        fprintf(SaidaBubble, "%s\n", v[i]);
    }

    for (i = 0; i < quantidadeStrings; i++) {
        strcpy(v[i], auxiliar[i]);
    }

    fclose(Entrada);
    fclose(SaidaBubble);
    return 0;
}
