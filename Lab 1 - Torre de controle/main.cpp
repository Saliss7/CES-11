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
    noh* primeiroAuxiliar = NULL;
    noh* segundoAuxiliar = NULL;
    noh* ultimoUrgencia = NULL;
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
            fscanf(Entrada, "%d ", &(primeiroFila->numero));
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
            primeiroAuxiliar = (noh*)malloc(sizeof(noh));
            fscanf(Entrada, "%s", primeiroAuxiliar->menssagem);
            fscanf(Entrada, "%d ", &(primeiroAuxiliar->numero));
            fgets(primeiroAuxiliar->localPartida, sizeof(primeiroAuxiliar->proximoFila), Entrada);
            primeiroAuxiliar->proximoFila = NULL;
            if(strcmp(primeiroAuxiliar->menssagem, "pista_liberada") == 0) {
                printf("%s    %04d    %s", primeiroFila->menssagem, primeiroFila->numero, primeiroFila->localPartida);
                free(primeiroAuxiliar);
                primeiroAuxiliar = primeiroFila->proximoFila;
                free(primeiroFila);
                primeiroFila = primeiroAuxiliar;
                primeiroAuxiliar = NULL;
            }
            if(strcmp(primeiroAuxiliar->menssagem, "pede_pouso") == 0) {
                primeiroAuxiliar->proximoFila = primeiroFila;
                while(primeiroAuxiliar->proximoFila->proximoFila != NULL) primeiroAuxiliar->proximoFila = primeiroAuxiliar->proximoFila->proximoFila;
                primeiroAuxiliar->proximoFila->proximoFila = primeiroAuxiliar;
                primeiroAuxiliar->proximoFila = NULL;
            }
            if(strcmp(primeiroAuxiliar->menssagem, "URGENCIA") == 0) {
                if(ultimoUrgencia == NULL) {
                    primeiroAuxiliar->proximoFila = primeiroFila;
                    while(primeiroAuxiliar->numero != primeiroAuxiliar->proximoFila->numero) {
                        segundoAuxiliar = primeiroAuxiliar->proximoFila;
                        primeiroAuxiliar->proximoFila = primeiroAuxiliar->proximoFila->proximoFila;
                    }
                    ultimoUrgencia = primeiroAuxiliar->proximoFila;
                    segundoAuxiliar->proximoFila = primeiroAuxiliar->proximoFila->proximoFila;
                    ultimoUrgencia->proximoFila = primeiroFila;
                    primeiroFila = ultimoUrgencia;
                    free(primeiroAuxiliar);
                    primeiroAuxiliar = NULL;
                    segundoAuxiliar = NULL;
                }
                if(ultimoUrgencia != NULL) {
                    primeiroAuxiliar->proximoFila = primeiroFila;
                    while(primeiroAuxiliar->numero != primeiroAuxiliar->proximoFila->numero) {
                        segundoAuxiliar = primeiroAuxiliar->proximoFila;
                        primeiroAuxiliar->proximoFila = primeiroAuxiliar->proximoFila->proximoFila;
                    }
                    segundoAuxiliar->proximoFila = primeiroAuxiliar->proximoFila->proximoFila;
                    primeiroAuxiliar->proximoFila->proximoFila = ultimoUrgencia->proximoFila;
                    ultimoUrgencia->proximoFila =  primeiroAuxiliar->proximoFila;
                    ultimoUrgencia = primeiroAuxiliar->proximoFila;
                    free(primeiroAuxiliar);
                    primeiroAuxiliar = NULL;
                    segundoAuxiliar = NULL;
                }
            }
            if(strcmp(primeiroAuxiliar->menssagem, "FIM") == 0) {
                lerArquivo = false;
                free(primeiroAuxiliar);
                primeiroAuxiliar = NULL;
                //implementar a logica do fim da fila aqui.
            }
        }


        i++;
    }

    fclose(Entrada);
    return 0;
}