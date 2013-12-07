#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

//fun��o responsavel por alocar e armazenar os dados do novo usuario
Tusuario* Novo(char nome[], Tusuario* esq, Tusuario* dir)
{
    Tusuario* novo = (Tusuario*) malloc(sizeof(Tusuario)); //aloca espa�o na memoria
    novo->ptfeed=NULL; //inicializa o ponteiro
    novo->ptamigos=NULL; //inicializa o ponteiro
    novo->ptinimigos=NULL; //inicializa o ponteiro
    novo->esq=esq; //inicializa o ponteiron (sempre recebe NULL)
    novo->dir=dir; //inicializa o ponteiro (sempre recebe NULL)
    novo->numamigos=0; //inicializa o contador
    novo->numinimigos=0; //inicializa o contador
    strcpy(novo->nome,nome); //insere o nome do usuario
    return novo;
};

//chama fun��o splay para inser��o do novo usu�rio
Tusuario* Insere_Usuario(Tusuario *t, char nome[], FILE *saida)
{
    Tusuario *retorno=Splay(t,nome, saida);
    return retorno;
};

//fun��o respons�vel por
Tusuario* Splay(Tusuario* t, char nome[], FILE *saida)
{
    Tusuario *retorno;
    if (t == NULL)
    {
        retorno=Novo(nome,NULL,NULL);
        fprintf(saida,"i usuario inserido com sucesso\n");
    }
    else
    {
        if (!strcmp(nome,t->nome))
        {
            fprintf(saida,"i ERRO: Usuario ja cadastrado\n");
            retorno=t;
        }
        else
        {
            if (strcmp(nome,t->nome)<0)
            {
                if (t->esq == NULL)
                {
                    retorno=Novo(nome,NULL,t);
                    fprintf(saida,"i usuario inserido com sucesso\n");
                }
                else
                {
                    if (!strcmp(nome,t->esq->nome))
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
            }
            else
            {
                if (t->dir == NULL)
                {
                    retorno=Novo(nome,t,NULL);
                    fprintf(saida,"i usuario inserido com sucesso\n");
                }
                else
                {
                    if (!strcmp(nome,t->dir->nome))
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
            }
        }
    }
    return retorno;
};

//faz rota��o para direita
Tusuario* RotDir(Tusuario* t)
{
    Tusuario* x = t->esq;
    t->esq = x->dir;
    x->dir = t;
    return x;
};

//faz rota��o para esquerda
Tusuario* RotEsq(Tusuario* t)
{
    Tusuario* x = t->dir;
    t->dir = x->esq;
    x->esq = t;
    return x;
};

//fun��o respons�vel por exibir os usu�rios em ordem alfab�tica
void Exibe_Usuarios_Cresc(Tusuario *t, int *top, FILE *saida)
{
    if(t!=NULL) //apenas executa se o ponteiro para usu�rio n�o for NULL
    {
        Exibe_Usuarios_Cresc(t->esq,top,saida); //chama a mesma fun��o para arvore a esquerda
        if(*top!=0) //equanto o contador for diferente de 0, continua
        {
            fprintf(saida, " %s", t->nome); //imprime o nome do usu�rio
            *top=*top-1; //decrementa o contador
        }
        Exibe_Usuarios_Cresc(t->dir,top,saida); //chama a mesma fun��o para arvore a direita
    }
}

//fun��o respons�vel por exibir os usu�rios em ordem inversa � alfab�tica
void Exibe_Usuarios_Decresc(Tusuario *t, int *top, FILE *saida)
{
    if(t!=NULL) //apenas executa se o ponteiro para usu�rio n�o for NULL
    {
        Exibe_Usuarios_Decresc(t->dir,top,saida); //chama a mesma fun��o para arvore a direita
        if(*top!=0) //equanto o contador for diferente de 0, continua
        {
            fprintf(saida, " %s", t->nome); //imprime o nome do usu�rio
            *top=*top-1; //decrementa o contador
        }
        Exibe_Usuarios_Decresc(t->esq,top,saida); //chama a mesma fun��o para arvore a esquerda
    }
}

//fun��o respons�vel por exibir todos os usu�rios em ordem alfab�tica
void Exibe_Todos_Usuarios_Cresc(Tusuario *t, FILE *saida)
{
    if(t!=NULL) //apenas executa se o ponteiro para usu�rio n�o for NULL
    {
        Exibe_Todos_Usuarios_Cresc(t->esq,saida); //chama a mesma fun��o para arvore a esquerda
        fprintf(saida, " %s", t->nome); //imprime o nome do usu�rio
        Exibe_Todos_Usuarios_Cresc(t->dir,saida); //chama a mesma fun��o para arvore a direita
    }
}

//fun��o respons�vel por exibir os usu�rios em ordem inversa � alfab�tica
void Exibe_Todos_Usuarios_Decresc(Tusuario *t, FILE *saida)
{
    if(t!=NULL) //apenas executa se o ponteiro para usu�rio n�o for NULL
    {
        Exibe_Todos_Usuarios_Decresc(t->dir,saida); //chama a mesma fun��o para arvore a direita
        fprintf(saida, " %s", t->nome); //imprime o nome do usu�rio
        Exibe_Todos_Usuarios_Decresc(t->esq,saida); //chama a mesma fun��o para arvore a esquerda
    }
}

//fun��o respons�vel por verificar a exist�ncia ou n�o de um usu�rio
Tusuario* Consulta_Usuario(Tusuario* t, char nome[])
{
    Tusuario* retorno;
    if (t==NULL) //se o ponteiro for NULL, retorna NULL (lista de usu�rios vazia)
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

//fun��o respons�vel pela impress�o dos amigos ou rivais de um dado usu�rio t
void Exibe_Amigos(Tusuario* t, int tipo, int top, FILE *saida)
{
    fprintf(saida,"m"); //imprime o c�digo da opera��o no arquivo txt
    if (top == 0) //se o top for 0, imprime todos os amigos ou rivais do usu�rio t
    {
        if (tipo == 1) //se tipo for 1, ent�o imprime todos amigos do usuario t
        {
            if (t->ptamigos == NULL) //caso o ponteiro para a lista de amigos seja nula, a lista esta vazia
            {
                fprintf(saida," ERRO nenhum amigo cadastrado"); //mensagem de erro impresso no arquivo txt
            }
            else //se n�o estiver vazia, imprime todos amigos da lista
            {
                Exibe_Todos_Amigos_Cresc(t->ptamigos, saida); //chamada da fun��o
            }
        }
        else //se o tipo for 2,  ent�o imprime todos os rivais do usuario t
        {
            if (t->ptinimigos == NULL) //caso o ponteiro para a lista de rivais seja nula, a lista esta vazia
            {
                fprintf(saida," ERRO nenhum rival cadastrado"); //mensagem de erro impresso no arquivo txt
            }
            else //se n�o estiver vazia, imprime todos rivais da lista
            {
                Exibe_Todos_Amigos_Cresc(t->ptinimigos, saida); //chamada da fun��o
            }
        }
    }
    else
    {
        if (tipo == 1) //se tipo for 1, ent�o imprime o n�mero contigo em top de amigos do usuario t
        {
            if (t->ptamigos == NULL) //caso o ponteiro para a lista de amigos seja nula, a lista esta vazia
            {
                fprintf(saida," ERRO nenhum amigo cadastrado"); //mensagem de erro impresso no arquivo txt
            }
            else //se n�o estiver vazia, imprime o n�mero contigo em top de amigos da lista
            {
                Exibe_Amigos_Cresc(t->ptamigos, &top, saida); //chamada da fun��o
            }
        }
        else //se o tipo for 2,  ent�o imprime o n�mero contigo em top de rivais do usuario t
        {
            if (t->ptinimigos == NULL) //caso o ponteiro para a lista de rivais seja nula, a lista esta vazia
            {
                fprintf(saida," ERRO nenhum rival cadastrado"); //mensagem de erro impresso no arquivo txt
            }
            else //se n�o estiver vazia, imprime o n�mero contigo em top de rivais da lista
            {
                Exibe_Amigos_Cresc(t->ptinimigos, &top, saida); //chamada da fun��o
            }
        }
    }
    fprintf(saida,"\n"); //imprime um "Enter" no arquivo txt
}

//fun��o respons�vel por imprimir todos amigos ou rivais de um usuario
void Exibe_Todos_Amigos_Cresc(Tamigo_inimigo *t, FILE *saida)
{
    if(t!=NULL) //apena executa se o ponteiro t n�o for NULL
    {
        Exibe_Todos_Amigos_Cresc(t->esq, saida); //chama a mesma fun��o para arvore a esquerda
        fprintf(saida, " %s", t->info->nome); //imprime o nome do amigo ou rival
        Exibe_Todos_Amigos_Cresc(t->dir, saida); //chama a mesma fun��o para arvore a direita
    }
}

//fun��o respons�vel por imprimir um n�mero X (contigo na vari�vel top) de amigos ou rivais de um usuario
void Exibe_Amigos_Cresc(Tamigo_inimigo *t, int *top, FILE *saida)
{
    if(t!=NULL) //apena executa se o ponteiro t n�o for NULL
    {
        Exibe_Amigos_Cresc(t->esq,top, saida); //chama a mesma fun��o para arvore a esquerda
        if(*top!=0) //executa apenas se o contador for diferente de 0
        {
            fprintf(saida, " %s", t->info->nome); //imprime o nome do amigo ou rival
            *top=*top-1; //decrementa o contador
        }
        Exibe_Amigos_Cresc(t->dir,top, saida); //chama a mesma fun��o para arvore a direita
    }
}

//cria uma ABP para organizar o ranking de tipo 0
void Cria_Ranking_amigo_inimigo (Tranking_popular **ptranking, Tusuario *ptusuario)
{
    if(ptusuario!=NULL) //apena executa se o ponteiro ptusuario n�o for NULL
    {
        Cria_Ranking_amigo_inimigo(ptranking,ptusuario->dir); //chama a mesma fun��o para arvore a direita
        if(((ptusuario->numamigos)+(ptusuario->numinimigos))!=0) //apenas executa se a soma do n�mero de amigos e rivais for diferente de 0
            *ptranking=Insere_Ranking_amigo_inimigo(*ptranking,ptusuario); //chama a fun��o de inserir ranking e guarda o retorno no ptranking
        Cria_Ranking_amigo_inimigo(ptranking,ptusuario->esq); //chama a mesma fun��o para arvore a esquerda
    }
}

//Insere os dados na �rvore usando como chave a soma do n�mero de amigos e rivais
Tranking_popular* Insere_Ranking_amigo_inimigo (Tranking_popular *ptranking, Tusuario *ptusuario)
{
    Tranking_popular *retorno=ptranking; //declara um ponteiro
    if(ptranking==NULL) //apena executa se o ponteiro ptranking for NULL (foi encontrado o local correto para inserir o nodo)
    {
        retorno=malloc(sizeof(Tranking_popular)); //aloca espa�o na memoria
        strcpy(retorno->nome,ptusuario->nome); //armazena o nome do usuario
        retorno->num=(ptusuario->numamigos)+(ptusuario->numinimigos); //armazena a soma do n�mero de amigos e rivais
        retorno->esq=NULL; //inicializa o ponteiro
        retorno->dir=NULL; //inicializa o ponteiro
    }
    else if (ptranking->num>((ptusuario->numamigos)+(ptusuario->numinimigos))) //se a soma do n�mero de amigos e rivais do novo nodo for menor que a do nodo atual
        ptranking->esq=Insere_Ranking_amigo_inimigo(ptranking->esq, ptusuario); //chama a mesma fun��o para a �rvore a esquerda
    else //se a soma do n�mero de amigos e rivais do novo nodo for maior que a do nodo atual
        ptranking->dir=Insere_Ranking_amigo_inimigo(ptranking->dir, ptusuario); //chama a mesma fun��o para a �rvore a direita
    return retorno; //retorna os dados do ponteiro retorno
}

//cria uma ABP para organizar o ranking de tipo 1
void Cria_Ranking_amigo (Tranking_popular **ptranking, Tusuario *ptusuario)
{
    if(ptusuario!=NULL) //apena executa se o ponteiro ptusuario n�o for NULL
    {
        Cria_Ranking_amigo(ptranking,ptusuario->dir); //chama a mesma fun��o para arvore a direita
        if(ptusuario->numamigos!=0) //apenas executa se o n�mero de amigos for diferente de 0
            *ptranking=Insere_Ranking_amigo(*ptranking,ptusuario); //chama a fun��o de inserir ranking e guarda o retorno no ptranking
        Cria_Ranking_amigo(ptranking,ptusuario->esq); //chama a mesma fun��o para arvore a esquerda
    }
}

//Insere os dados na �rvore usando como chave o n�mero de amigos
Tranking_popular* Insere_Ranking_amigo (Tranking_popular *ptranking, Tusuario *ptusuario)
{
    Tranking_popular *retorno=ptranking; //declara um ponteiro
    if(ptranking==NULL) //apena executa se o ponteiro ptranking for NULL (foi encontrado o local correto para inserir o nodo)
    {
        retorno=malloc(sizeof(Tranking_popular)); //aloca espa�o na memoria
        strcpy(retorno->nome,ptusuario->nome); //armazena o nome do usuario
        retorno->num=ptusuario->numamigos; //armazena o n�mero de amigos
        retorno->esq=NULL; //inicializa o ponteiro
        retorno->dir=NULL; //inicializa o ponteiro
    }
    else if (ptranking->num>ptusuario->numamigos) //se o n�mero de amigos do novo nodo for menor que a do nodo atual
        ptranking->esq=Insere_Ranking_amigo (ptranking->esq, ptusuario);  //chama a mesma fun��o para a �rvore a esquerda
    else //se o n�mero de amigos do novo nodo for maior que a do nodo atual
        ptranking->dir=Insere_Ranking_amigo (ptranking->dir, ptusuario);  //chama a mesma fun��o para a �rvore a direita
    return retorno; //retorna os dados do ponteiro retorno
}

//cria uma ABP para organizar o ranking de tipo 2
void Cria_Ranking_inimigo (Tranking_popular **ptranking, Tusuario *ptusuario)
{
    if(ptusuario!=NULL) //apena executa se o ponteiro ptusuario n�o for NULL
    {
        Cria_Ranking_inimigo(ptranking,ptusuario->dir); //chama a mesma fun��o para arvore a direita
        if(ptusuario->numinimigos!=0) //apenas executa se o n�mero de rivais for diferente de 0
            *ptranking=Insere_Ranking_inimigo(*ptranking,ptusuario); //chama a fun��o de inserir ranking e guarda o retorno no ptranking
        Cria_Ranking_inimigo(ptranking,ptusuario->esq); //chama a mesma fun��o para arvore a esquerda
    }
}

//Insere os dados na �rvore usando como chave o n�mero de rivais
Tranking_popular* Insere_Ranking_inimigo (Tranking_popular *ptranking, Tusuario *ptusuario)
{
    Tranking_popular *retorno=ptranking; //declara um ponteiro
    if(ptranking==NULL) //apena executa se o ponteiro ptranking for NULL (foi encontrado o local correto para inserir o nodo)
    {
        retorno=malloc(sizeof(Tranking_popular)); //aloca espa�o na memoria
        strcpy(retorno->nome,ptusuario->nome); //armazena o nome do usuario
        retorno->num=ptusuario->numinimigos; //armazena o n�mero de rivais
        retorno->esq=NULL; //inicializa o ponteiro
        retorno->dir=NULL; //inicializa o ponteiro
    }
    else if (ptranking->num>ptusuario->numinimigos) //se o n�mero de rivais do novo nodo for menor que a do nodo atual
        ptranking->esq=Insere_Ranking_inimigo (ptranking->esq, ptusuario); //chama a mesma fun��o para arvore a esquerda
    else //se o n�mero de rivais do novo nodo for maior que a do nodo atual
        ptranking->dir=Insere_Ranking_inimigo (ptranking->dir, ptusuario); //chama a mesma fun��o para arvore a direita
    return retorno; //retorna os dados do ponteiro retorno
}

//dado uma ABP ranking, imprime o nome de todos usuario com caminhamento central a direita
void Imprime_Todos_Ranking (Tranking_popular *ptranking, FILE *saida)
{
    if(ptranking!=NULL) //apenas executa se o ponteiro n�o for NULL (nenhum dado a ser impresso)
    {
        Imprime_Todos_Ranking(ptranking->dir,saida); //chama a mesma fun��o para arvore a direita
        fprintf(saida," %s", ptranking->nome); //imprime o nome do usuario no arquivo txt
        Imprime_Todos_Ranking(ptranking->esq,saida); //chama a mesma fun��o para arvore a esquerda
    }
}

//dado uma ABP ranking, imprime um n�mero X (contigo na vari�vel top) de amigos ou rivais de um usuario
void Imprime_Ranking (Tranking_popular *ptranking, int *top, FILE *saida)
{
    if(ptranking!=NULL) //apena executa se o ponteiro ptranking n�o for NULL
    {
        Imprime_Ranking(ptranking->dir,top,saida); //chama a mesma fun��o para arvore a direita
        if(*top!=0) //executa apenas se o contador for diferente de 0
        {
            fprintf(saida, " %s", ptranking->nome); //imprime o nome do usuario
            *top=*top-1; //decrementa o contador
        }
        Imprime_Ranking(ptranking->esq,top,saida); //chama a mesma fun��o para arvore a esquerda
    }
}

//fun��o respons�vel por apagar a ABP ranking depois do uso
Tranking_popular* Exclui_Ranking (Tranking_popular *ptranking)
{
    if(ptranking!=NULL) //se o ponteiro for diferente de NULL, libera o espa�o por ele apontado
    {
        ptranking->esq=Exclui_Ranking(ptranking->esq); //chama a mesma fun��o para arvore a esquerda
        ptranking->dir=Exclui_Ranking(ptranking->dir); //chama a mesma fun��o para arvore a direita
        free(ptranking); //libera o espa�o apontado por ptranking
        ptranking=NULL; //faz ptranking apotar para NULL
    }
    return ptranking; //retorna o ponteiro ptranking
}

//consulta a existencia ou n�o de um amigo ou rival numa lista de amigos ou rivais de um usuario
Tamigo_inimigo* Consulta_amigo_inimigo (Tamigo_inimigo *t, char nome[])
{
    int comp; //declara��o de variavel do tipo inteiro
    if(t!=NULL) //se o ponteiro t for diferente de NULL, procura pela existencia do amigo ou rival
    {
        comp=strcmp(t->info->nome, nome); //faz a compara��o do nome do amigo ou rival com o nome do nodo atual e salva o resultado na variavel comp
        if(comp==0) //se for igual, o usu�rio foi encontrado
            return t; //retorna o ponteiro t
        if(comp>0) //se o nome do amigo ou rival for, por ordem alfab�tica, menor que o do nodo atual
            return Consulta_amigo_inimigo(t->esq,nome); //chama a mesma fun��o para arvore a esquerda
        else //se o nome do amigo ou rival for, por ordem alfab�tica, maior que o do nodo atual
            return Consulta_amigo_inimigo(t->dir,nome); //chama a mesma fun��o para arvore a direita
    }
    else //se o ponteiro for NULL, finaliza a busca
        return t; //retorna o ponteiro t
}

//faz rota��o a direita da AVL de amigos ou rivais
Tamigo_inimigo* rotacao_direita(Tamigo_inimigo *pt)
{
    Tamigo_inimigo* ptu;
    ptu = pt->esq;
    pt->esq = ptu->dir;
    ptu->dir = pt;
    pt->FB = 0;
    pt = ptu;
    return pt;
}

//faz rota��o a esquerda da AVL de amigos ou rivais
Tamigo_inimigo* rotacao_esquerda(Tamigo_inimigo *pt)
{
    Tamigo_inimigo* ptu;
    ptu = pt->dir;
    pt->dir = ptu->esq;
    ptu->esq = pt;
    pt->FB = 0;
    pt = ptu;
    return pt;
}

//faz rota��o dupla a direita da AVL de amigos ou rivais
Tamigo_inimigo* rotacao_dupla_direita (Tamigo_inimigo* pt)
{
    Tamigo_inimigo* ptu, *ptv;
    ptu = pt->esq;
    ptv = ptu->dir;
    ptu->dir = ptv->esq;
    ptv->esq = ptu;
    pt->esq = ptv->dir;
    ptv->dir = pt;
    if (ptv->FB == 1)   pt->FB = -1;
    else pt->FB = 0;
    if (ptv->FB == -1)  ptu->FB = 1;
    else ptu->FB = 0;
    pt = ptv;
    return pt;
}

//faz rota��o dupla a esquerda da AVL de amigos ou rivais
Tamigo_inimigo* rotacao_dupla_esquerda (Tamigo_inimigo* pt)
{
    Tamigo_inimigo *ptu, *ptv;
    ptu = pt->dir;
    ptv = ptu->esq;
    ptu->esq = ptv->dir;
    ptv->dir = ptu;
    pt->dir = ptv->esq;
    ptv->esq = pt;
    if (ptv->FB == -1) pt->FB = 1;
    else pt->FB = 0;
    if (ptv->FB == 1) ptu->FB = -1;
    else ptu->FB = 0;
    pt = ptv;
    return pt;
}


Tamigo_inimigo* Caso1 (Tamigo_inimigo* a , int *ok)
{
    Tamigo_inimigo *ptu;
    ptu = a->esq;
    if (ptu->FB == 1)
    {
        a = rotacao_direita(a);
    }
    else
    {
        a = rotacao_dupla_direita(a);
    }

    a->FB = 0;
    *ok = 0;
    return a;
}

Tamigo_inimigo* Caso2 (Tamigo_inimigo *a , int *ok)
{
    Tamigo_inimigo *ptu;
    ptu = a->dir;
    if (ptu->FB == -1)
    {
        a=rotacao_esquerda(a);
    }
    else
    {
        a=rotacao_dupla_esquerda(a);
    }
    a->FB = 0;
    *ok = 0;
    return a;
}

Tamigo_inimigo* Insere_amigo (Tamigo_inimigo *a, Tusuario *x, int *ok, FILE *saida)
{
    int comp;
    if (a == NULL)
    {
        a = (Tamigo_inimigo*) malloc(sizeof(Tamigo_inimigo));
        a->info = x;
        a->esq = NULL;
        a->dir = NULL;
        a->FB = 0;
        *ok = 1;
        fprintf(saida,"a amigo inserido com sucesso\n");
        x->numamigos+=1;
    }
    else
    {
        comp=strcmp(a->info->nome, x->nome);
        if (comp==0)
        {
            fprintf(saida,"a ERRO amigo ja inserido\n");
            return a;
        }
        else if (comp>0)
        {
            a->esq = Insere_amigo(a->esq,x,ok, saida);
            if (*ok)
            {
                switch (a->FB)
                {
                case -1:
                    a->FB = 0;
                    *ok = 0;
                    break;
                case  0:
                    a->FB = 1;
                    break;
                case  1:
                    a=Caso1(a,ok);
                    break;
                }
            }
        }
        else
        {
            a->dir = Insere_amigo(a->dir,x,ok, saida);
            if (*ok)
            {
                switch (a->FB)
                {
                case  1:
                    a->FB = 0;
                    *ok = 0;
                    break;
                case  0:
                    a->FB = -1;
                    break;
                case -1:
                    a = Caso2(a,ok);
                    break;
                }
            }
        }
    }
    return a;
}

Tamigo_inimigo* Insere_inimigo (Tamigo_inimigo *a, Tusuario *x, int *ok, FILE *saida)
{
    int comp;
    if (a == NULL)
    {
        a = (Tamigo_inimigo*) malloc(sizeof(Tamigo_inimigo));
        a->info = x;
        a->esq = NULL;
        a->dir = NULL;
        a->FB = 0;
        *ok = 1;
        fprintf(saida,"a inimigo inserido com sucesso\n");
        x->numinimigos+=1;
    }
    else
    {
        comp=strcmp(a->info->nome, x->nome);
        if (comp==0)
        {
            fprintf(saida,"a ERRO inimigo ja inserido\n");
            return a;
        }
        else if (comp>0)
        {
            a->esq = Insere_inimigo(a->esq,x,ok, saida);
            if (*ok)
            {
                switch (a->FB)
                {
                case -1:
                    a->FB = 0;
                    *ok = 0;
                    break;
                case  0:
                    a->FB = 1;
                    break;
                case  1:
                    a=Caso1(a,ok);
                    break;
                }
            }
        }
        else
        {
            a->dir = Insere_inimigo(a->dir,x,ok, saida);
            if (*ok)
            {
                switch (a->FB)
                {
                case  1:
                    a->FB = 0;
                    *ok = 0;
                    break;
                case  0:
                    a->FB = -1;
                    break;
                case -1:
                    a = Caso2(a,ok);
                    break;
                }
            }
        }
    }
    return a;
}

Tfeed* Pushfeed(Tfeed* topo, char post[], char nome[])
{
    Tfeed *novo; //novo elemento
    novo = (Tfeed*) malloc(sizeof(Tfeed)); //aloca um novo nodo
    novo->prox = NULL; //inicialisa o ponteiro como NULL
    strcpy(novo->texto, post); //insere o post
    strcpy(novo->nome, nome); //insere o nome do usuario que fez o post
    novo->prox = topo; //encaeia o elemento
    topo = novo; //encaeia o elemento

    return topo;//retorna o topo da pilha para a fun��o que a chamou
}

//fun��o respons�vel por inserir o post de um usu�rio na lista de post dos amigos ou rivis
void Insere_Post_Amigo_Inimigo(Tamigo_inimigo *t, char post[], char nome[])
{
    if(t!=NULL) //apenas executa se o ponteiro para a lista de amigos ou rivais n�o for NULL
    {
        Insere_Post_Amigo_Inimigo(t->esq, post, nome); //chama a mesma fun��o para arvore a esquerda
        t->info->ptfeed = Pushfeed(t->info->ptfeed, post,  nome); //chama a fun��o Pushfeed para inser��o do post
        Insere_Post_Amigo_Inimigo(t->dir, post, nome); //chama a mesma fun��o para arvore a direita
    }
}

//fun��o respons�vel por inserir o post de um usu�rio na lista de post de todos usu�rios da rede
void Insere_Post_Todos(Tusuario* t, char post[], char nome[])
{
    if(t!=NULL) //apenas executa se o ponteiro para usu�rio n�o for NULL
    {
        Insere_Post_Todos(t->esq, post, nome); //chama a mesma fun��o para arvore a esquerda
        t->ptfeed = Pushfeed(t->ptfeed, post, nome); //chama a fun��o Pushfeed para inser��o do post
        Insere_Post_Todos(t->dir, post, nome); //chama a mesma fun��o para arvore a direita
    }
}

//imprime todos os post de um usu�rio e de seus amigos
void Imprime_feed_todos_amigos(Tfeed* topo, Tusuario *t, int *achou, FILE* saida)
{
    if(topo!=NULL) //se a pilha de post n�o for vazia, executa a fun��o
    {
        if((!strcmp(topo->nome,t->nome))||(Consulta_amigo_inimigo(t->ptamigos, topo->nome)!=NULL)) //compara strings para verificar se o usuario que postou est� na lista de amigos
        {
            fprintf(saida,"\n\"%s\" %s", topo->texto, topo->nome); //imprime o post e o nome do usuario q o criou
            *achou=1; //flag para indicar que ao menos um post foi encotrado
        }
        Imprime_feed_todos_amigos(topo->prox, t, achou, saida); //chama a fun��o para o pr�ximo post da pilha
    }
}

//imprime todos os post de um usu�rio e de seus rivais
void Imprime_feed_todos_inimigos(Tfeed* topo, Tusuario *t, int *achou, FILE* saida)
{
    if(topo!=NULL) //se a pilha de post n�o for vazia, executa a fun��o
    {
        if((!strcmp(topo->nome,t->nome))||(Consulta_amigo_inimigo(t->ptinimigos, topo->nome)!=NULL)) //compara strings para verificar se o usuario que postou est� na lista de rivais
        {
            fprintf(saida,"\n\"%s\" %s", topo->texto, topo->nome); //imprime o post e o nome do usuario q o criou
            *achou=1; //flag para indicar que ao menos um post foi encotrado
        }
        Imprime_feed_todos_inimigos (topo->prox, t, achou, saida); //chama a fun��o para o pr�ximo post da pilha
    }
}

//imprime todos os post de um usu�rio, de seus amigos e de seus rivais
void Imprime_feed_todos_amigos_inimigos(Tfeed* topo, Tusuario *t, int *achou, FILE* saida)
{
    if(topo!=NULL) //se a pilha de post n�o for vazia, executa a fun��o
    {
        if(!strcmp(topo->nome,t->nome) ||
                (Consulta_amigo_inimigo(t->ptamigos, topo->nome)!=NULL) ||
                (Consulta_amigo_inimigo(t->ptinimigos, topo->nome)!=NULL))//compara strings para verificar se o usuario que postou est� na lista de amigos ou rivais
        {
            fprintf(saida,"\n\"%s\" %s", topo->texto, topo->nome); //imprime o post e o nome do usuario q o criou
            *achou=1; //flag para indicar que ao menos um post foi encotrado
        }
        Imprime_feed_todos_amigos_inimigos(topo->prox, t, achou, saida); //chama a fun��o para o pr�ximo post da pilha
    }
}

void Imprime_feed_amigos(Tfeed* topo, Tusuario *t, int top, int *achou, FILE* saida)
{
    if((topo!=NULL)&&(top!=0)) //se a pilha de post n�o for vazia e o contador de post n�o for 0, executa a fun��o
    {
        if((!strcmp(topo->nome,t->nome))||(Consulta_amigo_inimigo(t->ptamigos, topo->nome)!=NULL))//compara strings para verificar se o usuario que postou est� na lista de amigos
        {
            fprintf(saida,"\n\"%s\" %s", topo->texto, topo->nome); //imprime o post e o nome do usuario q o criou
            *achou=1; //flag para indicar que ao menos um post foi encotrado
        }
        Imprime_feed_amigos(topo->prox, t, top-1, achou, saida); //chama a fun��o para o pr�ximo post da pilha, decrementado o contador
    }
}

void Imprime_feed_inimigos(Tfeed* topo, Tusuario *t, int top, int *achou, FILE* saida)
{
    if((topo!=NULL)&&(top!=0)) //se a pilha de post n�o for vazia e o contador de post n�o for 0, executa a fun��o
    {
        if((!strcmp(topo->nome,t->nome))||(Consulta_amigo_inimigo(t->ptinimigos, topo->nome)!=NULL)) //compara strings para verificar se o usuario que postou est� na lista de rivais ou � o proprio usuario
        {
            fprintf(saida,"\n\"%s\" %s", topo->texto, topo->nome); //imprime o post e o nome do usuario q o criou
            *achou=1; //flag para indicar que ao menos um post foi encotrado
        }
        Imprime_feed_amigos(topo->prox, t, top-1, achou, saida); //chama a fun��o para o pr�ximo post da pilha, decrementado o contador
    }
}

void Imprime_feed_amigos_inimigos(Tfeed* topo, Tusuario *t, int top, int *achou, FILE* saida)
{
    if((topo!=NULL)&&(top!=0)) //se a pilha de post n�o for vazia e o contador de post n�o for 0, executa a fun��o
    {
        if(!strcmp(topo->nome,t->nome) ||
                (Consulta_amigo_inimigo(t->ptamigos, topo->nome)!=NULL) ||
                (Consulta_amigo_inimigo(t->ptinimigos, topo->nome)!=NULL)) //compara strings para verificar se o usuario que postou est� na lista de amigos ou rivais ou � o proprio usuario
        {
            fprintf(saida,"\n\"%s\" %s", topo->texto, topo->nome); //imprime o post e o nome do usuario q o criou
            *achou=1; //flag para indicar que ao menos um post foi encotrado
        }
        Imprime_feed_amigos_inimigos(topo->prox, t, top-1, achou, saida); //chama a fun��o para o pr�ximo post da pilha, decrementado o contador
    }
}

Tranking_circulo* Insere_ranking_circulo (Tranking_circulo *ptlista, char nome[])
{
    Tranking_circulo *novo, *aux, *aux2=NULL;
    if(ptlista==NULL)
    {
        ptlista=malloc(sizeof(Tranking_circulo));
        strcpy(ptlista->nome,nome);
        ptlista->num=1;
        ptlista->ant=NULL;
        ptlista->prox=NULL;
    }
    else
    {
        aux=ptlista;
        while((aux!=NULL)&&((strcmp(aux->nome,nome))!=0))
        {
            aux2=aux;
            aux=aux->prox;
        }
        if(aux==NULL)
        {
            novo=malloc(sizeof(Tranking_circulo));
            strcpy(novo->nome,nome);
            novo->num=1;
            novo->ant=aux2;
            aux2->prox=novo;
            novo->prox=NULL;
        }
        else
        {
            aux->num+=1;
            while((aux->ant!=NULL)&&(aux->ant->num<aux->num))
            {
                aux2=aux->ant->ant;
                aux->ant->prox=aux->prox;
                if(aux->prox!=NULL)
                    aux->prox->ant=aux->ant;
                aux->prox=aux->ant;
                aux->ant->ant=aux;
                if(aux2!=NULL)
                    aux2->prox=aux;
                aux->ant=aux2;
            }
            if(aux->prox==ptlista)
                ptlista=aux;
        }
    }
    return ptlista;
}

Tranking_circulo* Exclui_ranking_circulo (Tranking_circulo *ptlista)
{
    if(ptlista!=NULL)
    {
        while(ptlista->prox!=NULL)
        {
            ptlista=ptlista->prox;
            free(ptlista->ant);
            ptlista->ant=NULL;
        }
        free(ptlista);
        ptlista=NULL;
    }
    return ptlista;
}

void Percorre_amigos_circular(Tamigo_inimigo *t, Tranking_circulo **ptlista)
{
    if(t!=NULL) //apenas executa se o ponteiro para usu�rio n�o for NULL
    {
        Percorre_amigos_circular(t->esq, ptlista); //chama a mesma fun��o para arvore a esquerda
        Percorre_amigos_amigos_circular(t->info->ptamigos, ptlista);
        Percorre_amigos_circular(t->dir, ptlista); //chama a mesma fun��o para arvore a direita
    }
}

void Percorre_amigos_amigos_circular(Tamigo_inimigo *t, Tranking_circulo **ptlista)
{
    if(t!=NULL) //apenas executa se o ponteiro para usu�rio n�o for NULL
    {
        Percorre_amigos_amigos_circular(t->esq, ptlista); //chama a mesma fun��o para arvore a esquerda
        (*ptlista) = Insere_ranking_circulo ((*ptlista), t->info->nome);
        Percorre_amigos_amigos_circular(t->dir, ptlista); //chama a mesma fun��o para arvore a direita
    }
}

void Percorre_rivais_circular(Tamigo_inimigo *t, Tranking_circulo **ptlista)
{
    if(t!=NULL) //apenas executa se o ponteiro para usu�rio n�o for NULL
    {
        Percorre_rivais_circular(t->esq, ptlista); //chama a mesma fun��o para arvore a esquerda
        Percorre_rivais_rivais_circular(t->info->ptamigos, ptlista);
        Percorre_rivais_circular(t->dir, ptlista); //chama a mesma fun��o para arvore a direita
    }
}

void Percorre_rivais_rivais_circular(Tamigo_inimigo *t, Tranking_circulo **ptlista)
{
    if(t!=NULL) //apenas executa se o ponteiro para usu�rio n�o for NULL
    {
        Percorre_rivais_rivais_circular(t->esq, ptlista); //chama a mesma fun��o para arvore a esquerda
        (*ptlista) = Insere_ranking_circulo ((*ptlista), t->info->nome);
        Percorre_rivais_rivais_circular(t->dir, ptlista); //chama a mesma fun��o para arvore a direita
    }
}

void Imprime_todos_ranking_circulo (Tranking_circulo *ptlista, FILE *saida)
{
    while(ptlista!=NULL)
    {
        fprintf(saida," %s", ptlista->nome);
        ptlista=ptlista->prox;
    }
}

void Imprime_ranking_circulo (Tranking_circulo *ptlista, int top, FILE *saida)
{
    while((ptlista!=NULL) && (top!=0))
    {
        fprintf(saida," %s", ptlista->nome);
        ptlista=ptlista->prox;
        top--;
    }
}

