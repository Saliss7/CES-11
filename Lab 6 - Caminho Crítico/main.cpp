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
    bool existe[53];                 //Existencia do noh
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
void inicializarPilha(Pilha *pilha) {
    pilha->MAX = 52;
    pilha->topo = 0;
    pilha->elementos = (noh *) malloc((pilha->MAX + 1) * sizeof(noh));
}

/**
 * Verificar se a pilha esta vazia
 * @param pilha
 * @return true se esta vazia e false se nao esta
 */
bool pilhaVazia(Pilha *pilha) {
    if (pilha->topo == 0) {
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
bool pilhaCheia(Pilha *pilha) {
    if (pilha->topo == pilha->MAX) {
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
void empilhar(Pilha *pilha, noh elemento) {
    pilha->topo++;
    pilha->elementos[pilha->topo] = elemento;
}

/**
 * Retirar um elemento do topo da pilha
 * @param pilha
 * @param elemento
 */
void desempilhar(Pilha *pilha, noh *elemento) {
    pilha->topo--;
}

/**
 * Consultar o elemento do topo da pilha sem remove-lo
 * @param pilha
 * @return retorna o elemento do topo da pilha
 */
noh topoPilha(Pilha *pilha) {
    return pilha->elementos[pilha->topo];
}


int main() {

    Grafo grafo;
    char linha[70];
    int i;
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


    fclose(Entrada);
    fclose(Saida);
    return 0;
}