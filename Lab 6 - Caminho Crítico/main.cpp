/* Matheus Felipe Ramos Borges             */
/* Turma 4                                 */
/* Exercício 6: Caminho Critico            */
/*                                         */
/* Programa compilado com CLion 2024.2.0.1 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct noh{
    char tarefa;                    //Nome da tarefa
    char descricao[32];             //Descricao da tarefa
    int tempo;                      //Tempo que a tarefa demora para ser realizada
    int numeroTarefa;               //A posição da tarefa na lista de tarefas
    bool inicializado = false;      //Marcador de inicializado para nao acessar lixo no grafo
    bool descoberto = false;        //Marcador de descoberto para a busca no grafo
    bool finalizado = false;        //Marcador de finalizado para a busca no grafo
};

struct Grafo{
    noh listaTarefas[53];            //Lista de tarefas do grafo, nao utilizar a posicao 0
    int matrizAdjacencias[53][53];   //Matriz de adjacencias do grafo, nao utilizar a posicao 0
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

/**
 * Funcao para fazer a busca em profundidade em pre-ordem para determinar se ha ciclo
 * @param grafo
 * @param i posicao na lista de taredas
 * @param grafoCiclico booleana para determinar se foi encontrado ciclo
 * @param pilha
 * @param inicioCiclo
 */
void GrafoCiclicoDFS (Grafo *grafo, int i, bool *grafoCiclico, Pilha *pilha, int *inicioCiclo) {
    if (!(*inicioCiclo)) {
        int j;

        grafo->listaTarefas[i].descoberto = true;
        Empilhar(pilha, grafo->listaTarefas[i]);

        for (j = 1; j < 53; j++) {
            if (grafo->matrizAdjacencias[i][j] == 1 && grafo->listaTarefas[j].inicializado) {

                /**
                 * Caso seja encontrado um noh descoberto e nao terminado finalizar a recurssao e indicar ciclo
                 */
                if (grafo->listaTarefas[j].descoberto && !grafo->listaTarefas[j].finalizado) {
                    *grafoCiclico = true;
                    *inicioCiclo = j;
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
}

/**
 * Funcao travessia da analise do grafo ciclico
 * @param grafo
 * @param grafoCiclico booleana que indica se o grafo e ou nao ciclico
 * @param pilha
 * @param inicioCiclo posicao do incio do ciclo na lista de tarefas
 */
void TravessiaGrafoCiclicoDFS (Grafo *grafo, bool *grafoCiclico, Pilha *pilha, int *inicioCiclo) {
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

/**
 * Funcao para printar o ciclo no arquivo de saida
 * @param pilha
 * @param inicioCiclo
 * @param Saida
 */
void PrintarCiclo(Pilha pilha, int inicioCiclo, FILE *Saida) {
    Pilha pilhaAux;
    InicializarPilha(&pilhaAux);
    bool passsarParaAuxiliar = true;

    while (passsarParaAuxiliar) {
        Empilhar(&pilhaAux, TopoPilha(pilha));
        if (TopoPilha(pilha).numeroTarefa == inicioCiclo)
            passsarParaAuxiliar = false;
        Desempilhar(&pilha);
    }

    while (!PilhaVazia(pilhaAux)) {
        fprintf(Saida, "%c ", TopoPilha(pilhaAux).tarefa);
        Desempilhar(&pilhaAux);
    }
}

/**
 * Funcao para fazer a busca em profundidade em pos-ordem para determinar se ha ciclo
 * @param grafo
 * @param i posicao na lista de taredas
 * @param pilha
 */
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

/**
 * Funcao travessia da ordem topologica
 * @param grafo
 * @param pilha
 */
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

/**
 * Funcao para printar a ordem topologica no arquivo de saida
 * @param pilha
 * @param Saida
 */
void PrintarOrdemTopologica (Pilha pilha, FILE *Saida) {
    while (!PilhaVazia(pilha)) {
        fprintf(Saida, "%c ", TopoPilha(pilha).tarefa);
        Desempilhar(&pilha);
    }
}

/**
 *
 * @param grafo
 * @param pilha
 * @param TMT tempo minimo de realizacao de uma tarefa
 * @param predecessor guardar o noh predecessor
 * @param ultimaTarefa guardar a ultima tarefa do caminho critico
 */
void CaminhoCritico (Grafo *grafo, Pilha *pilha, int *TMT, int *predecessor, int *ultimaTarefa) {
    int i;
    int maiorAntecessor;

    for (i = 0; i < 53; ++i)
        TMT[i] = 0;

    *ultimaTarefa = 0;

    while (!PilhaVazia(*pilha)) {
        maiorAntecessor = 0;
        for (i = 1; i < 53; ++i) {
            if (grafo->matrizAdjacencias[i][TopoPilha(*pilha).numeroTarefa] == 1 && TMT[i] > TMT[maiorAntecessor])
                maiorAntecessor = i;
        }

        TMT[TopoPilha(*pilha).numeroTarefa] = TopoPilha(*pilha).tempo + TMT[maiorAntecessor];
        predecessor[TopoPilha(*pilha).numeroTarefa] = maiorAntecessor;

        if (TMT[TopoPilha(*pilha).numeroTarefa] > TMT[*ultimaTarefa])
            *ultimaTarefa = TopoPilha(*pilha).numeroTarefa;

        Desempilhar(pilha);
    }
}

/**
 * Funcao para printar o caminho critico no arquivo de saida
 * @param grafo
 * @param predecessor
 * @param ultimaTarefa
 * @param Saida
 */
void PrintarCaminhoCritico (Grafo *grafo, int *predecessor, int ultimaTarefa, FILE *Saida) {

    Pilha pilha;
    int i = ultimaTarefa;

    InicializarPilha(&pilha);

    while (i != 0) {
        Empilhar(&pilha, grafo->listaTarefas[i]);
        i = predecessor[i];
    }

    while (!PilhaVazia(pilha)) {
        fprintf(Saida, "  %c   %s%2d\n", TopoPilha(pilha).tarefa, TopoPilha(pilha).descricao, TopoPilha(pilha).tempo);
        Desempilhar(&pilha);
    }
}


int main() {

    Grafo grafo;
    char linha[70];              //Variavel para pular linhas desnecessarias no arquivo de entrada
    char aux;                    //Variavel auxiliar para a leitura de variaveis
    int i, j;
    bool grafoCiclico = false;   //Booleana para identificar se ha ciclo
    int inicioCiclo;             //Caso haja um ciclo, guardar a posicao da tarefa onde iniciou o ciclo
    int TMT[53];                 //Tempo minimo para a realizacao de uma tarefa
    int predecessor[53];         //Guardar o predecessor na ordem topologica
    int ultimaTarefa;            //Guardar a posicao da ultima tarefa no caminho critico
    bool lerArquivo = true;
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
     * Leitura dos dados
     */
    for (int j = 0; j < 53; ++j) {
        for (int k = 0; k < 53; ++k) {
            grafo.matrizAdjacencias[j][k] = 0;
        }
    }

    while (lerArquivo) {
        fgets(linha, 2, Entrada);
        fscanf(Entrada, " %c", &aux);
        fgets(linha, 4, Entrada);

        if (aux == '-') {
            lerArquivo = false;
        } else {
            if (aux >= 65 && aux <= 90) {
                i = aux % 64;
            } else if (aux >= 97 && aux <= 122) {
                i = aux % 96 + 26;
            }

            grafo.listaTarefas[i].tarefa = aux;
            grafo.listaTarefas[i].inicializado = true;
            grafo.listaTarefas[i].numeroTarefa = i;

            fgets(grafo.listaTarefas[i].descricao, 32, Entrada);
            fscanf(Entrada, " %d", &grafo.listaTarefas[i].tempo);
            fgets(linha, 5, Entrada);
            fscanf(Entrada, " %c", &aux);

            if (aux >= 65 && aux <= 90) {
                j = aux % 64;
                grafo.matrizAdjacencias[j][i] = 1;
            } else if (aux >= 97 && aux <= 122) {
                j = aux % 96 + 26;
                grafo.matrizAdjacencias[j][i] = 1;
            }
            fscanf(Entrada, "%c", &aux);
            while (aux != '\n') {
                fscanf(Entrada, "%c", &aux);
                if (aux >= 65 && aux <= 90) {
                    j = aux % 64;
                    grafo.matrizAdjacencias[j][i] = 1;
                } else if (aux >= 97 && aux <= 122) {
                    j = aux % 96 + 26;
                    grafo.matrizAdjacencias[j][i] = 1;
                }
            }
        }
    }

    fprintf(Saida, "Exemplo de arquivo de saida\n"
                       "PERT/CPM\n"
                       "Pode escrever qualquer coisa no cabecalho.\n"
                       "Coloque exatamente 5 linhas antes do traco.\n"
                       "\n"
                       "------------------------------------------------------------\n\n");

    InicializarPilha(&pilha);

    TravessiaGrafoCiclicoDFS(&grafo, &grafoCiclico, &pilha, &inicioCiclo);

    if (grafoCiclico) {

        fprintf(Saida, "Ciclo:\n\n");

        PrintarCiclo(pilha, inicioCiclo, Saida);

        fprintf(Saida, "\n\nE impossivel encontrar o caminho critico, pois o grafo nao e aciclico\n");

    } else {

        TravessiaOrdemTopologicaDFS(&grafo, &pilha);

        fprintf(Saida, "UMA ORDENACAO TOPOLOGICA:\n\n");

        PrintarOrdemTopologica(pilha, Saida);

        fprintf(Saida, "\n\n------------------------------------------------------------\n\n");

        CaminhoCritico(&grafo, &pilha, TMT, predecessor, &ultimaTarefa);

        fprintf(Saida, "TEMPO MINIMO PARA O PROJETO:  %d semanas", TMT[ultimaTarefa]);

        fprintf(Saida, "\n\n------------------------------------------------------------\n"
                "\n"
                "CAMINHO CRITICO:\n"
                "\n"
                "TAREFA        DESCRICAO           DURACAO\n\n");

        PrintarCaminhoCritico(&grafo, predecessor, ultimaTarefa, Saida);

    }

    fprintf(Saida, "\n"
                   "------------------------------------------------------------");

    fclose(Entrada);
    fclose(Saida);
    return 0;
}