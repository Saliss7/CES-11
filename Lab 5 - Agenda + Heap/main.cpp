/* Matheus Felipe Ramos Borges             */
/* Turma 4                                 */
/* Exercício 5: Agenda + heap              */
/*                                         */
/* Programa compilado com CLion 2024.2.0.1 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*--------------------------------------------------*/
struct TipoTarefa
{
    char descricao [42];
    int  prioridade;
};
/*--------------------------------------------------*/
// TAD fila de prioridade
struct TipoAgenda
{
    TipoTarefa * vet;  // o vetor
    int quant,         // quantidade de elementos
         MAX;           // quantidade máxima possível de elementos (será lida do arquivo de entrada)
};
/*--------------------------------------------------*/
void Inicializar (TipoAgenda * Agd, int numero_maximo)
{
    // Inicializar a Fila
    Agd->quant = 0;
    Agd->MAX = numero_maximo;
    Agd->vet = (TipoTarefa *) malloc((numero_maximo + 1)*sizeof(TipoTarefa));
}
/*--------------------------------------------------*/
void Finalizar (TipoAgenda * Agd)
{
    // Finalizar o ponteiro
    free(Agd->vet);
}
/*--------------------------------------------------*/
bool FilaVazia (TipoAgenda Agd)
{
    // Se a fila esta vazia retornar true, se nao retornar false
    if (Agd.quant == 0)
    {
        return true;
    } else
    {
        return false;
    }
}
/*--------------------------------------------------*/
bool FilaCheia (TipoAgenda Agd)
{
    // Se a fila esta cheia retornar true, se nao retornar false
    if (Agd.quant == Agd.MAX)
    {
        return true;
    } else
    {
        return false;
    }
}
/*--------------------------------------------------*/
void Inserir (TipoAgenda * Agd, TipoTarefa Tar)
{
    int i;
    TipoTarefa aux;
    Agd->quant++;
    i = Agd->quant;
    Agd->vet[Agd->quant] = Tar;
    // Condicao para nao ser a raiz e ser maior que o pai para trocar
    while (i > 1 && Agd->vet[i].prioridade > Agd->vet[i/2].prioridade)
    {
        aux = Agd->vet[i];
        Agd->vet[i] = Agd->vet[i/2];
        Agd->vet[i/2] = aux;
        i = i/2;
    }
}
/*--------------------------------------------------*/
void RemoverMax (TipoAgenda * Agd)
{
    int i = 1;
    bool trocou = true;
    TipoTarefa aux;
    Agd->vet[1] = Agd->vet[Agd->quant];
    Agd->quant--;
    // Condicao para ter filho esquerdo e ter acontecido alguma troca na heap
    while (i <= Agd->quant/2 && trocou)
    {
        // Condicao para ter o filho direito
        if (2*i + 1 <= Agd->quant)
        {
            // Caso seja menor que os dois conferir o maior entre os filhos e trocar. Se for maior que apenas um, trocar com ele
            if (Agd->vet[i].prioridade < Agd->vet[2*i].prioridade && Agd->vet[i].prioridade < Agd->vet[2*i + 1].prioridade)
            {
                if (Agd->vet[2*i].prioridade > Agd->vet[2*i + 1].prioridade) {
                    aux = Agd->vet[i];
                    Agd->vet[i] = Agd->vet[2*i];
                    Agd->vet[2*i] = aux;
                    i = 2*i;
                } else
                {
                    aux = Agd->vet[i];
                    Agd->vet[i] = Agd->vet[2*i + 1];
                    Agd->vet[2*i + 1] = aux;
                    i = 2*i + 1;
                }
                // Caso seja menor que apenas um
            } else if (Agd->vet[i].prioridade < Agd->vet[2*i].prioridade)
            {
                aux = Agd->vet[i];
                Agd->vet[i] = Agd->vet[2*i];
                Agd->vet[2*i] = aux;
                i = 2*i;
            } else if (Agd->vet[i].prioridade < Agd->vet[2*i + 1].prioridade)
            {
                aux = Agd->vet[i];
                Agd->vet[i] = Agd->vet[2*i + 1];
                Agd->vet[2*i + 1] = aux;
                i = 2*i + 1;
                // Caso nao houve trocas acabar o loop
            } else
            {
                trocou = false;
            }
            // Caso so tenha filho esquerdo
        } else
        {
            // se for menor trocar se nao acabar o loop
            if (Agd->vet[i].prioridade < Agd->vet[2*i].prioridade) {
                aux = Agd->vet[i];
                Agd->vet[i] = Agd->vet[2 * i];
                Agd->vet[2*i] = aux;
                i = 2*i;
            } else
            {
                trocou = false;
            }
        }
    }
}
/*--------------------------------------------------*/
TipoTarefa ConsultarMax (TipoAgenda Agd)
{
    // Retornar o maior valor (primeiro elemento do vetor)
    return Agd.vet[1];
}
/*--------------------------------------------------*/
int main()
{
    FILE * ent;           // arquivo de entrada
    FILE * sai;           // arquivo de saída
    TipoAgenda A;         // Agenda = fila de prioridade
    TipoTarefa T;         // Cada tarefa na agenda
    int  i;
    int  tamanho_max;     // tamanho maximo da agenda
    char comando [8];     // NOVA, PROXIMA ou FIM
    char linha  [72];     // para pular linhas do cabecalho

    // abrir arquivos
    ent = fopen ("entrada5.txt", "r");
    sai = fopen ("Lab5_Matheus_Felipe_Ramos_Borges.txt", "w");
    // pular 5 linhas iniciais da entrada
    for (i=1; i<=5; i++)
        fgets (linha, 72, ent);
    // ler tamanho maximo e inicializar agenda
    fscanf (ent, "%d", & tamanho_max);
    Inicializar   (&A,   tamanho_max);
    // pular mais 3 linhas da entrada
    for (i=1; i<=3; i++)
        fgets (linha, 72, ent);
    // escrever 5 linhas iniciais na saída
    fprintf(sai, "linha 1: Exemplo de arquivo de saida.             \n");
    fprintf(sai, "linha 2:                                          \n");
    fprintf(sai, "linha 3: Nestas 5 linhas, voce pode escrever      \n");
    fprintf(sai, "linha 4: quaisquer frases, livremente  :-)        \n");
    fprintf(sai, "linha 5:                                          \n");
    fprintf(sai, "--------------------------------------------------\n");
    fprintf(sai, "RESPOSTAS DAS CONSULTAS                           \n");
    fprintf(sai, "--------------------------------------------------\n");
    // Processar cada linha da entrada
    do
    {
        fscanf (ent, " %s ", & comando);
        // comando para Inserir
        if (strcmp (comando, "NOVA")==0)
        {
            fscanf (ent, " %d ", & T.prioridade);
            fgets  (T.descricao, 72, ent);
            if (FilaCheia (A))
                fprintf(sai, "ERRO     Agenda cheia. Impossivel inserir. \n");
            else Inserir (&A, T);
        }
        // comando para Remover
        if (strcmp (comando, "PROXIMA")==0)
            if (FilaVazia (A))
                fprintf(sai, "AVISO    Nao ha tarefas na agenda  :-) \n");
            else
            {
                T = ConsultarMax (A);
                fprintf(sai, "%2d       %s", T.prioridade, T.descricao);
                RemoverMax (&A);
            }
        // até chegar comando "FIM"
    } while (strcmp (comando, "FIM")!=0);
    // Desfazer a fila e imprimir todas as tarefas remanescentes
    fprintf(sai,"\n--------------------------------------------------\n");
    fprintf(sai,  "FICA PARA O DIA SEGUINTE                          \n");
    fprintf(sai,  "--------------------------------------------------\n");
    if (FilaVazia (A))
        fprintf(sai, "Agenda vazia! Nao restam tarefas para o dia seguinte. \n");
    while (! FilaVazia (A))
    {
        T = ConsultarMax (A);
        fprintf(sai, "%2d       %s", T.prioridade, T.descricao);
        RemoverMax (&A);
    }
    // Procedimentos finais
    Finalizar (&A);
    fclose (ent);
    fclose (sai);
    return 0;
}