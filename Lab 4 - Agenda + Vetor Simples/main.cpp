/* Matheus Felipe Ramos Borges             */
/* Turma 4                                 */
/* Exercício 4: Agenda + Vetor Simples     */
/*                                         */
/* Programa compilado com CLion 2024.2.0.1 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Tarefa {
    char descricao[40];
    int importancia;
};

struct Agenda {
    int maximoElementos;
    int quantidade;
    Tarefa *vetor;
};

void Inserir(Tarefa tarefa, Agenda *agenda) {
    int posicao;
    int esquerda, media, direita;
    esquerda = 0;
    direita = agenda->maximoElementos;
    while (esquerda < direita) {
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

void RemoverMax(Agenda *agenda) {
    for (int i = 1; i < agenda->quantidade; i++) {
        agenda->vetor[i] = agenda->vetor[i + 1];
    }
    agenda->quantidade--;
}

Tarefa ConsultarMax(Agenda *agenda) {
    return agenda->vetor[1];
}

void Inicializar(Agenda *agenda, int maximoElementos) {
    agenda->maximoElementos = maximoElementos;
    agenda->quantidade = 0;
    agenda->vetor = (Tarefa *) malloc((maximoElementos + 1) * sizeof(Tarefa));
}

void Finalizar(Agenda *agenda) {
    free(agenda->vetor);
}

bool FilaVazia(Agenda *agenda) {
    if (agenda->quantidade == 0) {
        return true;
    } else {
        return false;
    }
}

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
    Agenda agenda;
    Tarefa tarefa;
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

    fscanf(Entrada, "%d", &maximoElementos);

    /**
     * Pular as 3 proximas linhas do arquivo de entrada
     */
    for (i = 0; i < 3; i++) {
        fgets(linha, sizeof(linha), Entrada);
    }

    fprintf(Saida,
            "Agenda Eletronica - Exemplo de arquivo de saida.\nPode colocar qualquer texto no cabecalho.\nO cabecalho deve ter exatamente 5 linhas.\nNeste caso, a quinta linha estah em branco  :-)\n\n--------------------------------------------------\nRESPOSTAS DAS CONSULTAS\n--------------------------------------------------\n");

    Inicializar(&agenda, maximoElementos);

    while (lerArquivo) {

        fscanf(Entrada, "%s", tipoTarefa);
        if (strcmp(tipoTarefa, "FIM") == 0) {
            lerArquivo = false;
            fprintf(Saida,
                    "\n--------------------------------------------------\nFICA PARA O DIA SEGUINTE\n--------------------------------------------------\n");
            while (!FilaVazia(&agenda)) {
                fprintf(Saida, "%2d       %s", ConsultarMax(&agenda).importancia, ConsultarMax(&agenda).descricao);
                RemoverMax(&agenda);
            }
        } else if (strcmp(tipoTarefa, "PROXIMA") == 0) {
            if (FilaVazia(&agenda)) {
                fprintf(Saida, "AVISO    Nao ha tarefas na agenda  :-)");
            } else {
                fprintf(Saida, "%2d       %s", ConsultarMax(&agenda).importancia, ConsultarMax(&agenda).descricao);
                RemoverMax(&agenda);
            }
        } else if (strcmp(tipoTarefa, "NOVA") == 0) {
            fscanf(Entrada, "%d ", &(tarefa.importancia));
            fgets(tarefa.descricao, sizeof(tarefa.descricao), Entrada);

            if (FilaCheia(&agenda)) {
                fprintf(Saida, "ERRO     Agenda cheia. Impossivel inserir.");
            } else {
                Inserir(tarefa, &agenda);
            }
        }
    }

    Finalizar(&agenda);

    fclose(Entrada);
    fclose(Saida);
    return 0;
}
