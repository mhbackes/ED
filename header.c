//Claudio Rodrigo Gisch   Nº228366
//Marcos Henrique Backes  Nº228483

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

//função responsavel por alocar e armazenar os dados do novo usuario
Tusuario* Novo(char nome[], Tusuario* esq, Tusuario* dir)
{
    Tusuario* novo = (Tusuario*) malloc(sizeof(Tusuario)); //aloca espaço na memoria
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

//chama função splay para inserção do novo usuário
Tusuario* Insere_Usuario(Tusuario *t, char nome[], FILE *saida)
{
    Tusuario *retorno=Splay(t,nome, saida);
    return retorno;
};

//função responsável por organizar a arvore de usuários
Tusuario* Splay(Tusuario* t, char nome[], FILE *saida)
{
    Tusuario *retorno;
    if (t == NULL) //arvore vazia
    {
        retorno=Novo(nome,NULL,NULL); //insere o novo usuário
        fprintf(saida,"i usuario inserido com sucesso\n"); //imprime o resultado no arquivo texto
    }
    else //não vazia
    {
        if (!strcmp(nome,t->nome)) //verifica se o usuario esta cadastrado
        {
            fprintf(saida,"i ERRO: Usuario ja cadastrado\n"); //imprime uma mensagem de erro no arquivo texto
            retorno=t; //retorna o ponteiro da arvore de usuarios
        }
        else
        {
            if (strcmp(nome,t->nome)<0) //procura o local para a inserção do novo usuario
            {
                if (t->esq == NULL) //nodo a esquerda está disponível
                {
                    retorno=Novo(nome,NULL,t); //insere o novo usuario
                    fprintf(saida,"i usuario inserido com sucesso\n"); //imprime o resultado no arquivo texto
                }
                else
                {
                    if (!strcmp(nome,t->esq->nome))//verifica se o usuario esta cadastrado
                    {
                        fprintf(saida,"i ERRO: Usuario ja cadastrado\n"); //imprime uma mensagem de erro no arquivo texto
                        retorno=RotDir(t); //faz rotação a direita
                    }
                    else
                    {
                        if (strcmp(nome,t->esq->nome)<0) //procura o local para a inserção do novo usuario
                        {
                            t->esq->esq = Splay(t->esq->esq, nome,saida); //chama a mesma função
                            t = RotDir(t); //faz rotação a direita
                        }
                        else
                        {
                            t->esq->dir = Splay(t->esq->dir, nome,saida); //chama a mesma função
                            t->esq = RotEsq(t->esq); //faz rotação a esquerda
                        }
                        retorno=RotDir(t); //faz rotação a direita
                    }
                }
            }
            else
            {
                if (t->dir == NULL) //nodo da direita está disponivel
                {
                    retorno=Novo(nome,t,NULL);  //insere o novo usuario
                    fprintf(saida,"i usuario inserido com sucesso\n"); //imprime o resultado no arquivo texto
                }
                else
                {
                    if (!strcmp(nome,t->dir->nome)) //verifica se o usuario esta cadastrado
                    {
                        fprintf(saida,"i ERRO: Usuario ja cadastrado\n"); //imprime uma mensagem de erro no arquivo texto
                        retorno=RotEsq(t); //faz rotação a esquerda
                    }
                    else
                    {
                        if (strcmp(nome,t->dir->nome)>0) //procura o local para a inserção do novo usuario
                        {
                            t->dir->dir = Splay(t->dir->dir, nome,saida); //chama a mesma função
                            t = RotEsq(t); //faz rotação a esquerda
                        }
                        else
                        {
                            t->dir->esq = Splay(t->dir->esq, nome,saida); //chama a mesma função
                            t->dir = RotDir(t->dir); //faz rotação a direita
                        }
                        retorno=RotEsq(t); //faz rotação as esquerda
                    }
                }
            }
        }
    }
    return retorno; //retorna o ponteiro retorno
};

//faz rotação para direita
Tusuario* RotDir(Tusuario* t)
{
    Tusuario* x = t->esq;
    t->esq = x->dir;
    x->dir = t;
    return x;
};

//faz rotação para esquerda
Tusuario* RotEsq(Tusuario* t)
{
    Tusuario* x = t->dir;
    t->dir = x->esq;
    x->esq = t;
    return x;
};

//função responsável por exibir os usuários em ordem alfabética
void Exibe_Usuarios_Cresc(Tusuario *t, int *top, FILE *saida)
{
    if(t!=NULL) //apenas executa se o ponteiro para usuário não for NULL
    {
        Exibe_Usuarios_Cresc(t->esq,top,saida); //chama a mesma função para arvore a esquerda
        if(*top!=0) //equanto o contador for diferente de 0, continua
        {
            fprintf(saida, " %s", t->nome); //imprime o nome do usuário
            *top=*top-1; //decrementa o contador
        }
        Exibe_Usuarios_Cresc(t->dir,top,saida); //chama a mesma função para arvore a direita
    }
}

//função responsável por exibir os usuários em ordem inversa à alfabética
void Exibe_Usuarios_Decresc(Tusuario *t, int *top, FILE *saida)
{
    if(t!=NULL) //apenas executa se o ponteiro para usuário não for NULL
    {
        Exibe_Usuarios_Decresc(t->dir,top,saida); //chama a mesma função para arvore a direita
        if(*top!=0) //equanto o contador for diferente de 0, continua
        {
            fprintf(saida, " %s", t->nome); //imprime o nome do usuário
            *top=*top-1; //decrementa o contador
        }
        Exibe_Usuarios_Decresc(t->esq,top,saida); //chama a mesma função para arvore a esquerda
    }
}

//função responsável por exibir todos os usuários em ordem alfabética
void Exibe_Todos_Usuarios_Cresc(Tusuario *t, FILE *saida)
{
    if(t!=NULL) //apenas executa se o ponteiro para usuário não for NULL
    {
        Exibe_Todos_Usuarios_Cresc(t->esq,saida); //chama a mesma função para arvore a esquerda
        fprintf(saida, " %s", t->nome); //imprime o nome do usuário
        Exibe_Todos_Usuarios_Cresc(t->dir,saida); //chama a mesma função para arvore a direita
    }
}

//função responsável por exibir os usuários em ordem inversa à alfabética
void Exibe_Todos_Usuarios_Decresc(Tusuario *t, FILE *saida)
{
    if(t!=NULL) //apenas executa se o ponteiro para usuário não for NULL
    {
        Exibe_Todos_Usuarios_Decresc(t->dir,saida); //chama a mesma função para arvore a direita
        fprintf(saida, " %s", t->nome); //imprime o nome do usuário
        Exibe_Todos_Usuarios_Decresc(t->esq,saida); //chama a mesma função para arvore a esquerda
    }
}

//função responsável por verificar a existência ou não de um usuário
Tusuario* Consulta_Usuario(Tusuario* t, char nome[])
{
    Tusuario* retorno;
    if (t==NULL) //se o ponteiro for NULL, retorna NULL (lista de usuários vazia)
        retorno=NULL;
    else if (strcmp(nome, t->nome)<0) //compara nome do nodo atual com o nome a ser procurado
    {
        if (t->esq == NULL)
            retorno=t;
        else if (strcmp(nome, t->esq->nome)<0) //compara nome do nodo atual com o nome a ser procurado
        {
            t->esq->esq = Consulta_Usuario(t->esq->esq, nome); // chama a mesma função
            t = RotDir(t); //rotação a direita
            if (t->esq == NULL)
                retorno=t;
            else
                retorno=RotDir(t); //rotação a direita
        }
        else if (strcmp(t->esq->nome,nome)<0) //compara nome do nodo atual com o nome a ser procurado
        {
            t->esq->dir = Consulta_Usuario(t->esq->dir, nome); //chama a mesma função
            if (t->esq->dir != NULL)
                t->esq = RotEsq(t->esq); //rotação a esquerda
            retorno=RotDir(t); //rotação a direita
        }
        else
            retorno=RotDir(t); //rotação a direita
    }
    else if(strcmp(t->nome, nome)<0) //compara nome do nodo atual com o nome a ser procurado
    {
        if (t->dir == NULL)
            retorno=t;
        else if (strcmp(t->dir->nome,nome)<0) //compara nome do nodo atual com o nome a ser procurado
        {
            t->dir->dir = Consulta_Usuario(t->dir->dir, nome); // chama a mesma fução
            t = RotEsq(t); //rotação a esquerda
            if (t->dir == NULL)
                retorno=t;
            else
                retorno=RotEsq(t); //rotação a esquerda
        }
        else if (strcmp(nome,t->dir->nome)<0) //compara nome do nodo atual com o nome a ser procurado
        {
            t->dir->esq = Consulta_Usuario(t->dir->esq, nome); //chama a mesma função
            if (t->dir->esq != NULL) t->dir = RotDir(t->dir); //rotação a direita
            retorno=RotEsq(t); //rotação a esquerda
        }
        else
            retorno=RotEsq(t); //rotação a esquerda
    }
    else
        retorno=t;
    return retorno; //retorna o ponteiro retorno
};

//função responsável pela impressão dos amigos ou rivais de um dado usuário t
void Exibe_Amigos(Tusuario* t, int tipo, int top, FILE *saida)
{
    fprintf(saida,"m"); //imprime o código da operação no arquivo txt
    if (top == 0) //se o top for 0, imprime todos os amigos ou rivais do usuário t
    {
        if (tipo == 1) //se tipo for 1, então imprime todos amigos do usuario t
        {
            if (t->ptamigos == NULL) //caso o ponteiro para a lista de amigos seja nula, a lista esta vazia
            {
                fprintf(saida," ERRO nenhum amigo cadastrado"); //mensagem de erro impresso no arquivo txt
            }
            else //se não estiver vazia, imprime todos amigos da lista
            {
                Exibe_Todos_Amigos_Cresc(t->ptamigos, saida); //chamada da função
            }
        }
        else //se o tipo for 2,  então imprime todos os rivais do usuario t
        {
            if (t->ptinimigos == NULL) //caso o ponteiro para a lista de rivais seja nula, a lista esta vazia
            {
                fprintf(saida," ERRO nenhum rival cadastrado"); //mensagem de erro impresso no arquivo txt
            }
            else //se não estiver vazia, imprime todos rivais da lista
            {
                Exibe_Todos_Amigos_Cresc(t->ptinimigos, saida); //chamada da função
            }
        }
    }
    else
    {
        if (tipo == 1) //se tipo for 1, então imprime o número contigo em top de amigos do usuario t
        {
            if (t->ptamigos == NULL) //caso o ponteiro para a lista de amigos seja nula, a lista esta vazia
            {
                fprintf(saida," ERRO nenhum amigo cadastrado"); //mensagem de erro impresso no arquivo txt
            }
            else //se não estiver vazia, imprime o número contigo em top de amigos da lista
            {
                Exibe_Amigos_Cresc(t->ptamigos, &top, saida); //chamada da função
            }
        }
        else //se o tipo for 2,  então imprime o número contigo em top de rivais do usuario t
        {
            if (t->ptinimigos == NULL) //caso o ponteiro para a lista de rivais seja nula, a lista esta vazia
            {
                fprintf(saida," ERRO nenhum rival cadastrado"); //mensagem de erro impresso no arquivo txt
            }
            else //se não estiver vazia, imprime o número contigo em top de rivais da lista
            {
                Exibe_Amigos_Cresc(t->ptinimigos, &top, saida); //chamada da função
            }
        }
    }
    fprintf(saida,"\n"); //imprime um "Enter" no arquivo txt
}

//função responsável por imprimir todos amigos ou rivais de um usuario
void Exibe_Todos_Amigos_Cresc(Tamigo_inimigo *t, FILE *saida)
{
    if(t!=NULL) //apena executa se o ponteiro t não for NULL
    {
        Exibe_Todos_Amigos_Cresc(t->esq, saida); //chama a mesma função para arvore a esquerda
        fprintf(saida, " %s", t->info->nome); //imprime o nome do amigo ou rival
        Exibe_Todos_Amigos_Cresc(t->dir, saida); //chama a mesma função para arvore a direita
    }
}

//função responsável por imprimir um número X (contigo na variável top) de amigos ou rivais de um usuario
void Exibe_Amigos_Cresc(Tamigo_inimigo *t, int *top, FILE *saida)
{
    if(t!=NULL) //apena executa se o ponteiro t não for NULL
    {
        Exibe_Amigos_Cresc(t->esq,top, saida); //chama a mesma função para arvore a esquerda
        if(*top!=0) //executa apenas se o contador for diferente de 0
        {
            fprintf(saida, " %s", t->info->nome); //imprime o nome do amigo ou rival
            *top=*top-1; //decrementa o contador
        }
        Exibe_Amigos_Cresc(t->dir,top, saida); //chama a mesma função para arvore a direita
    }
}

//cria uma ABP para organizar o ranking de tipo 0
void Cria_Ranking_amigo_inimigo (Tranking_popular **ptranking, Tusuario *ptusuario)
{
    if(ptusuario!=NULL) //apena executa se o ponteiro ptusuario não for NULL
    {
        Cria_Ranking_amigo_inimigo(ptranking,ptusuario->dir); //chama a mesma função para arvore a direita
        if(((ptusuario->numamigos)+(ptusuario->numinimigos))!=0) //apenas executa se a soma do número de amigos e rivais for diferente de 0
            *ptranking=Insere_Ranking_amigo_inimigo(*ptranking,ptusuario); //chama a função de inserir ranking e guarda o retorno no ptranking
        Cria_Ranking_amigo_inimigo(ptranking,ptusuario->esq); //chama a mesma função para arvore a esquerda
    }
}

//Insere os dados na árvore usando como chave a soma do número de amigos e rivais
Tranking_popular* Insere_Ranking_amigo_inimigo (Tranking_popular *ptranking, Tusuario *ptusuario)
{
    Tranking_popular *retorno=ptranking; //declara um ponteiro
    if(ptranking==NULL) //apena executa se o ponteiro ptranking for NULL (foi encontrado o local correto para inserir o nodo)
    {
        retorno=malloc(sizeof(Tranking_popular)); //aloca espaço na memoria
        strcpy(retorno->nome,ptusuario->nome); //armazena o nome do usuario
        retorno->num=(ptusuario->numamigos)+(ptusuario->numinimigos); //armazena a soma do número de amigos e rivais
        retorno->esq=NULL; //inicializa o ponteiro
        retorno->dir=NULL; //inicializa o ponteiro
    }
    else if (ptranking->num>((ptusuario->numamigos)+(ptusuario->numinimigos))) //se a soma do número de amigos e rivais do novo nodo for menor que a do nodo atual
        ptranking->esq=Insere_Ranking_amigo_inimigo(ptranking->esq, ptusuario); //chama a mesma função para a árvore a esquerda
    else //se a soma do número de amigos e rivais do novo nodo for maior que a do nodo atual
        ptranking->dir=Insere_Ranking_amigo_inimigo(ptranking->dir, ptusuario); //chama a mesma função para a árvore a direita
    return retorno; //retorna os dados do ponteiro retorno
}

//cria uma ABP para organizar o ranking de tipo 1
void Cria_Ranking_amigo (Tranking_popular **ptranking, Tusuario *ptusuario)
{
    if(ptusuario!=NULL) //apena executa se o ponteiro ptusuario não for NULL
    {
        Cria_Ranking_amigo(ptranking,ptusuario->dir); //chama a mesma função para arvore a direita
        if(ptusuario->numamigos!=0) //apenas executa se o número de amigos for diferente de 0
            *ptranking=Insere_Ranking_amigo(*ptranking,ptusuario); //chama a função de inserir ranking e guarda o retorno no ptranking
        Cria_Ranking_amigo(ptranking,ptusuario->esq); //chama a mesma função para arvore a esquerda
    }
}

//Insere os dados na árvore usando como chave o número de amigos
Tranking_popular* Insere_Ranking_amigo (Tranking_popular *ptranking, Tusuario *ptusuario)
{
    Tranking_popular *retorno=ptranking; //declara um ponteiro
    if(ptranking==NULL) //apena executa se o ponteiro ptranking for NULL (foi encontrado o local correto para inserir o nodo)
    {
        retorno=malloc(sizeof(Tranking_popular)); //aloca espaço na memoria
        strcpy(retorno->nome,ptusuario->nome); //armazena o nome do usuario
        retorno->num=ptusuario->numamigos; //armazena o número de amigos
        retorno->esq=NULL; //inicializa o ponteiro
        retorno->dir=NULL; //inicializa o ponteiro
    }
    else if (ptranking->num>ptusuario->numamigos) //se o número de amigos do novo nodo for menor que a do nodo atual
        ptranking->esq=Insere_Ranking_amigo (ptranking->esq, ptusuario);  //chama a mesma função para a árvore a esquerda
    else //se o número de amigos do novo nodo for maior que a do nodo atual
        ptranking->dir=Insere_Ranking_amigo (ptranking->dir, ptusuario);  //chama a mesma função para a árvore a direita
    return retorno; //retorna os dados do ponteiro retorno
}

//cria uma ABP para organizar o ranking de tipo 2
void Cria_Ranking_inimigo (Tranking_popular **ptranking, Tusuario *ptusuario)
{
    if(ptusuario!=NULL) //apena executa se o ponteiro ptusuario não for NULL
    {
        Cria_Ranking_inimigo(ptranking,ptusuario->dir); //chama a mesma função para arvore a direita
        if(ptusuario->numinimigos!=0) //apenas executa se o número de rivais for diferente de 0
            *ptranking=Insere_Ranking_inimigo(*ptranking,ptusuario); //chama a função de inserir ranking e guarda o retorno no ptranking
        Cria_Ranking_inimigo(ptranking,ptusuario->esq); //chama a mesma função para arvore a esquerda
    }
}

//Insere os dados na árvore usando como chave o número de rivais
Tranking_popular* Insere_Ranking_inimigo (Tranking_popular *ptranking, Tusuario *ptusuario)
{
    Tranking_popular *retorno=ptranking; //declara um ponteiro
    if(ptranking==NULL) //apena executa se o ponteiro ptranking for NULL (foi encontrado o local correto para inserir o nodo)
    {
        retorno=malloc(sizeof(Tranking_popular)); //aloca espaço na memoria
        strcpy(retorno->nome,ptusuario->nome); //armazena o nome do usuario
        retorno->num=ptusuario->numinimigos; //armazena o número de rivais
        retorno->esq=NULL; //inicializa o ponteiro
        retorno->dir=NULL; //inicializa o ponteiro
    }
    else if (ptranking->num>ptusuario->numinimigos) //se o número de rivais do novo nodo for menor que a do nodo atual
        ptranking->esq=Insere_Ranking_inimigo (ptranking->esq, ptusuario); //chama a mesma função para arvore a esquerda
    else //se o número de rivais do novo nodo for maior que a do nodo atual
        ptranking->dir=Insere_Ranking_inimigo (ptranking->dir, ptusuario); //chama a mesma função para arvore a direita
    return retorno; //retorna os dados do ponteiro retorno
}

//dado uma ABP ranking, imprime o nome de todos usuario com caminhamento central a direita
void Imprime_Todos_Ranking (Tranking_popular *ptranking, FILE *saida)
{
    if(ptranking!=NULL) //apenas executa se o ponteiro não for NULL (nenhum dado a ser impresso)
    {
        Imprime_Todos_Ranking(ptranking->dir,saida); //chama a mesma função para arvore a direita
        fprintf(saida," %s", ptranking->nome); //imprime o nome do usuario no arquivo txt
        Imprime_Todos_Ranking(ptranking->esq,saida); //chama a mesma função para arvore a esquerda
    }
}

//dado uma ABP ranking, imprime um número X (contigo na variável top) de amigos ou rivais de um usuario
void Imprime_Ranking (Tranking_popular *ptranking, int *top, FILE *saida)
{
    if(ptranking!=NULL) //apena executa se o ponteiro ptranking não for NULL
    {
        Imprime_Ranking(ptranking->dir,top,saida); //chama a mesma função para arvore a direita
        if(*top!=0) //executa apenas se o contador for diferente de 0
        {
            fprintf(saida, " %s", ptranking->nome); //imprime o nome do usuario
            *top=*top-1; //decrementa o contador
        }
        Imprime_Ranking(ptranking->esq,top,saida); //chama a mesma função para arvore a esquerda
    }
}

//função responsável por apagar a ABP ranking depois do uso
Tranking_popular* Exclui_Ranking (Tranking_popular *ptranking)
{
    if(ptranking!=NULL) //se o ponteiro for diferente de NULL, libera o espaço por ele apontado
    {
        ptranking->esq=Exclui_Ranking(ptranking->esq); //chama a mesma função para arvore a esquerda
        ptranking->dir=Exclui_Ranking(ptranking->dir); //chama a mesma função para arvore a direita
        free(ptranking); //libera o espaço apontado por ptranking
        ptranking=NULL; //faz ptranking apotar para NULL
    }
    return ptranking; //retorna o ponteiro ptranking
}

//consulta a existencia ou não de um amigo ou rival numa lista de amigos ou rivais de um usuario
Tamigo_inimigo* Consulta_amigo_inimigo (Tamigo_inimigo *t, char nome[])
{
    int comp; //declaração de variavel do tipo inteiro
    if(t!=NULL) //se o ponteiro t for diferente de NULL, procura pela existencia do amigo ou rival
    {
        comp=strcmp(t->info->nome, nome); //faz a comparação do nome do amigo ou rival com o nome do nodo atual e salva o resultado na variavel comp
        if(comp==0) //se for igual, o usuário foi encontrado
            return t; //retorna o ponteiro t
        if(comp>0) //se o nome do amigo ou rival for, por ordem alfabética, menor que o do nodo atual
            return Consulta_amigo_inimigo(t->esq,nome); //chama a mesma função para arvore a esquerda
        else //se o nome do amigo ou rival for, por ordem alfabética, maior que o do nodo atual
            return Consulta_amigo_inimigo(t->dir,nome); //chama a mesma função para arvore a direita
    }
    else //se o ponteiro for NULL, finaliza a busca
        return t; //retorna o ponteiro t
}

//faz rotação a direita da AVL de amigos ou rivais
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

//faz rotação a esquerda da AVL de amigos ou rivais
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

//faz rotação dupla a direita da AVL de amigos ou rivais
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

//faz rotação dupla a esquerda da AVL de amigos ou rivais
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

//adiciona um novo amigo a lista de amigos
Tamigo_inimigo* Insere_amigo (Tamigo_inimigo *a, Tusuario *x, int *ok, FILE *saida)
{
    int comp;
    if (a == NULL) //se for NULL, insere o novo amigo
    {
        //atualização dos dados do amigo
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
        //verifica se o amigo já foi inserido
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

//adiciona um novo rival a lista de inimigos
Tamigo_inimigo* Insere_inimigo (Tamigo_inimigo *a, Tusuario *x, int *ok, FILE *saida)
{
    int comp;
    if (a == NULL) //se for NULL, insere o novo rival
    {
        //atualização dos dados do amigo
        a = (Tamigo_inimigo*) malloc(sizeof(Tamigo_inimigo));
        a->info = x;
        a->esq = NULL;
        a->dir = NULL;
        a->FB = 0;
        *ok = 1;
        fprintf(saida,"a rival inserido com sucesso\n");
        x->numinimigos+=1;
    }
    else
    {
        //verifica se o amigo já foi inserido
        comp=strcmp(a->info->nome, x->nome);
        if (comp==0)
        {
            fprintf(saida,"a ERRO rival ja inserido\n");
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

    return topo;//retorna o topo da pilha para a função que a chamou
}

//função responsável por inserir o post de um usuário na lista de post dos amigos ou rivis
void Insere_Post_Amigo_Inimigo(Tamigo_inimigo *t, char post[], char nome[])
{
    if(t!=NULL) //apenas executa se o ponteiro para a lista de amigos ou rivais não for NULL
    {
        Insere_Post_Amigo_Inimigo(t->esq, post, nome); //chama a mesma função para arvore a esquerda
        t->info->ptfeed = Pushfeed(t->info->ptfeed, post,  nome); //chama a função Pushfeed para inserção do post
        Insere_Post_Amigo_Inimigo(t->dir, post, nome); //chama a mesma função para arvore a direita
    }
}

//função responsável por inserir o post de um usuário na lista de post de todos usuários da rede
void Insere_Post_Todos(Tusuario* t, char post[], char nome[])
{
    if(t!=NULL) //apenas executa se o ponteiro para usuário não for NULL
    {
        Insere_Post_Todos(t->esq, post, nome); //chama a mesma função para arvore a esquerda
        t->ptfeed = Pushfeed(t->ptfeed, post, nome); //chama a função Pushfeed para inserção do post
        Insere_Post_Todos(t->dir, post, nome); //chama a mesma função para arvore a direita
    }
}

//imprime todos os post de um usuário e de seus amigos
void Imprime_feed_todos_amigos(Tfeed* topo, Tusuario *t, int *achou, FILE* saida)
{
    if(topo!=NULL) //se a pilha de post não for vazia, executa a função
    {
        if((!strcmp(topo->nome,t->nome))||(Consulta_amigo_inimigo(t->ptamigos, topo->nome)!=NULL)) //compara strings para verificar se o usuario que postou está na lista de amigos
        {
            fprintf(saida,"\n\"%s\" %s", topo->texto, topo->nome); //imprime o post e o nome do usuario q o criou
            *achou=1; //flag para indicar que ao menos um post foi encotrado
        }
        Imprime_feed_todos_amigos(topo->prox, t, achou, saida); //chama a função para o próximo post da pilha
    }
}

//imprime todos os post de um usuário e de seus rivais
void Imprime_feed_todos_inimigos(Tfeed* topo, Tusuario *t, int *achou, FILE* saida)
{
    if(topo!=NULL) //se a pilha de post não for vazia, executa a função
    {
        if((!strcmp(topo->nome,t->nome))||(Consulta_amigo_inimigo(t->ptinimigos, topo->nome)!=NULL)) //compara strings para verificar se o usuario que postou está na lista de rivais
        {
            fprintf(saida,"\n\"%s\" %s", topo->texto, topo->nome); //imprime o post e o nome do usuario q o criou
            *achou=1; //flag para indicar que ao menos um post foi encotrado
        }
        Imprime_feed_todos_inimigos (topo->prox, t, achou, saida); //chama a função para o próximo post da pilha
    }
}

//imprime todos os post de um usuário, de seus amigos e de seus rivais
void Imprime_feed_todos_amigos_inimigos(Tfeed* topo, Tusuario *t, int *achou, FILE* saida)
{
    if(topo!=NULL) //se a pilha de post não for vazia, executa a função
    {
        if(!strcmp(topo->nome,t->nome) ||
                (Consulta_amigo_inimigo(t->ptamigos, topo->nome)!=NULL) ||
                (Consulta_amigo_inimigo(t->ptinimigos, topo->nome)!=NULL))//compara strings para verificar se o usuario que postou está na lista de amigos ou rivais
        {
            fprintf(saida,"\n\"%s\" %s", topo->texto, topo->nome); //imprime o post e o nome do usuario q o criou
            *achou=1; //flag para indicar que ao menos um post foi encotrado
        }
        Imprime_feed_todos_amigos_inimigos(topo->prox, t, achou, saida); //chama a função para o próximo post da pilha
    }
}

void Imprime_feed_amigos(Tfeed* topo, Tusuario *t, int top, int *achou, FILE* saida)
{
    if((topo!=NULL)&&(top!=0)) //se a pilha de post não for vazia e o contador de post não for 0, executa a função
    {
        if((!strcmp(topo->nome,t->nome))||(Consulta_amigo_inimigo(t->ptamigos, topo->nome)!=NULL))//compara strings para verificar se o usuario que postou está na lista de amigos
        {
            fprintf(saida,"\n\"%s\" %s", topo->texto, topo->nome); //imprime o post e o nome do usuario q o criou
            *achou=1; //flag para indicar que ao menos um post foi encotrado
        }
        Imprime_feed_amigos(topo->prox, t, top-1, achou, saida); //chama a função para o próximo post da pilha, decrementado o contador
    }
}

void Imprime_feed_inimigos(Tfeed* topo, Tusuario *t, int top, int *achou, FILE* saida)
{
    if((topo!=NULL)&&(top!=0)) //se a pilha de post não for vazia e o contador de post não for 0, executa a função
    {
        if((!strcmp(topo->nome,t->nome))||(Consulta_amigo_inimigo(t->ptinimigos, topo->nome)!=NULL)) //compara strings para verificar se o usuario que postou está na lista de rivais ou é o proprio usuario
        {
            fprintf(saida,"\n\"%s\" %s", topo->texto, topo->nome); //imprime o post e o nome do usuario q o criou
            *achou=1; //flag para indicar que ao menos um post foi encotrado
        }
        Imprime_feed_amigos(topo->prox, t, top-1, achou, saida); //chama a função para o próximo post da pilha, decrementado o contador
    }
}

void Imprime_feed_amigos_inimigos(Tfeed* topo, Tusuario *t, int top, int *achou, FILE* saida)
{
    if((topo!=NULL)&&(top!=0)) //se a pilha de post não for vazia e o contador de post não for 0, executa a função
    {
        if(!strcmp(topo->nome,t->nome) ||
                (Consulta_amigo_inimigo(t->ptamigos, topo->nome)!=NULL) ||
                (Consulta_amigo_inimigo(t->ptinimigos, topo->nome)!=NULL)) //compara strings para verificar se o usuario que postou está na lista de amigos ou rivais ou é o proprio usuario
        {
            fprintf(saida,"\n\"%s\" %s", topo->texto, topo->nome); //imprime o post e o nome do usuario q o criou
            *achou=1; //flag para indicar que ao menos um post foi encotrado
        }
        Imprime_feed_amigos_inimigos(topo->prox, t, top-1, achou, saida); //chama a função para o próximo post da pilha, decrementado o contador
    }
}

//função responsável por atualizar a lista de ranking circular
Tranking_circulo* Insere_ranking_circulo (Tranking_circulo *ptlista, char nome[])
{
    Tranking_circulo *novo, *aux, *aux2=NULL; //variaveis
    if(ptlista==NULL) //se a lista for NULL, insere novo usuario
    {
        //inicializa os dados do usuario
        ptlista=malloc(sizeof(Tranking_circulo));
        strcpy(ptlista->nome,nome);
        ptlista->num=1;
        ptlista->ant=NULL;
        ptlista->prox=NULL;
    }
    else
    //verifica se o usuario já está na lista
    {
        aux=ptlista;
        while((aux!=NULL)&&((strcmp(aux->nome,nome))!=0)) //executa o laço até encontrar um espaço vazio ou até achar o usuario na lista
        {
            aux2=aux;
            aux=aux->prox;
        }
        if(aux==NULL) //se aux for NULL, o usuario não está na lista, portanto é inserido nela
        {
            novo=malloc(sizeof(Tranking_circulo));
            strcpy(novo->nome,nome);
            novo->num=1;
            novo->ant=aux2;
            aux2->prox=novo;
            novo->prox=NULL;
        }
        else //se nao for NULL, o usuario está na lista e se incrementa o numero de vezes que ele aparece
        {
            aux->num+=1;
            //verifica se ele, com essa atualização, o usuario ficou mais popular que outro da lista
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

//função para liberar o espaço, alocado para a função circulo, depois de sua execução
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

//responsável por chamar para cada amigo do usuario t, uma função recursiva
void Percorre_amigos_circular(Tamigo_inimigo *t, Tranking_circulo **ptlista)
{
    if(t!=NULL) //apenas executa se o ponteiro para usuário não for NULL
    {
        Percorre_amigos_circular(t->esq, ptlista); //chama a mesma função para arvore a esquerda
        Percorre_amigos_amigos_circular(t->info->ptamigos, ptlista); //chama a função recursiva
        Percorre_amigos_circular(t->dir, ptlista); //chama a mesma função para arvore a direita
    }
}

//responsável por percorrer uma lista de amigos e chamar a função de atualzação da lista popular para cada um dos amigos
void Percorre_amigos_amigos_circular(Tamigo_inimigo *t, Tranking_circulo **ptlista)
{
    if(t!=NULL) //apenas executa se o ponteiro para usuário não for NULL
    {
        Percorre_amigos_amigos_circular(t->esq, ptlista); //chama a mesma função para arvore a esquerda
        (*ptlista) = Insere_ranking_circulo ((*ptlista), t->info->nome); //chama a função insere para atualizar a lista
        Percorre_amigos_amigos_circular(t->dir, ptlista); //chama a mesma função para arvore a direita
    }
}

//responsável por chamar para cada rival do usuario t, uma função recursiva
void Percorre_rivais_circular(Tamigo_inimigo *t, Tranking_circulo **ptlista)
{
    if(t!=NULL) //apenas executa se o ponteiro para usuário não for NULL
    {
        Percorre_rivais_circular(t->esq, ptlista); //chama a mesma função para arvore a esquerda
        Percorre_rivais_rivais_circular(t->info->ptinimigos, ptlista); //chama a função recursiva
        Percorre_rivais_circular(t->dir, ptlista); //chama a mesma função para arvore a direita
    }
}

//responsável por percorrer uma lista de rivais e chamar a função de atualzação da lista popular para cada um dos rivais
void Percorre_rivais_rivais_circular(Tamigo_inimigo *t, Tranking_circulo **ptlista)
{
    if(t!=NULL) //apenas executa se o ponteiro para usuário não for NULL
    {
        Percorre_rivais_rivais_circular(t->esq, ptlista); //chama a mesma função para arvore a esquerda
        (*ptlista) = Insere_ranking_circulo ((*ptlista), t->info->nome); //chama a função insere para atualizar a lista
        Percorre_rivais_rivais_circular(t->dir, ptlista); //chama a mesma função para arvore a direita
    }
}

//responsável por chamar para cada amigo e rival do usuario t, uma função recursiva
void Percorre_amigos_rivais_circular(Tamigo_inimigo *t, Tranking_circulo **ptlista)
{
    if(t!=NULL) //apenas executa se o ponteiro para usuário não for NULL
    {
        Percorre_amigos_rivais_circular(t->esq, ptlista); //chama a mesma função para arvore a esquerda
        Percorre_amigos_amigos_circular(t->info->ptamigos, ptlista); //chama a função recursiva para os amigos
        Percorre_rivais_rivais_circular(t->info->ptinimigos, ptlista); //chama a função recursiva para os rivais
        Percorre_amigos_rivais_circular(t->dir, ptlista); //chama a mesma função para arvore a direita
    }
}

//função que imprime todos os usuarios da lista popular por ordem de popularidade
void Imprime_todos_ranking_circulo (Tranking_circulo *ptlista, FILE *saida)
{
    while(ptlista!=NULL)
    {
        fprintf(saida," %s", ptlista->nome);
        ptlista=ptlista->prox;
    }
}

//função que imprime um número X (definido pelo parametro top) de usuarios da lista popular por ordem de popularidade
void Imprime_ranking_circulo (Tranking_circulo *ptlista, int top, FILE *saida)
{
    while((ptlista!=NULL) && (top!=0))
    {
        fprintf(saida," %s", ptlista->nome);
        ptlista=ptlista->prox;
        top--;
    }
}

