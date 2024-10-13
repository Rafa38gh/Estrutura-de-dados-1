#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <locale.h>
#include "FILA.h"

void CadastrarVoo(Fila *f, Fila *e, Tempo *horarioGlobal)
{
    // Dados do vôo
    char codigo[4];
    int numPass;

    Tempo *horario;

    // Aloca espaço para armazenar os horários
    horario = (Tempo*) malloc(sizeof(Tempo));
    if(horario == NULL)
    {
        printf("\nERRO: Espaço de memória insuficiente...");
        exit(1);
    }

    // Variável auxiliar
    int aux;

    // Input do usuário
    int input;

    // Chance de vôo emergencial
    int emergencia = 0;

    system("cls");
    printf("\n\t == CADASTRO DE VOOS ==");
    printf("\n HORA ATUAL %.2d:%.2d", horarioGlobal->hora, horarioGlobal->minutos);

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
    free(horario);
}

void AutorizarPouso(Fila *f, Fila *e, Fila *p, Tempo *horarioGlobal)
{
    system("cls");
    Nos *aux = f->ini;
    Nos *aux2 = e->ini;

    if(!VaziaFila(f) || !VaziaFila(e))
    {
        // Imprime os próximos 3 vôos a serem autorizados
        printf("\n HORA ATUAL %.2d:%.2d", horarioGlobal->hora, horarioGlobal->minutos);
        printf("\n == PROXIMOS POUSOS ==");

        // Imprime os 3 próximos voos
        for(int i = 0; i < 3; i++)
        {
            // Verifica se há pousos de emergência
            if(!VaziaFila(e) && aux2 != NULL)
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
            alteraHora(horarioGlobal, &f->ini);
            InsereFila(p, e->ini->codigo, e->ini->numPass, e->ini->horario, e->ini->checkHora);
            printf("\n\nRetirou voo de emergência: %.4s\n", e->ini->codigo);

            RetiraFila(e);

        } else if(!VaziaFila(f))
        {
            alteraHora(horarioGlobal, &f->ini);
            InsereFila(p, f->ini->codigo, f->ini->numPass, f->ini->horario, f->ini->checkHora);
            printf("\n\nRetirou voo: %.4s\n", f->ini->codigo);

            RetiraFila(f);
        }

    } else
    {
        printf("\n\n\t ERRO: Nenhum voo registrado no sistema...");
    }
}

void SimularPouso(Fila *f, Fila *e, Tempo *horarioGlobal)
{
    int minutos;      // tempo escolhido pelo usuário
    Nos *aux = e->ini;
    Nos *aux2 = f->ini;
    Tempo *tempHora = (Tempo*) malloc(sizeof(Tempo));

    Fila *temp = CriaFila();    // Fila de pousos temporários

    tempHora->hora = horarioGlobal->hora;
    tempHora->minutos = horarioGlobal->minutos;

    printf("\n HORA ATUAL %.2d:%.2d", tempHora->hora, tempHora->minutos);
    printf("\n == SIMULAÇÃO DE POUSOS ==");

    // Inserção do tempo
    do
    {
         printf("\n\n\t Insira um tempo, em minutos, para simular os pousos: ");
        scanf("%d", &minutos);
        
    } while (minutos <= 0);

    // Simulação dos pousos
    while(minutos > 0)
    {
        if(!VaziaFila(e) && aux != NULL)
        {
            alteraHora(tempHora, &aux);
            InsereFila(temp, aux->codigo, aux->numPass, aux->horario, aux->checkHora);
            aux = aux->prox;

        } else if(!VaziaFila(f) && aux2 != NULL)
        {
            alteraHora(tempHora, &aux2);
            InsereFila(temp, aux2->codigo, aux2->numPass, aux2->horario, aux2->checkHora);
            aux2 = aux2->prox;

        }
        minutos -= 10;
    }

    ImprimeFila(temp, 1);       // Imprime a simulação com o checkHora dos vôos
    printf("\n NOVO HORÁRIO %.2d:%.2d", tempHora->hora, tempHora->minutos);
    free(tempHora);
    LiberaFila(temp);
}

void alteraHora(Tempo *horarioGlobal, Nos **voo)        // Altera o horário global e atualiza o checkHora
{
    // Altera o checkHora com base no horário atual
    if((*voo)->checkHora != -1)
    {
        if(horarioGlobal->hora > (*voo)->horario->hora)
        {
            (*voo)->checkHora = 0;

        } else if(horarioGlobal->minutos > (*voo)->horario->minutos)
        {
            (*voo)->checkHora = 0;
        }
    }

    // Cada vôo leva 10 minutos para pousar
    horarioGlobal->minutos += 10;
    if(horarioGlobal->minutos >= 60)
    {
        horarioGlobal->hora += 1;
        horarioGlobal->minutos -= 60;
    }
}

int main()
{
    system("cls");
    setlocale(LC_ALL, "Portuguese");

    // Input do usuário no menu;
    int input = 0;

    // Seed
    int seed;

    // Horário global
    Tempo *horarioGlobal;
    int horaGlobal, minutoGlobal;

    //=================================================================================
    // Filas principais
    Fila *f = CriaFila();       // Fila principal de pouso
    Fila *e = CriaFila();       // Fila de pousos de emergência
    Fila *p = CriaFila();       // Fila de aviões que pousaram

    //=================================================================================
    // Inserção da seed
    printf("\n\n\t INSIRA O VALOR DA SEED: ");
    scanf("%d", &seed);
    srand(seed);

    //=================================================================================
    // Inserção do horário global
    horarioGlobal = (Tempo*) malloc(sizeof(Tempo));
    horaGlobal = rand() % 24;
    minutoGlobal = rand() % 60;

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
        printf("\n HORA ATUAL %.2d:%.2d", horarioGlobal->hora, horarioGlobal->minutos);
        printf("\n\n == MENU PRINCIPAL ==");
        printf("\n\n\t 1. Cadastrar novo voo");
        printf("\n\t 2. Autorizar pouso");
        printf("\n\t 3. Imprimir lista de espera");
        printf("\n\t 4. Imprimir lista de pouso");
        printf("\n\t 5. Simular pousos");
        printf("\n\t 0. Sair do programa");

        printf("\n\n Escolha uma das opcoes acima: ");
        scanf("%d", &input);

        switch(input)
        {
            case 1:
                CadastrarVoo(f, e, horarioGlobal);
                break;

            case 2:
                AutorizarPouso(f, e, p, horarioGlobal);
                break;

            case 3:
                system("cls");
                printf("\n\n == FILA DE EMERGÊNCIA ==");
                ImprimeFila(e, 0);
                printf("\n\n == FILA PRINCIPAL ==");
                ImprimeFila(f, 0);
                break;

            case 4:
                system("cls");
                printf("\n HORA ATUAL %.2d:%.2d", horarioGlobal->hora, horarioGlobal->minutos);
                ImprimeFila(p, 1);
                break;

            case 5:
                system("cls");
                SimularPouso(f, e, horarioGlobal);
                break;

            case 0:
                printf("\n\n\t\t Encerrando programa...");
                LiberaFila(f);
                LiberaFila(e);
                LiberaFila(p);
                break;

            default:
                printf("\n\n\t\t ERRO: Comando invalido inserido...");
                break;
        }
    } while (input != 0);


    return 0;
}