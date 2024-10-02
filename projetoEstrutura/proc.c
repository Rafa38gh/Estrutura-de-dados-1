#include<stdio.h>
#include "FILA.h"

int main()
{
    int num;

    // Dados do vôo
    char codigo[5];
    int numPass;
    Tempo* horario;

    // Variáveis para inserção do horario
    int hora, minutos;


    Fila* f = CriaFila();

    system("cls");

    printf("\n Digite a quantidade de dados que deseja inserir: ");
    scanf("%d", &num);


    // Inserção de dados
    for(int i = 0; i < num; i++)
    {
        printf("\n Insira o codigo do voo: ");
        scanf("%4s", codigo);

        printf("\n\t Insira o numero de passageiros: ");
        scanf("%d", &numPass);

        printf("\n\t Insira a hora do voo: ");
        scanf("%d", &hora);

        printf("\n\t Insira os minutos do voo: ");
        scanf("%d", &minutos);

        // Mesclando os dados do tempo
        horario = (Tempo*) malloc(sizeof(Tempo));
        horario->hora = hora;
        horario->minutos = minutos;

        InsereFila(f, codigo, numPass, horario);
        free(horario);
    }

    ImprimeFila(f);

    Nos* noRemov = RetiraFila(f);

    ImprimeFila(f);

    LiberaFila(f);

    return 0;
}
