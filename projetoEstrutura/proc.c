#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include "FILA.h"

int main()
{
    system("cls");
    setlocale(LC_ALL, "Portuguese");

    // Seed
    int seed;

    // Horario global
    Tempo *horarioGlobal;
    int horaGlobal, minutoGlobal;

    // Dados do vôo
    char codigo[4];
    int numPass;
    Tempo *horario;

    // Variáveis para inserção do horario
    int hora, minutos;

    //=================================================================================
    // Inserção da seed
    printf("\n\n\t INSIRA O VALOR DA SEED: ");
    scanf("%d", &seed);
    srand(seed);

    //=================================================================================
    // Inserção do horário global
    horaGlobal = rand() % 23;
    minutoGlobal = rand() % 59;

    horarioGlobal->hora = horaGlobal;
    horarioGlobal->minutos = minutoGlobal;

    printf("\n HORA ATUAL %d:%d", horaGlobal, minutoGlobal);

    return 0;
}
