/* Matheus Felipe Ramos Borges             */
/* Turma 4                                 */
/* Exercício 3: Ordenacao                  */
/*                                         */
/* Programa compilado com CLion 2024.2.0.1 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {

    FILE *Entrada;
    FILE *SaidaBubble;
    FILE *SaidaMerge;
    FILE *SaidaQuick;
    Entrada = fopen("entrada3.txt", "r");
    SaidaBubble = fopen("Lab3_Matheus_Felipe_Ramos_Borges_bubble.txt", "w");
    SaidaMerge = fopen("Lab3_Matheus_Felipe_Ramos_Borges_merge.txt", "w");
    SaidaQuick = fopen("Lab3_Matheus_Felipe_Ramos_Borges_quick.txt", "w");


    fclose(Entrada);
    fclose(SaidaBubble);
    fclose(SaidaMerge);
    fclose(SaidaQuick);
    return 0;
}
