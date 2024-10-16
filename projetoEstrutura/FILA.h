#ifndef FILA_H_INCLUDED
#define FILA_H_INCLUDED

typedef struct tempo
{
    int hora;
    int minutos;
} Tempo;

typedef struct nos
{
    char codigo[5];
    int numPass;
    Tempo* horario;
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

Nos* InsereFim(Nos* fim, char codigo[], int valor, Tempo* horario)
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
    p->prox = NULL;

    if(fim != NULL)
    {
        fim->prox = p;
    }

    return p;
}

void InsereFila(Fila* f, char codigo[], int valor, Tempo* horario)
{
    f->fim = InsereFim(f->fim, codigo, valor, horario);

    if(f->ini == NULL)
    {
        f->ini = f->fim;
    }
}

void ImprimeFila(Fila* f)
{
    Nos* aux;
    
    printf("\n\n");

    for(aux = f->ini; aux != NULL; aux = aux->prox)
    {
        printf("\t\t%s", aux->codigo);
        printf("\t\t%d", aux->numPass);
        printf("\t\t Horario de chegada %d : %d", aux->horario->hora, aux->horario->minutos);
    }

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