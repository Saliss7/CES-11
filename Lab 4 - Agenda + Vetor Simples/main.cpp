/* Matheus Felipe Ramos Borges             */
/* Turma 4                                 */
/* Exercício 4: Agenda + Vetor Simples     */
/*                                         */
/* Programa compilado com CLion 2024.2.0.1 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Struct que guarda as informacoes sobre as tarefas
 */
struct Tarefa {
    char descricao[40];
    int importancia;
};

/**
 * Struct que guarda as informacoes sobre a agenda
 */
struct Agenda {
    int maximoElementos;
    int quantidade;
    Tarefa *vetor;
};


/**
 * Funcao para inserir uma nova tarefa na agenda
 */
void Inserir(Tarefa tarefa, Agenda *agenda) {
    int posicao;
    int esquerda, media, direita;
    esquerda = 0;
    direita = agenda->quantidade + 1;
    while (esquerda < direita - 1) {
        media = (esquerda + direita) / 2;
        if (agenda->vetor[media].importancia < tarefa.importancia) {
            esquerda = media;
        } else {
            direita = media;
        }
    }
    posicao = direita;

    for (int i = agenda->quantidade; i >= posicao; i--) {
        agenda->vetor[i + 1] = agenda->vetor[i];
    }
    agenda->vetor[posicao] = tarefa;
    agenda->quantidade++;
}

/**
 * Remover o maior elemento sem consultar
 */
void RemoverMax(Agenda *agenda) {
    agenda->quantidade--;
}

/**
 * Consultar o maior elemento sem remover
 */
Tarefa ConsultarMax(Agenda *agenda) {
    return agenda->vetor[agenda->quantidade];
}

/**
 * inicializar a agenda
 */
void Inicializar(Agenda *agenda, int maximoElementos) {
    agenda->maximoElementos = maximoElementos;
    agenda->quantidade = 0;
    agenda->vetor = (Tarefa *) malloc((maximoElementos + 1) * sizeof(Tarefa));
}

/**
 * Finalizar a agenda
 */
void Finalizar(Agenda *agenda) {
    free(agenda->vetor);
}

/**
 * Conferir se a fila esta vazia
 */
bool FilaVazia(Agenda *agenda) {
    if (agenda->quantidade == 0) {
        return true;
    } else {
        return false;
    }
}

/**
 * Conferir se a fila esta cheia
 */
bool FilaCheia(Agenda *agenda) {
    if (agenda->quantidade == agenda->maximoElementos) {
        return true;
    } else {
        return false;
    }
}

int main() {

    char tipoTarefa[10];
    bool lerArquivo = true;
    char linha[70];
    int maximoElementos;
    int i;
    struct Agenda agenda;
    struct Tarefa tarefa;
    FILE *Entrada;
    FILE *Saida;
    Entrada = fopen("entrada4.txt", "r");
    Saida = fopen("Lab4_Matheus_Felipe_Ramos_Borges.txt", "w");

    /**
     * Pular as 5 primeiras linhas do arquivo de entrada
     */
    for (i = 0; i < 5; i++) {
        fgets(linha, sizeof(linha), Entrada);
    }

    /**
     * Ler a quantidade maxima de elementos
     */
    fscanf(Entrada, "%d", &maximoElementos);

    /**
     * Pular as 3 proximas linhas do arquivo de entrada
     */
    for (i = 0; i < 3; i++) {
        fgets(linha, sizeof(linha), Entrada);
    }

    fprintf(Saida,
            "Agenda Eletronica - Exemplo de arquivo de saida.\nPode colocar qualquer texto no cabecalho.\nO cabecalho deve ter exatamente 5 linhas.\nNeste caso, a quinta linha estah em branco  :-)\n\n--------------------------------------------------\nRESPOSTAS DAS CONSULTAS\n--------------------------------------------------\n");

    /**
     * Inicializar a fila
     */
    Inicializar(&agenda, maximoElementos);

    while (lerArquivo) {

        /**
         * Ler o tipo da tarefa Fim, Proxima ou Nova
         */
        fscanf(Entrada, "%s", tipoTarefa);

        if (strcmp(tipoTarefa, "FIM") == 0) {
            lerArquivo = false;

            /**
             * Printar o fim da fila
             */
            fprintf(Saida,
                    "\n--------------------------------------------------\nFICA PARA O DIA SEGUINTE\n--------------------------------------------------\n");

            if (FilaVazia(&agenda)) {
                printf("Agenda vazia! Nao restam tarefas para o dia seguinte.");
            } else {
                while (!FilaVazia(&agenda)) {
                    fprintf(Saida, "%2d       %s", ConsultarMax(&agenda).importancia, ConsultarMax(&agenda).descricao);
                    RemoverMax(&agenda);
                }
            }
        } else if (strcmp(tipoTarefa, "PROXIMA") == 0) {

            /**
             * Printar a tarefa de maxima priopridade e remove-la
             */
            if (FilaVazia(&agenda)) {
                fprintf(Saida, "AVISO    Nao ha tarefas na agenda  :-)\n");
            } else {
                fprintf(Saida, "%2d       %s", ConsultarMax(&agenda).importancia, ConsultarMax(&agenda).descricao);
                RemoverMax(&agenda);
            }
        } else if (strcmp(tipoTarefa, "NOVA") == 0) {

            /**
             * Adicionar nova tarefa na fila
             */
            fscanf(Entrada, "%d ", &(tarefa.importancia));
            fgets(tarefa.descricao, sizeof(tarefa.descricao), Entrada);

            if (FilaCheia(&agenda)) {
                fprintf(Saida, "ERRO     Agenda cheia. Impossivel inserir.\n");
            } else {
                Inserir(tarefa, &agenda);
            }
        }
    }

    /**
     * Finalizar a agenda
     */
    Finalizar(&agenda);

    fclose(Entrada);
    fclose(Saida);
    return 0;
}
