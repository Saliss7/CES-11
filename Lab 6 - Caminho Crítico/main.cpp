/* Matheus Felipe Ramos Borges             */
/* Turma 4                                 */
/* Exercício 6: Caminho Critico            */
/*                                         */
/* Programa compilado com CLion 2024.2.0.1 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct noh{
    char tarefa;
    char descricao[32];
    int tempo;
    bool inicializado = false;
    bool descoberto = false;
    bool finalizado = false;
};

struct Grafo{
    noh listaTarefas[53];            //Nao utilizarei a posicao 0
    int matrizAdjacencias[53][53];   //Nao utilizarei a posicao 0
};

/**
 * Tipo Abstrato de Dados Pilha
 */
struct Pilha{
    noh *elementos;
    int MAX;
    int topo;
};

/**
 * Inicializar a pilha
 * @param pilha
 */
void InicializarPilha(Pilha *pilha) {
    pilha->MAX = 52;
    pilha->topo = 0;
    pilha->elementos = (noh *) malloc((pilha->MAX + 1) * sizeof(noh));
}

/**
 * Verificar se a pilha esta vazia
 * @param pilha
 * @return true se esta vazia e false se nao esta
 */
bool PilhaVazia(Pilha pilha) {
    if (pilha.topo == 0) {
        return true;
    } else {
        return false;
    }
}

/**
 * Verificar se a pilha esta cheia
 * @param pilha
 * @return true se esta cheia e false se nao esta
 */
bool PilhaCheia(Pilha pilha) {
    if (pilha.topo == pilha.MAX) {
        return true;
    } else {
        return false;
    }
}

/**
 * Coloca um elemento no topo da pilha
 * @param pilha
 * @param elemento
 */
void Empilhar(Pilha *pilha, noh elemento) {
    pilha->topo++;
    pilha->elementos[pilha->topo] = elemento;
}

/**
 * Retirar um elemento do topo da pilha
 * @param pilha
 * @param elemento
 */
void Desempilhar(Pilha *pilha) {
    pilha->topo--;
}

/**
 * Consultar o elemento do topo da pilha sem remove-lo
 * @param pilha
 * @return retorna o elemento do topo da pilha
 */
noh TopoPilha(Pilha pilha) {
    return pilha.elementos[pilha.topo];
}

void GrafoCiclicoDFS (Grafo *grafo, int i, bool *grafoCiclico, Pilha *pilha, char *inicioCiclo) {
    int j;

    grafo->listaTarefas[i].descoberto = true;
    Empilhar(pilha, grafo->listaTarefas[i]);

    for (j = 1; j < 53; j++) {
        if (grafo->matrizAdjacencias[i][j] == 1 && grafo->listaTarefas[j].inicializado) {
            if (grafo->listaTarefas[j].descoberto && !grafo->listaTarefas[j].finalizado) {
                *grafoCiclico = true;
                *inicioCiclo = grafo->listaTarefas[j].tarefa;
                return;
            } else if (!grafo->listaTarefas[j].descoberto) {
                GrafoCiclicoDFS(grafo, j, grafoCiclico, pilha, inicioCiclo);
                if (*grafoCiclico) {
                    return;
                }
            }
        }
    }

    grafo->listaTarefas[i].finalizado = true;
    Desempilhar(pilha);
}

void TravessiaGrafoCiclicoDFS (Grafo *grafo, bool *grafoCiclico, Pilha *pilha, char *inicioCiclo) {
    int i;

    /**
     * Inicializando todos false
     */
    for (i = 1; i < 53; i++){
        if (grafo->listaTarefas[i].inicializado) {
            grafo->listaTarefas[i].descoberto = false;
            grafo->listaTarefas[i].finalizado = false;
        }
    }

    /**
     * Enquanto ha nos nao descobertos chamar a funcao GrafoCiclicoDFS
     */
    for (i = 1; i < 53; i++) {
        if (grafo->listaTarefas[i].inicializado && !grafo->listaTarefas[i].descoberto) {
            GrafoCiclicoDFS(grafo, i, grafoCiclico, pilha, inicioCiclo);
        }
    }
}

void OrdemTopologicaDFS (Grafo *grafo, int i, Pilha *pilha) {
    int j;

    grafo->listaTarefas[i].descoberto = true;

    for (j = 1; j < 53; j++) {
        if (grafo->matrizAdjacencias[i][j] == 1 && grafo->listaTarefas[j].inicializado && !grafo->listaTarefas[j].descoberto) {
            OrdemTopologicaDFS(grafo, j, pilha);
        }
    }

    grafo->listaTarefas[i].finalizado = true;
    Empilhar(pilha, grafo->listaTarefas[i]);
}

void TravessiaOrdemTopologicaDFS (Grafo *grafo, Pilha *pilha){
    int i;

    /**
     * Inicializando todos false
     */
    for (i = 1; i < 53; i++){
        if (grafo->listaTarefas[i].inicializado) {
            grafo->listaTarefas[i].descoberto = false;
            grafo->listaTarefas[i].finalizado = false;
        }
    }

    /**
     * Enquanto ha nos nao descobertos chamar a funcao OrdemTopologicaDFS
     */
    for (i = 1; i < 53; i++) {
        if (grafo->listaTarefas[i].inicializado && !grafo->listaTarefas[i].descoberto) {
            OrdemTopologicaDFS(grafo, i, pilha);
        }
    }
}

int main() {

    Grafo grafo;
    char linha[70];
    int i;
    bool grafoCiclico = false;
    char inicioCiclo;
    Pilha pilha;
    FILE *Entrada;
    FILE *Saida;
    Entrada = fopen("entrada6.txt", "r");
    Saida = fopen("Lab6_Matheus_Felipe_Ramos_Borges.txt", "w");

    /**
     * Pular as 7 primeiras linhas do arquivo de entrada
     */
    for (i = 0; i < 7; i++) {
        fgets(linha, sizeof(linha), Entrada);
    }

    /**
     * Inicializacao temporario do grafo
     */

    for (int j = 0; j < 53; ++j) {
        for (int k = 0; k < 53; ++k) {
            grafo.matrizAdjacencias[j][k] = 0;
        }
    }

    grafo.listaTarefas[1].inicializado = true;
    grafo.listaTarefas[1].tarefa = 'A';
    grafo.matrizAdjacencias[1][2] = 1;
    grafo.matrizAdjacencias[1][6] = 1;

    grafo.listaTarefas[2].inicializado = true;
    grafo.listaTarefas[2].tarefa = 'B';
    grafo.matrizAdjacencias[2][3] = 1;

    grafo.listaTarefas[3].inicializado = true;
    grafo.listaTarefas[3].tarefa = 'C';
    grafo.matrizAdjacencias[3][4] = 1;

    grafo.listaTarefas[4].inicializado = true;
    grafo.listaTarefas[4].tarefa = 'D';
    grafo.matrizAdjacencias[4][5] = 1;

    grafo.listaTarefas[5].inicializado = true;
    grafo.listaTarefas[5].tarefa = 'E';
    grafo.matrizAdjacencias[5][3] = 1;

    grafo.listaTarefas[6].inicializado = true;
    grafo.listaTarefas[6].tarefa = 'F';

    InicializarPilha(&pilha);

    travessiaGrafoCiclicoDFS (&grafo, &grafoCiclico, &pilha, &inicioCiclo);

    if (grafoCiclico) {
        printf("E ciclico\n");
        while (inicioCiclo != TopoPilha(pilha).tarefa) {
            printf("%c ", TopoPilha(pilha).tarefa);
            Desempilhar(&pilha);
        }
        printf("%c ", inicioCiclo);
    } else {
        TravessiaOrdemTopologicaDFS(&grafo, &pilha);
        while (!PilhaVazia(pilha)) {
            printf("%c ", TopoPilha(pilha).tarefa);
            Desempilhar(&pilha);
        }
    }

    fclose(Entrada);
    fclose(Saida);
    return 0;
}