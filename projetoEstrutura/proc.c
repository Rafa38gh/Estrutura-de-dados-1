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

    //=================================================================================
    // Filas principais
    Fila *f = CriaFila();       // Fila principal de pouso
    Fila *e = CriaFila();       // Fila de pousos de emergência
    Fila *u = CriaFila();       // Fila de aviões que pousaram

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
        printf("\n\n\t\t == MENU PRINCIPAL ==");
        printf("\n\n\t 1. Cadastrar novo voo");
        printf("\n\t 2. Autorizar pouso");
        printf("\n\t 3. Imprimir lista de espera");
        printf("\n\t 4. Imprimir lista de pouso");
        printf("\n\t 0. Sair do programa");

        printf("\n\n Escolha uma das opcoes acima: ");
        scanf("%d", &input);

        switch(input)
        {
            case 1:
                CadastrarVoo(f, e, horarioGlobal);
                break;

            case 2:
                AutorizarPouso(f, e, u, horarioGlobal);
                break;

            case 3:
                system("cls");
                printf("\n\n == FILA DE EMERGÊNCIA ==");
                ImprimeFila(e, 0);
                printf("\n\n == FILA PRINCIPAL ==");
                ImprimeFila(f, 0);
                break;

            case 4:
                ImprimeFila(u, 1);
                break;

            case 0:
                printf("\n\n\t\t Encerrando programa...");
                LiberaFila(f);
                LiberaFila(e);
                LiberaFila(u);
                break;

            default:
                printf("\n\n\t\t ERRO: Comando invalido inserido...");
                break;
        }
    } while (input != 0);


    return 0;
}

void CadastrarVoo(Fila *f, Fila *e, Tempo *horarioGlobal)
{
    // Dados do vôo
    char codigo[4];
    int numPass;
    Tempo *horario;

    // Variável auxiliar
    int aux;

    // Input do usuário
    int input;

    // Chance de vôo emergencial
    int emergencia = 0;

    system("cls");
    printf("\n\t == CADASTRO DE VOOS ==");
    printf("\n HORA ATUAL %d:%d", horarioGlobal->hora, horarioGlobal->minutos);

    printf("\n\t\t Quantos voos deseja inserir: ");
    scanf("%d", &input);

    for(input; input > 0; input--)
    {
        // Código do vôo
        for(int i = 0; i < 4; i++)
        {
            aux = rand() % 2;

            if(aux == 0)
            {
                codigo[i] = '0' + rand() % 10;

            } else
            {
                codigo[i] = 'A' + rand() % 26;
            }
        }

        horario = (Tempo*) malloc(sizeof(Tempo*));

        if(horario == NULL)       // Verifica se foi possível alocar memória para o horário
        {
            printf("\n\t\t ERRO: Falha ao alocar memoria para o horario do voo");
            exit(0);
        }

        numPass = rand() % 151 + 50;
        horario->hora = rand() % 23;
        horario->minutos = rand() % 59;

        emergencia = rand() % 100;      // Haverá 20% de chance do vôo ser emergencial

        if(emergencia > 20)
        {
            InsereFila(f, codigo, numPass, horario, 1);

        } else
        {
            InsereFila(e, codigo, numPass, horario, -1);
        }
    }
}

void AutorizarPouso(Fila *f, Fila *e, Fila *u, Tempo *horarioGlobal)
{
    system("cls");
    Nos *aux = f->ini;
    Nos *aux2 = e->ini;
    Nos *aux3;

    // Imprime os próximos 3 vôos a serem autorizados
    printf("\n HORA ATUAL %d:%d", horarioGlobal->hora, horarioGlobal->minutos);
    printf("\n == PROXIMOS POUSOS ==");
    for(int i = 0; i < 3; i++)
    {
        // Verifica se há pousos de emergência
        if(!VaziaFila(e)&& aux2 != NULL)
        {
            ImprimeNo(aux2);
            aux2 = aux2->prox;

        } else if(!VaziaFila(f) && aux != NULL)
        {
            ImprimeNo(aux);
            aux = aux->prox;
        }
    }

    // Autorizando pouso
    if(!VaziaFila(e))
    {
        aux3 = RetiraFila(e);

    } else if(!VaziaFila(f))
    {
        aux3 = RetiraFila(f);
    }

    InsereFila(u, aux3->codigo, aux3->numPass, aux3->horario, aux3->checkHora);
    free(aux3->horario);
    free(aux3);
}
