#ifndef FILA_H_INCLUDED
#define FILA_H_INCLUDED

/*  BIBLIOTECA DE FILAS

    int VaziaFila(Fila *f)  ........................    Verifica se a fila está vazia, retorna 1 caso sim e 0 caso não

    Fila *CriaFila()        ........................    Cria uma nova fila e a retorna

    void InsereFila(Fila* f, char codigo[], int valor, Tempo* horario)  ........................    Insere os dados na fila

    Nos *RetiraFila(Fila *f)    ........................    Retira o primeiro nó da fila e retorna

    void ImprimeFila(Fila* f, Fila *e, int status)   ........................    Imprime a fila completa, status define a impresão do checkHora

    Fila *LiberaFila(Fila* f)   ........................    Libera os espaços de memória alocados para a fila

*/

typedef struct tempo
{
    int hora;
    int minutos;
} Tempo;

typedef struct nos
{
    char codigo[4];
    int numPass;
    Tempo* horario;
    int checkHora;
    struct nos* prox;
} Nos;

typedef struct fila
{
    Nos* ini;
    Nos* fim;
} Fila;

int VaziaFila(Fila* f)
{
    if(f->ini == NULL)
    {
        return 1;
    }

    return 0;
}

Fila* CriaFila()
{
    Fila* f = (Fila*) malloc(sizeof(Fila));
    f->ini = f->fim = NULL;
    return f;
}

Nos* InsereFim(Nos* fim, char codigo[], int valor, Tempo* horario, int checkHora)
{
    Nos* p = (Nos*) malloc(sizeof(Nos));

    for(int i = 0; i <= 4; i++)
    {
        p->codigo[i] = codigo[i];
    }

    p->numPass = valor;

    p->horario = (Tempo*) malloc(sizeof(Tempo));

    p->horario->hora = horario->hora;
    p->horario->minutos = horario->minutos;
    p->checkHora = checkHora;        // checkHora é inicializado como NULL por padrão
    p->prox = NULL;

    if(fim != NULL)
    {
        fim->prox = p;
    }

    return p;
}

void InsereFila(Fila* f, char codigo[], int valor, Tempo* horario, int checkHora)
{
    f->fim = InsereFim(f->fim, codigo, valor, horario, checkHora);

    if(f->ini == NULL)
    {
        f->ini = f->fim;
    }
}

Nos* RetiraInicio(Nos* ini)
{
    Nos* p = ini->prox;
    free(ini);

    return p;
}

Nos* RetiraFila(Fila* f)
{
    Nos* v;

    if(VaziaFila(f))
    {
        printf("\n\t ERRO: Fila vazia");
        exit(0);
    }

    v = f->ini;

    f->ini = RetiraInicio(f->ini);

    if(f->ini == NULL)
    {
        f->fim = NULL;
    }

    return v;
}

void ImprimeFila(Fila *f, Fila *e, int status)
{
    Nos* aux;
    system("cls");
    if(VaziaFila(f))
    {
        printf("\n\n\t\t ERRO: Fila Vazia");

    } else
    {
        printf("\n\n == FILA PRINCIPAL ==");

        for(aux = f->ini; aux != NULL; aux = aux->prox)
        {
            printf("\n\t Voo: %.4s", aux->codigo);
            printf("\n\t\t Numero de passageiros: %d", aux->numPass);
            printf("\n\t\t Horario de chegada %.2d:%.2d", aux->horario->hora, aux->horario->minutos);

            if(status == 1)
            {
                printf("\n\t\t Status de pouso: %d", aux->checkHora);
            }
        }
    }

    if(VaziaFila(e))
    {
        printf("\n\n\t\t ERRO: Fila Vazia");

    } else
    {
        printf("\n\n == FILA DE EMERGENCIA ==");

        for(aux = e->ini; aux != NULL; aux = aux->prox)
        {
            printf("\n\t Voo: %.4s", aux->codigo);
            printf("\n\t\t Numero de passageiros: %d", aux->numPass);
            printf("\n\t\t Horario de chegada %.2d:%.2d", aux->horario->hora, aux->horario->minutos);

            if(status == 1)
            {
                printf("\n\t\t Status de pouso: %d", aux->checkHora);
            }
        }
    }

}

void ImprimeNo(Nos *n)
{
    printf("\n\t Voo: %.4s", n->codigo);
    printf("\n\t\t Numero de passageiros: %d", n->numPass);
    printf("\n\t\t Status do voo: %d", n->checkHora);
}

Fila* LiberaFila(Fila* f)
{
    Nos* aux = f->ini;

    while(aux != NULL)
    {
        Nos* aux2 = aux->prox;
        free(aux->horario);     // Liberando espaço alocado para a struct Tempo
        free(aux);

        aux = aux2;
    }

    free(f);
    return NULL;
}

#endif // FILA_H_INCLUDED
