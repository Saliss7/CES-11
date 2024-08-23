/* Matheus Felipe Ramos Borges        */
/* Turma 4                            */
/* Exercício 1: Torre de Controle     */
/*                                    */
/* Programa compilado com CLion 17.12 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct aviao noh;

struct aviao{
    char menssagem[70];
    int numero;
    char localPartida[30];
    noh* proximoFila = NULL;
};

int main() {

    noh* primeiroFila = NULL;
    noh* p = NULL;
    int i = 0;
    bool lerArquivo = true;
    char linha[200];
    FILE* Entrada;
    Entrada = fopen("entrada1.txt", "r");

    //pular as 8 primeiras linhas do arquivo de entrada
    for (int i = 0; i < 8; i++) {
        fgets(linha, sizeof(linha), Entrada);
    }

    while(lerArquivo) {
        if(primeiroFila == NULL) {
            primeiroFila = (noh*)malloc(sizeof(noh));
            fscanf(Entrada, "%s", &primeiroFila->menssagem);
            fscanf(Entrada, "%d ", &primeiroFila->numero);
            fgets(primeiroFila->localPartida, Entrada);
            primeiroFila->proximoFila = NULL;
        } else {
            primeiroFila = (noh*)malloc(sizeof(noh));
            fscanf(Entrada, "%s", &p->menssagem);
            fscanf(Entrada, "%d ", &p->numero);
            fgets(p->localPartida, Entrada);
            p->proximoFila = primeiroFila;
            while (p->proximoFila != NULL) p->proximoFila = p->proximoFila->proximoFila;
        }


        i++;
    }

    fclose(Entrada);
    return 0;
}