#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"


Tusuario* Novo(char nome[], Tusuario* esq, Tusuario* dir)
{
    Tusuario* novo = (Tusuario*) malloc(sizeof(Tusuario));
    novo->ptfeed=NULL;
    novo->ptamigos=NULL;
    novo->ptinimigos=NULL;
    novo->esq=esq;
    novo->dir=dir;
    strcpy(novo->nome,nome);
    return novo;
};

Tusuario* Insere_Usuario(Tusuario *t, char nome[], FILE *saida)
{
    Tusuario *retorno=Splay(t,nome, saida);
};

Tusuario* Splay(Tusuario* t, char nome[], FILE *saida)
{
    Tusuario *retorno;
    if (t == NULL)
    {
        retorno=Novo(nome,NULL,NULL);
        fprintf(saida,"i usuario inserido com sucesso\n");
    }
    else if (!strcmp(nome,t->nome))
    {
        fprintf(saida,"i ERRO: Usuario ja cadastrado\n");
        retorno=t;
    }
    else if (strcmp(nome,t->nome)<0)
    {
        if (t->esq == NULL)
        {
            retorno=Novo(nome,NULL,t);
            fprintf(saida,"i usuario inserido com sucesso\n");
        }
        else if (!strcmp(nome,t->esq->nome))
        {
            fprintf(saida,"i ERRO: Usuario ja cadastrado\n");
            retorno=RotDir(t);
        }
        else
        {
            if (strcmp(nome,t->esq->nome)<0)
            {
                t->esq->esq = Splay(t->esq->esq, nome,saida);
                t = RotDir(t);
            }
            else
            {
                t->esq->dir = Splay(t->esq->dir, nome,saida);
                t->esq = RotEsq(t->esq);
            }
            retorno=RotDir(t);
        }
    }
    else
    {
        if (t->dir == NULL)
        {
            retorno=Novo(nome,t,NULL);
            fprintf(saida,"i usuario inserido com sucesso\n");
        }
        else if (!strcmp(nome,t->dir->nome))
        {
            fprintf(saida,"i ERRO: Usuario ja cadastrado\n");
            retorno=RotEsq(t);
        }
        else
        {
            if (strcmp(nome,t->dir->nome)>0)
            {
                t->dir->dir = Splay(t->dir->dir, nome,saida);
                t = RotEsq(t);
            }
            else
            {
                t->dir->esq = Splay(t->dir->esq, nome,saida);
                t->dir = RotDir(t->dir);
            }
            retorno=RotEsq(t);
        }
    }
    return retorno;
};

Tusuario* RotDir(Tusuario* t)
{
    Tusuario* x = t->esq;
    t->esq = x->dir;
    x->dir = t;
    return x;
};

Tusuario* RotEsq(Tusuario* t)
{
    Tusuario* x = t->dir;
    t->dir = x->esq;
    x->esq = t;
    return x;
};

void Exibe_Usuarios_Cresc(Tusuario *t, int *top, FILE *saida)
{
    if(t!=NULL)
    {
        Exibe_Usuarios_Cresc(t->esq,top,saida);
        if(*top!=0)
        {
            fprintf(saida, " %s", t->nome);
            *top=*top-1;
        }
        Exibe_Usuarios_Cresc(t->dir,top,saida);
    }
}

void Exibe_Usuarios_Decresc(Tusuario *t, int *top, FILE *saida)
{
    if(t!=NULL)
    {
        Exibe_Usuarios_Decresc(t->dir,top,saida);
        if(*top!=0)
        {
            fprintf(saida, " %s", t->nome);
            *top=*top-1;
        }
        Exibe_Usuarios_Decresc(t->esq,top,saida);
    }
}

void Exibe_Todos_Usuarios_Cresc(Tusuario *t, FILE *saida)
{ 
    if(t!=NULL)
    {
        Exibe_Todos_Usuarios_Cresc(t->esq,saida);
        fprintf(saida, " %s", t->nome);
        Exibe_Todos_Usuarios_Cresc(t->dir,saida);
    }
}

void Exibe_Todos_Usuarios_Decresc(Tusuario *t, FILE *saida)
{
    if(t!=NULL)
    {
        Exibe_Todos_Usuarios_Decresc(t->dir,saida);
        fprintf(saida, " %s", t->nome);
        Exibe_Todos_Usuarios_Decresc(t->esq,saida);
    }
}

Tusuario* Consulta_Usuario(Tusuario* t, char nome[])
{
    Tusuario* retorno;
    if (t==NULL)
        retorno=NULL;
    else if (strcmp(nome, t->nome)<0)
    {
        if (t->esq == NULL)
            retorno=t;
        else if (strcmp(nome, t->esq->nome)<0)
        {
            t->esq->esq = Consulta_Usuario(t->esq->esq, nome);
            t = RotDir(t);
            if (t->esq == NULL)
                retorno=t;
            else
                retorno=RotDir(t);
        }
        else if (strcmp(t->esq->nome,nome)<0)
        {
            t->esq->dir = Consulta_Usuario(t->esq->dir, nome);
            if (t->esq->dir != NULL)
                t->esq = RotEsq(t->esq);
            retorno=RotDir(t);
        }
        else
            retorno=RotDir(t);
    }
    else if(strcmp(t->nome, nome)<0)
    {
        if (t->dir == NULL)
            retorno=t;
        else if (strcmp(t->dir->nome,nome)<0)
        {
            t->dir->dir = Consulta_Usuario(t->dir->dir, nome);
            t = RotEsq(t);
            if (t->dir == NULL)
                retorno=t;
            else
                retorno=RotEsq(t);
        }
        else if (strcmp(nome,t->dir->nome)<0)
        {
            t->dir->esq = Consulta_Usuario(t->dir->esq, nome);
            if (t->dir->esq != NULL) t->dir = RotDir(t->dir);
            retorno=RotEsq(t);
        }
        else
            retorno=RotEsq(t);
    }
    else
        retorno=t;
    return retorno;
};

void Desenha(Tusuario* t, int nivel, int num)
{
    int x;
    if (t !=NULL)
    {
        for (x=1; x<=nivel; x++)
            printf("=");
        printf("%s", t->nome);
        if (num==0)
            printf(" Raiz\n");
        else if(num==1)
            printf(" Esq\n");
        else
            printf(" Dir\n");
        if (t->esq != NULL) Desenha(t->esq, (nivel+1), 1);
        if (t->dir != NULL) Desenha(t->dir, (nivel+1), 2);
    }
    else printf("Arvore Vazia");
}
void central_esquerda (Tusuario *a, char array[][80], int *i, int nivel)
{
    if(a!=NULL)
    {
        central_esquerda(a->esq,array,i,nivel+1);
        array[nivel][*i]=a->nome[0];
        array[nivel][*i+1]=a->nome[1];
        *i=*i+2;
        central_esquerda(a->dir,array,i,nivel+1);
    }
}

void imprime_arvore (Tusuario *a)
{
    char array[24][80]= {0};
    int i=0,j;
    central_esquerda (a,array,&i,0);
    for(i=0; i<24; i++)
    {
        for(j=0; j<80; j++)
        {
            if(array[i][j]!=0)
                printf("%c", array[i][j]);
            else
                printf(" ");
        }
        if(j%2)
            printf(" ");
    }
}

Tamigo_inimigo* InsereABP(Tusuario* amigo, Tamigo_inimigo* a, char nome[])
{
    if (a == NULL)
    {
        a = (Tamigo_inimigo*) malloc(sizeof(Tamigo_inimigo));
        a->info = amigo;
        a->esq = NULL;
        a->dir = NULL;
    }
    else
    {
        if (strcmp(a->info->nome, nome) > 0)
        {
            a->esq = InsereABP(amigo, a->esq, nome);
        }
        else
        {
            a->dir = InsereABP(amigo, a->dir, nome);
        }
    }
    return a;
}

Tamigo_inimigo* InsereAmigoInimigo(Tusuario* t, Tusuario* amigo, int tipo, FILE *saida)
{
    Tamigo_inimigo* retorno=NULL;
    if(tipo == 1)
    {
        if(consultaAmigo(t->ptamigos, amigo->nome) != NULL)
        {
            fprintf(saida, "a ERRO amigo ja inserido\n");
            retorno = t->ptamigos;
        }
        else
        {
            retorno = InsereABP(amigo, t->ptamigos, amigo->nome);
            fprintf(saida,"a amigo inserido com sucesso\n");
        }
    }
    else
    {
        if(consultaInimigo(t->ptinimigos, amigo->nome) != NULL)
        {
            fprintf(saida,"a ERRO inimigo ja inserido\n");
            retorno = t->ptinimigos;
        }
        else
        {
            retorno = InsereABP(amigo, t->ptinimigos, amigo->nome);
            fprintf(saida,"a inimigo inserido com sucesso\n");
        }
    }
    return retorno;
}

Tusuario* consultaAmigo(Tamigo_inimigo* pt, char nome[])
{
    Tusuario* retorno;
    if (pt == NULL)
    {
        retorno = NULL;
    }
    else
    {
        if (!strcmp(pt->info->nome, nome))
        {
            retorno = pt->info;
        }
        else
        {
            if (strcmp(pt->info->nome, nome) > 0)
            {
                retorno = consultaAmigo(pt->esq, nome);
            }
            else
            {
                retorno = consultaAmigo(pt->dir, nome);
            }
        }
    }
    return retorno;
}

Tusuario* consultaInimigo(Tamigo_inimigo* pt, char nome[])
{
    Tusuario* retorno;
    if (pt == NULL)
    {
        retorno = NULL;
    }
    else
    {
        if (strcmp(pt->info->nome, nome) == 0)
        {
            retorno = pt->info;
        }
        else
        {
            if (strcmp(pt->info->nome, nome) > 0)
            {
                retorno = consultaInimigo(pt->esq, nome);
            }
            else
            {
                retorno = consultaInimigo(pt->dir, nome);
            }
        }
    }
    return retorno;
}

void Exibe_Amigos(Tusuario* t, int tipo, int top, FILE *saida)
{
	fprintf(saida,"m");
    if (top == 0)
    {
        if (tipo == 1)
        {
            if (t->ptamigos == NULL)
            {
                fprintf(saida," ERRO nenhum amigo cadastrado");
            }
            else
            {
                Exibe_Todos_Amigos_Cresc(t->ptamigos, saida);
            }
        }
        else
        {
            if (t->ptinimigos == NULL)
            {
                fprintf(saida," ERRO nenhum rival cadastrado");
            }
            else
            {
                Exibe_Todos_Amigos_Cresc(t->ptinimigos, saida);
            }
        }
    }
    else
    {
        if (tipo == 1)
        {
            if (t->ptamigos == NULL)
            {
                fprintf(saida," ERRO nenhum amigo cadastrado");
            }
            else
            {
                Exibe_Amigos_Cresc(t->ptamigos, &top, saida);
            }
        }
        else
        {
            if (t->ptinimigos == NULL)
            {
                fprintf(saida," ERRO nenhum rival cadastrado");
            }
            else
            {
                Exibe_Amigos_Cresc(t->ptinimigos, &top, saida);
            }
        }
    }
    fprintf(saida,"\n");
}

void Exibe_Todos_Amigos_Cresc(Tamigo_inimigo *t, FILE *saida)
{
    if(t!=NULL)
    {
        Exibe_Todos_Amigos_Cresc(t->esq, saida);
        fprintf(saida, " %s", t->info->nome);
        Exibe_Todos_Amigos_Cresc(t->dir, saida);
    }
}

void Exibe_Amigos_Cresc(Tamigo_inimigo *t, int *top, FILE *saida)
{
    if(t!=NULL)
    {
        Exibe_Amigos_Cresc(t->esq,top, saida);
        if(*top!=0)
        {
            fprintf(saida, " %s", t->info->nome);
            *top=*top-1;
        }
        Exibe_Amigos_Cresc(t->dir,top, saida);
    }
}
