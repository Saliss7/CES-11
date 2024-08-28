/* Matheus Felipe Ramos Borges             */
/* Turma 4                                 */
/* Exercício 1: Torre de Controle          */
/*                                         */
/* Programa compilado com CLion 2024.2.0.1 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct aviao noh;

struct aviao {
    char menssagem[70];
    int numero;
    char localPartida[30];
    noh *proximoFila = NULL;
};

int main() {

    noh *primeiroFila = NULL;
    noh *primeiroAuxiliar = NULL;
    noh *segundoAuxiliar = NULL;
    noh *ultimoUrgencia = NULL;
    bool lerArquivo = true;
    char linha[200];
    FILE *Entrada;
    Entrada = fopen("entrada1.txt", "r");

    //pular as 8 primeiras linhas do arquivo de entrada
    for (int i = 0; i < 8; i++) {
        fgets(linha, sizeof(linha), Entrada);
    }

    printf("Bla bla bla\nBle\nAUTORIZACOES DE POUSO\n=========================================\nFLIGHT  FROM\n\n");

    while (lerArquivo) {
        if (primeiroFila == NULL) {
            primeiroFila = (noh *) malloc(sizeof(noh));
            fscanf(Entrada, "%s", primeiroFila->menssagem);
            fscanf(Entrada, "%d ", &(primeiroFila->numero));
            fgets(primeiroFila->localPartida, sizeof(primeiroFila->localPartida), Entrada);
            primeiroFila->proximoFila = NULL;
            if (strcmp(primeiroFila->menssagem, "pista_liberada") == 0) {
                printf("0000    Nenhum avião pousando\n");
                free(primeiroFila);
                primeiroFila = NULL;
            }
            else if (strcmp(primeiroFila->menssagem, "FIM") == 0) {
                lerArquivo = false;
                printf("\n\nSituacao da fila\n\nFila vazia\n");
                free(primeiroFila);
                primeiroFila = NULL;
            }
        }
        if (primeiroFila != NULL) {
            primeiroAuxiliar = (noh *) malloc(sizeof(noh));
            fscanf(Entrada, "%s", primeiroAuxiliar->menssagem);
            fscanf(Entrada, "%d ", &(primeiroAuxiliar->numero));
            fgets(primeiroAuxiliar->localPartida, sizeof(primeiroAuxiliar->localPartida), Entrada);
            primeiroAuxiliar->proximoFila = NULL;
            if (strcmp(primeiroAuxiliar->menssagem, "pista_liberada") == 0) {
                printf("%04d    %s", primeiroFila->numero, primeiroFila->localPartida);
                free(primeiroAuxiliar);
                primeiroAuxiliar = primeiroFila->proximoFila;
                free(primeiroFila);
                primeiroFila = primeiroAuxiliar;
                primeiroAuxiliar = NULL;
            }
            else if (strcmp(primeiroAuxiliar->menssagem, "pede_pouso") == 0) {
                segundoAuxiliar = primeiroFila;
                while (segundoAuxiliar->proximoFila != NULL) {
                    segundoAuxiliar = segundoAuxiliar->proximoFila;
                }
                segundoAuxiliar->proximoFila = primeiroAuxiliar;
                primeiroAuxiliar = NULL;
            }
            else if (strcmp(primeiroAuxiliar->menssagem, "URGENCIA") == 0) {
                if (ultimoUrgencia == NULL) {
                    if (primeiroAuxiliar->numero == primeiroFila->numero) {
                        ultimoUrgencia = primeiroFila;
                        free(primeiroAuxiliar);
                        primeiroAuxiliar = NULL;
                    }
                    else {
                        segundoAuxiliar = primeiroFila;
                        primeiroAuxiliar->proximoFila = primeiroFila->proximoFila;
                        while (primeiroAuxiliar->proximoFila->numero != primeiroAuxiliar->numero) {
                            segundoAuxiliar = primeiroAuxiliar->proximoFila;
                            primeiroAuxiliar->proximoFila = primeiroAuxiliar->proximoFila->proximoFila;
                        }
                        ultimoUrgencia = primeiroAuxiliar->proximoFila;
                        segundoAuxiliar->proximoFila = ultimoUrgencia->proximoFila;
                        ultimoUrgencia->proximoFila = primeiroFila;
                        primeiroFila = ultimoUrgencia;
                        free(primeiroAuxiliar);
                        primeiroAuxiliar = NULL;
                    }
                }
                else {
                    segundoAuxiliar = primeiroFila;
                    primeiroAuxiliar->proximoFila = primeiroFila->proximoFila;
                    while (primeiroAuxiliar->proximoFila->numero != primeiroAuxiliar->numero) {
                        segundoAuxiliar = primeiroAuxiliar->proximoFila;
                        primeiroAuxiliar->proximoFila = primeiroAuxiliar->proximoFila->proximoFila;
                    }
                    segundoAuxiliar->proximoFila = primeiroAuxiliar->proximoFila->proximoFila;
                    primeiroAuxiliar->proximoFila->proximoFila = ultimoUrgencia->proximoFila;
                    ultimoUrgencia->proximoFila = primeiroAuxiliar->proximoFila;
                    ultimoUrgencia = primeiroAuxiliar->proximoFila;
                    free(primeiroAuxiliar);
                    primeiroAuxiliar = NULL;
                    segundoAuxiliar = NULL;
                }

            }
            else if (strcmp(primeiroAuxiliar->menssagem, "FIM") == 0) {
                lerArquivo = false;
                free(primeiroAuxiliar);
                primeiroAuxiliar = NULL;
                printf("\n\nSituacao da fila\n\n");
                primeiroAuxiliar = primeiroFila;
                while (primeiroAuxiliar != NULL) {
                    primeiroAuxiliar = primeiroAuxiliar->proximoFila;
                    printf("%04d    %s", primeiroFila->numero, primeiroFila->localPartida);
                    free(primeiroFila);
                    primeiroFila = primeiroAuxiliar;
                }
            }
        }
    }

    fclose(Entrada);
    return 0;
}