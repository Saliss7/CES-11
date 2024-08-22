/* Matheus Felipe Ramos Borges        */
/* Turma 4                            */
/* Exercício 1: Torre de Controle     */
/*                                    */
/* Programa compilado com CLion 17.12 */

#include<stdio.h>

typedef struct{
    int numero;
    char localPartida;
    int* proximoFila;
}aviao;

int main() {

    int* primeiroFila = NULL;
    aviao aviao[100];
    FILE* Entrada;
    Entrada = fopen("entrada1.txt", "r");

    if (Entrada == NULL) {
        printf("Erro ao abrir o arquivo\n");
        return 0;
    }

    fclose(Entrada);
    return 0;
}