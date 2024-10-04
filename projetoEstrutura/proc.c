#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <locale.h>
#include "FILA.h"

int main()
{
    system("cls");
    setlocale(LC_ALL, "Portuguese");

    // Input do usuário no menu;
    int input = 0;

    // Seed
    int seed;

    // Horario global
    Tempo *horarioGlobal;
    int horaGlobal, minutoGlobal;

    // Variáveis para inserção do horario
    int hora, minutos;

    //=================================================================================
    // Filas principais
    Fila *f = CriaFila();       // Fila principal de pouso
    Fila *e = CriaFila();       // Fila de pousos de emergência

    //=================================================================================
    // Inserção da seed
    printf("\n\n\t INSIRA O VALOR DA SEED: ");
    scanf("%d", &seed);
    srand(seed);

    //=================================================================================
    // Inserção do horário global
    horarioGlobal = (Tempo*) malloc(sizeof(Tempo*));
    horaGlobal = rand() % 23;
    minutoGlobal = rand() % 59;

    if(horarioGlobal == NULL)       // Verifica se foi possível alocar memória para o horário
    {
        printf("\n\t\t ERRO: Falha ao alocar memoria para o horario global");
        exit(0);
    }

    horarioGlobal->hora = horaGlobal;
    horarioGlobal->minutos = minutoGlobal;

    //=================================================================================
    // Menu principal
    do
    {
        printf("\n\t\t == MENU PRINCIPAL ==");
        printf("\n\n\t 1. Cadastrar novo voo");
        printf("\n\t 2. Imprimir lista de pouso");
        printf("\n\t 3. Sair do programa");

        printf("\n\n Escolha uma das opcoes acima: ");
        scanf("%d", &input);

        switch(input)
        {
            case 1:
                CadastrarVoo(f, horarioGlobal);
                break;
            
            case 2:
                ImprimeFila(f);
                break;
                
            case 3:
                printf("\n\n\t\t Encerrando programa...");
                break;
                
            default:
                printf("\n\n\t\t ERRO: Comando invalido inserido...");
                break;
        }
    } while (input != 3);
    

    return 0;
}

void CadastrarVoo(Fila *f, Tempo *horarioGlobal)
{
    // Dados do vôo
    char codigo[4];
    int numPass;
    Tempo *horario;

    // Input do usuário
    char input = 0;

    system("cls");
    printf("\n CADASTRO DE VOOS");
    printf("\n HORA ATUAL %d:%d", horarioGlobal->hora, horarioGlobal->minutos);

    do
    {
        printf("\n\n\t Insira o codigo do voo (max 4 caracteres): ");
        fflush(stdin);
        scanf("%s", &codigo);

        horario = (Tempo*) malloc(sizeof(Tempo*));
        numPass = rand() % 151 + 50;
        horario->hora = rand() % 23;
        horario->minutos = rand() % 59;

        if(horario == NULL)       // Verifica se foi possível alocar memória para o horário
    {
        printf("\n\t\t ERRO: Falha ao alocar memoria para o horario do voo");
        exit(0);
    }

        InsereFila(f, codigo, numPass, horario);

        fflush(stdin);
        printf("\n\n\t\t Deseja cadastrar um novo voo? (S/N): ");
        scanf(" %c", &input);

        input = toupper(input);

    } while (input == 'S');
}
