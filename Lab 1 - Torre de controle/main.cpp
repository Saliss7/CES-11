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
    noh* ultimoUrgencia = NULL
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
            fscanf(Entrada, "%s", primeiroFila->menssagem);
            fscanf(Entrada, "%d ", primeiroFila->numero);
            fgets(primeiroFila->localPartida, sizeof(primeiroFila->localPartida), Entrada);
            primeiroFila->proximoFila = NULL;
            if(strcmp(primeiroFila->menssagem, "pista_liberada") == 0) {
                free(primeiroFila);
                primeiroFila = NULL;
            }
            if(strcmp(primeiroFila->menssagem, "FIM") == 0) {
                lerArquivo = false;
            }
        }
        if(primeiroFila != NULL) {
            p = (noh*)malloc(sizeof(noh));
            fscanf(Entrada, "%s", p->menssagem);
            fscanf(Entrada, "%d ", p->numero);
            fgets(p->localPartida, sizeof(p->proximoFila), Entrada);
            p->proximoFila = NULL;
            if(strcmp(p->menssagem, "pista_liberada") == 0) {
                printf("%s    %04d    %s", primeiroFila->menssagem, primeiroFila->numero, primeiroFila->localPartida);
                free(p);
                p = primeiroFila->proximoFila;
                free(primeiroFila);
                primeiroFila = p;
                p = NULL;
            }
            if(strcmp(p->menssagem, "pede_pouso") == 0) {
                p->proximoFila = primeiroFila;
                while(p->proximoFila->proximoFila != NULL) p->proximoFila = p->proximoFila->proximoFila;
                p->proximoFila->proximoFila = p;
                p->proximoFila = NULL;
            }
            if(strcmp(p->menssagem, "URGENCIA") == 0) {
                if(ultimoUrgencia == NULL) {
                    p->proximoFila = primeiroFila;
                    while(p->numero != p->proximoFila->numero) {
                        ultimoUrgencia = p->proximoFila;
                        p->proximoFila = p->proximoFila->proximoFila;
                    }
                    ultimoUrgencia->proximoFila = p->proximoFila->proximoFila;
                    p->proximoFila->proximoFila = primeiroFila;
                    //melhorar a logica da urgencia

                    ultimoUrgencia = p->proximoFila->proximoFila;
                    ultimoUrgencia->
                }
                if(ultimoUrgencia != NULL) {

                }
            }
            if(strcmp(p->menssagem, "FIM") == 0) {
                lerArquivo = false;
                free(p);
                p = NULL;
                //implementar a logica do fim da fila aqui.
            }
        }


        i++;
    }

    fclose(Entrada);
    return 0;
}