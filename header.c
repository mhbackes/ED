#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "abp.h"
void input(Tusuario **ptusuario)
{
    FILE *arq;
    Tamigo_inimigo* ret_ins_amigo = NULL;
    char opcao, nome1[100], nome2[100], texto[1000];
    int ord, top, tipo, a;
    if(arq=fopen("texto.txt","r"))
    {
        while(!feof(arq))
        {
            if(opcao=getc(arq))
            {
                switch(opcao)
                {
                case 'i':
                    printf("Insere Usuario\n");
                    fscanf(arq, "%s", nome1);
                    printf("nome1=%s\n\n", nome1);
                    *ptusuario=Insere_Usuario(*ptusuario,nome1);
                    printf("\n\n");
                    break;
                case 'e':
                    printf("Exibe\n");
                    fscanf(arq, "%d%d", &ord, &top);
                    printf("ord=%d, top=%d\n\n",ord, top);
                    if(top!=0)
                    {
                        printf("Impressao de %d usuarios:\n", top);
                        if(ord==1)
                            Exibe_Usuarios_Cresc(*ptusuario,&top);
                        else
                            Exibe_Usuarios_Decresc(*ptusuario,&top);
                        printf("\n");
                    }
                    else
                    {
                        printf("Impressao de todos usuarios:\n", top);
                        if(ord==1)
                            Exibe_Todos_Usuarios_Cresc(*ptusuario);
                        else
                            Exibe_Todos_Usuarios_Decresc(*ptusuario);
                        printf("\n");
                    }
                    break;
                case 'a':
                    printf("\nInsere Amigo\n");
                    fscanf(arq, "%s%s%d", nome1, nome2, &tipo);
                    printf("nome1=%s, nome2=%s, tipo=%d\n\n", nome1, nome2, tipo);
                    if(*ptusuario=Consulta_Usuario(*ptusuario,nome2))
                    {
                        if(!(strcmp(nome2,(*ptusuario)->nome)))
                        {
                            a=*ptusuario;
                            if(*ptusuario=Consulta_Usuario(*ptusuario,nome1))
                            {
                                if(!(strcmp(nome1,(*ptusuario)->nome)))
                                {
                                    ret_ins_amigo = InsereAmigoInimigo(*ptusuario, a, tipo);
                                    if(tipo == 1)
                                    {
                                        (*ptusuario)->ptamigos = ret_ins_amigo;
                                    }
                                    if(tipo == 2)
                                    {
                                        (*ptusuario)->ptinimigos = ret_ins_amigo;
                                    }
                                }
                                else
                                {
                                    printf("Usuario %s nao esta cadastrado\n\n", nome1);
                                }
                            }
                        }
                        else
                        {
                            printf("Usuario %s nao esta cadastrado\n\n", nome2);
                        }
                    }
                    break;
                case 'm':
                    printf("Exibe Amigos\n");
                    fscanf(arq, "%s%d%d", nome1, &tipo, &top);
                    printf("nome1=%s, tipo=%d, top=%d\n\n", nome1, tipo, top);
                    if(*ptusuario=Consulta_Usuario(*ptusuario,nome1))
                    {
                        if(!(strcmp(nome1,(*ptusuario)->nome)))
                        {
                            printf("%s\n\n",(*ptusuario)->nome);
                            Exibe_Amigos(*ptusuario, tipo, top);
                        }
                        else
                        {
                            printf("Usuario %s nao esta cadastrado\n\n", nome1);
                        }
                    }
                    break;
                case 't':
                    printf("Post\n");
                    fscanf(arq, "%s", nome1);
                    a=ftell(arq);
                    fseek(arq, 2, SEEK_CUR);
                    a=ftell(arq);
                    fgets(texto, 1000, arq);
                    strtok(texto,"\"");
                    a=ftell(arq);
                    fseek(arq, -3, SEEK_CUR);
                    a=ftell(arq);
                    fscanf(arq, "%d", &tipo);
                    printf("nome1=%s, texto=%s, tipo=%d\n\n", nome1, texto, tipo);
                    // post;
                    break;
                case 'p':
                    printf("Exibe Painel\n");
                    fscanf(arq, "%s%d%d", nome1, &tipo, &top);
                    printf("nome1=%s, tipo=%d, top=%d\n\n", nome1, tipo, top);
                    // exibe_painel;
                    break;
                case 'c':
                    printf("Ranking Popular Circulo\n");
                    fscanf(arq, "%s%d%d", nome1, &tipo, &top);
                    printf("nome1=%s, tipo=%d, top=%d\n\n", nome1, tipo, top);
                    // ranking_popular_circulo;
                    break;
                case 'r':
                    printf("Ranking Popular\n");
                    fscanf(arq, "%d%d", &tipo, &top);
                    printf("tipo=%d, top=%d\n\n", tipo, top);
                    // ranking_popular;
                }
                getc(arq);
            }
        }
        fclose(arq);
    }
    else
    {
        printf("Arquivo nao encontrado");
    }
}

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

Tusuario* Insere_Usuario(Tusuario *t, char nome[])
{
    Tusuario *retorno=Splay(t,nome);
};

Tusuario* Splay(Tusuario* t, char nome[])
{
    Tusuario *retorno;
    if (t == NULL)
    {
        retorno=Novo(nome,NULL,NULL);
        printf("Usuario inserido com sucesso\n\n");
    }
    else if (!strcmp(nome,t->nome))
    {
        printf("Usuario ja cadastrado");
        retorno=t;
    }
    else if (strcmp(nome,t->nome)<0)
    {
        if (t->esq == NULL)
        {
            retorno=Novo(nome,NULL,t);
            printf("Usuario inserido com sucesso\n");
        }
        else if (!strcmp(nome,t->esq->nome))
        {
            printf("Usuario ja cadastrado\n");
            retorno=RotDir(t);
        }
        else
        {
            if (strcmp(nome,t->esq->nome)<0)
            {
                t->esq->esq = Splay(t->esq->esq, nome);
                t = RotDir(t);
            }
            else
            {
                t->esq->dir = Splay(t->esq->dir, nome);
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
            printf("Usuario inserido com sucesso\n");
        }
        else if (!strcmp(nome,t->dir->nome))
        {
            printf("Usuario ja cadastrado\n");
            retorno=RotEsq(t);
        }
        else
        {
            if (strcmp(nome,t->dir->nome)>0)
            {
                t->dir->dir = Splay(t->dir->dir, nome);
                t = RotEsq(t);
            }
            else
            {
                t->dir->esq = Splay(t->dir->esq, nome);
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

void Exibe_Usuarios_Cresc(Tusuario *t, int *top)
{
    if(t!=NULL)
    {
        Exibe_Usuarios_Cresc(t->esq,top);
        if(*top!=0)
        {
            printf("%s\n", t->nome);
            *top=*top-1;
        }
        Exibe_Usuarios_Cresc(t->dir,top);
    }
}

void Exibe_Usuarios_Decresc(Tusuario *t, int *top)
{
    if(t!=NULL)
    {
        Exibe_Usuarios_Decresc(t->dir,top);
        if(*top!=0)
        {
            printf("%s\n", t->nome);
            *top=*top-1;
        }
        Exibe_Usuarios_Decresc(t->esq,top);
    }
}

void Exibe_Todos_Usuarios_Cresc(Tusuario *t)
{
    if(t!=NULL)
    {
        Exibe_Todos_Usuarios_Cresc(t->esq);
        printf("%s\n", t->nome);
        Exibe_Todos_Usuarios_Cresc(t->dir);
    }
}

void Exibe_Todos_Usuarios_Decresc(Tusuario *t)
{
    if(t!=NULL)
    {
        Exibe_Todos_Usuarios_Decresc(t->dir);
        printf("%s\n", t->nome);
        Exibe_Todos_Usuarios_Decresc(t->esq);
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

Tamigo_inimigo* InsereAmigoInimigo(Tusuario* t, Tusuario* amigo, int tipo)
{
    Tamigo_inimigo* a=NULL;
    if(tipo == 1)
    {
        if(consultaAmigo(t->ptamigos, amigo->nome) != NULL)
        {
            printf("Usuario %s ja eh amigo de %s\n\n", amigo->nome, t->nome);
            a = t->ptamigos;
        }
        else
        {
            a = InsereABP(amigo, t->ptamigos, amigo->nome);
            printf("Agora %s eh amigo de %s\n\n", amigo->nome, t->nome);
        }
    }
    else
    {
        if(consultaInimigo(t->ptinimigos, amigo->nome) != NULL)
        {
            printf("Usuario %s ja eh inimigo de %s\n\n", amigo->nome, t->nome);
            a = t->ptinimigos;
        }
        else
        {
            a = InsereABP(amigo, t->ptinimigos, amigo->nome);
            printf("Agora %s eh inimigo de %s\n\n", amigo->nome, t->nome);
        }
    }
    return a;
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

void Exibe_Amigos(Tusuario* t, int tipo, int top)
{
    if (top == 0)
    {
        if (tipo == 1)
        {
            if (t->ptamigos == NULL)
            {
                printf("Lista de amigos vazia\n\n");
            }
            else
            {
                Exibe_Todos_Amigos_Cresc(t->ptamigos);
            }
        }
        else
        {
            if (t->ptinimigos == NULL)
            {
                printf("Lista de inimigos vazia\n\n");
            }
            else
            {
                Exibe_Todos_Amigos_Cresc(t->ptinimigos);
            }
        }
    }
    else
    {
        if (tipo == 1)
        {
            if (t->ptamigos == NULL)
            {
                printf("Lista de amigos vazia\n\n");
            }
            else
            {
                Exibe_Amigos_Cresc(t->ptamigos, top);
            }
        }
        else
        {
            if (t->ptinimigos == NULL)
            {
                printf("Lista de inimigos vazia\n\n");
            }
            else
            {
                Exibe_Amigos_Cresc(t->ptinimigos, top);
            }
        }
    }
}

void Exibe_Todos_Amigos_Cresc(Tamigo_inimigo *t)
{
    if(t!=NULL)
    {
        Exibe_Todos_Amigos_Cresc(t->esq);
        printf("%s\n", t->info->nome);
        Exibe_Todos_Amigos_Cresc(t->dir);
    }
}

void Exibe_Amigos_Cresc(Tamigo_inimigo *t, int *top)
{
    if(t!=NULL)
    {
        Exibe_Amigos_Cresc(t->esq,top);
        if(*top!=0)
        {
            printf("%s\n", t->info->nome);
            *top=*top-1;
        }
        Exibe_Amigos_Cresc(t->dir,top);
    }
}
