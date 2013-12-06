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
    novo->numamigos=0;
    novo->numinimigos=0;
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

void Cria_Ranking_amigo_inimigo (Tranking_popular **ptranking, Tusuario *ptusuario)
{
	if(ptusuario!=NULL)
	{
		Cria_Ranking_amigo_inimigo(ptranking,ptusuario->dir);
		if(((ptusuario->numamigos)+(ptusuario->numinimigos))!=0)
			*ptranking=Insere_Ranking_amigo_inimigo(*ptranking,ptusuario);
		Cria_Ranking_amigo_inimigo(ptranking,ptusuario->esq);
	}
}

Tranking_popular* Insere_Ranking_amigo_inimigo (Tranking_popular *ptranking, Tusuario *ptusuario)
{
	Tranking_popular *retorno=ptranking;
	if(ptranking==NULL)
	{
		retorno=malloc(sizeof(Tranking_popular));
		strcpy(retorno->nome,ptusuario->nome);
		retorno->num=(ptusuario->numamigos)+(ptusuario->numinimigos);
		retorno->esq=NULL;
		retorno->dir=NULL;
	}
	else if (ptranking->num>((ptusuario->numamigos)+(ptusuario->numinimigos)))
		ptranking->esq=Insere_Ranking_amigo_inimigo(ptranking->esq, ptusuario);
	else
		ptranking->dir=Insere_Ranking_amigo_inimigo(ptranking->dir, ptusuario);
	return retorno;
}

void Cria_Ranking_amigo (Tranking_popular **ptranking, Tusuario *ptusuario)
{
	if(ptusuario!=NULL)
	{
		Cria_Ranking_amigo(ptranking,ptusuario->dir);
		if(ptusuario->numamigos!=0)
			*ptranking=Insere_Ranking_amigo(*ptranking,ptusuario);
		Cria_Ranking_amigo(ptranking,ptusuario->esq);
	}
}

Tranking_popular* Insere_Ranking_amigo (Tranking_popular *ptranking, Tusuario *ptusuario)
{
	Tranking_popular *retorno=ptranking;
	if(ptranking==NULL)
	{
		retorno=malloc(sizeof(Tranking_popular));
		strcpy(retorno->nome,ptusuario->nome);
		retorno->num=ptusuario->numamigos;
		retorno->esq=NULL;
		retorno->dir=NULL;
	}
	else if (ptranking->num>ptusuario->numamigos)
		ptranking->esq=Insere_Ranking_amigo (ptranking->esq, ptusuario);
	else
		ptranking->dir=Insere_Ranking_amigo (ptranking->dir, ptusuario);
	return retorno;
}

void Cria_Ranking_inimigo (Tranking_popular **ptranking, Tusuario *ptusuario)
{
	if(ptusuario!=NULL)
	{
		Cria_Ranking_inimigo(ptranking,ptusuario->dir);
		if(ptusuario->numinimigos!=0)
			*ptranking=Insere_Ranking_inimigo(*ptranking,ptusuario);
		Cria_Ranking_inimigo(ptranking,ptusuario->esq);
	}
}

Tranking_popular* Insere_Ranking_inimigo (Tranking_popular *ptranking, Tusuario *ptusuario)
{
	Tranking_popular *retorno=ptranking;
	if(ptranking==NULL)
	{
		retorno=malloc(sizeof(Tranking_popular));
		strcpy(retorno->nome,ptusuario->nome);
		retorno->num=ptusuario->numinimigos;
		retorno->esq=NULL;
		retorno->dir=NULL;
	}
	else if (ptranking->num>ptusuario->numinimigos)
		ptranking->esq=Insere_Ranking_inimigo (ptranking->esq, ptusuario);
	else
		ptranking->dir=Insere_Ranking_inimigo (ptranking->dir, ptusuario);
	return retorno;
}

void Imprime_Todos_Ranking (Tranking_popular *ptranking, FILE *saida)
{
	if(ptranking!=NULL)
	{
		Imprime_Todos_Ranking(ptranking->dir,saida);
		fprintf(saida," %s", ptranking->nome);
		Imprime_Todos_Ranking(ptranking->esq,saida);
	}
}

void Imprime_Ranking (Tranking_popular *ptranking, int *top, FILE *saida)
{
	if(ptranking!=NULL)
    {
        Imprime_Ranking(ptranking->dir,top,saida);
        if(*top!=0)
        {
            fprintf(saida, " %s", ptranking->nome);
            *top=*top-1;
        }
        Imprime_Ranking(ptranking->esq,top,saida);
    }
}

Tranking_popular* Exclui_Ranking (Tranking_popular *ptranking)
{
	if(ptranking!=NULL)
	{
		ptranking->esq=Exclui_Ranking(ptranking->esq);
		ptranking->dir=Exclui_Ranking(ptranking->dir);
		free(ptranking);
		ptranking=NULL;
	}
	return ptranking;
}

Tamigo_inimigo* Consulta_amigo_inimigo (Tamigo_inimigo *t, char nome[])
{
	int comp;
	if(t!=NULL)
	{
		comp=strcmp(t->info->nome, nome);
		if(comp==0)
			return t;
		if(comp>0)
			return Consulta_amigo_inimigo(t->esq,nome);
		else
			return Consulta_amigo_inimigo(t->dir,nome);
	}
	else
		return t;
}

Tamigo_inimigo* rotacao_direita(Tamigo_inimigo *pt){
   Tamigo_inimigo* ptu;
   ptu = pt->esq; 
   pt->esq = ptu->dir; 
   ptu->dir = pt; 
   pt->FB = 0;
   pt = ptu; 
   return pt;
}

Tamigo_inimigo* rotacao_esquerda(Tamigo_inimigo *pt){
   Tamigo_inimigo* ptu;
   ptu = pt->dir; 
   pt->dir = ptu->esq; 
   ptu->esq = pt; 
   pt->FB = 0;
   pt = ptu; 
   return pt;
} 

Tamigo_inimigo* rotacao_dupla_direita (Tamigo_inimigo* pt){
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

Tamigo_inimigo* rotacao_dupla_esquerda (Tamigo_inimigo* pt){
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
	   		    switch (a->FB) {
	        	  case -1:  a->FB = 0; *ok = 0; break;
				  case  0:  a->FB = 1;  break;
				  case  1:  a=Caso1(a,ok); break;
	            }
	         }
	     }
		 else
	     {
	  		    a->dir = Insere_amigo(a->dir,x,ok, saida);
	            if (*ok)
	            { 
	              switch (a->FB) {
	                case  1:  a->FB = 0; *ok = 0; break;
	                case  0:  a->FB = -1; break;
				    case -1:  a = Caso2(a,ok); break;
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
	   		    switch (a->FB) {
	        	  case -1:  a->FB = 0; *ok = 0; break;
				  case  0:  a->FB = 1;  break;
				  case  1:  a=Caso1(a,ok); break;
	            }
	         }
	     }
		 else
	     {
	  		    a->dir = Insere_inimigo(a->dir,x,ok, saida);
	            if (*ok)
	            { 
	              switch (a->FB) {
	                case  1:  a->FB = 0; *ok = 0; break;
	                case  0:  a->FB = -1; break;
				    case -1:  a = Caso2(a,ok); break;
	             }
	            }
	 	}
 	}
     return a;
}

Tfeed* Pushfeed(Tfeed* topo, char post[], char nome[])
{
    Tfeed *novo; //novo elemento
    novo = (Tfeed*) malloc(sizeof(Tfeed));//aloca um novo nodo
    novo->prox = NULL; //inicialisa o ponteiro como NULL
    strcpy(novo->texto, post);//insere a informação no novo nodo
    strcpy(novo->nome, nome);
    novo->prox = topo;//encaeia o elemento
    topo = novo;

    return topo;//retorna o topo da pilha para a função que a chamou
}

void Insere_Post_Amigo_Inimigo(Tamigo_inimigo *t, char post[], char nome[])
{
    if(t!=NULL)
    {
        Insere_Post_Amigo_Inimigo(t->esq, post, nome);
        t->info->ptfeed = Pushfeed(t->info->ptfeed, post,  nome);
        Insere_Post_Amigo_Inimigo(t->dir, post, nome);
    }
}

void Insere_Post_Todos(Tusuario* t, char post[], char nome[])
{
    if(t!=NULL)
    {
        Insere_Post_Todos(t->esq, post, nome);
        t->ptfeed = Pushfeed(t->ptfeed, post, nome);
        Insere_Post_Todos(t->dir, post, nome);
    }
}

void Imprime_feed_todos_amigos(Tfeed* topo, Tusuario *t, int *achou, FILE* saida)
{
	if(topo!=NULL)
	{
	    if((!strcmp(topo->nome,t->nome))||(Consulta_amigo_inimigo(t->ptamigos, topo->nome)!=NULL))
	    {
	        fprintf(saida,"\n\"%s\" %s", topo->texto, topo->nome);
	        *achou=1;
	    }
	    Imprime_feed_todos_amigos(topo->prox, t, achou, saida);
	}
}

void Imprime_feed_todos_inimigos(Tfeed* topo, Tusuario *t, int *achou, FILE* saida)
{
	if(topo!=NULL)
	{
	    if((!strcmp(topo->nome,t->nome))||(Consulta_amigo_inimigo(t->ptinimigos, topo->nome)!=NULL))
	    {
	        fprintf(saida,"\n\"%s\" %s", topo->texto, topo->nome);
	        *achou=1;
	    }
	    Imprime_feed_todos_inimigos (topo->prox, t, achou, saida);
	}
}

void Imprime_feed_todos_amigos_inimigos(Tfeed* topo, Tusuario *t, int *achou, FILE* saida)
{
	if(topo!=NULL)
	{
	    if(!strcmp(topo->nome,t->nome) ||
		(Consulta_amigo_inimigo(t->ptamigos, topo->nome)!=NULL) ||
		(Consulta_amigo_inimigo(t->ptinimigos, topo->nome)!=NULL))
	    {
	        fprintf(saida,"\n\"%s\" %s", topo->texto, topo->nome);
	        *achou=1;
	    }
	    Imprime_feed_todos_amigos_inimigos(topo->prox, t, achou, saida);
	}
}

void Imprime_feed_amigos(Tfeed* topo, Tusuario *t, int top, int *achou, FILE* saida)
{
	if((topo!=NULL)&&(top!=0))
	{
	    if((!strcmp(topo->nome,t->nome))||(Consulta_amigo_inimigo(t->ptamigos, topo->nome)!=NULL))
	    {
	        fprintf(saida,"\n\"%s\" %s", topo->texto, topo->nome);
	        *achou=1;
	    }
	    Imprime_feed_amigos(topo->prox, t, top-1, achou, saida);
	}
}

void Imprime_feed_inimigos(Tfeed* topo, Tusuario *t, int top, int *achou, FILE* saida)
{
	if((topo!=NULL)&&(top!=0))
	{
	    if((!strcmp(topo->nome,t->nome))||(Consulta_amigo_inimigo(t->ptinimigos, topo->nome)!=NULL))
	    {
	        fprintf(saida,"\n\"%s\" %s", topo->texto, topo->nome);
	        *achou=1;
	    }
	    Imprime_feed_amigos(topo->prox, t, top-1, achou, saida);
	}
}

void Imprime_feed_amigos_inimigos(Tfeed* topo, Tusuario *t, int top, int *achou, FILE* saida)
{
	if((topo!=NULL)&&(top!=0))
	{
	    if(!strcmp(topo->nome,t->nome) ||
		(Consulta_amigo_inimigo(t->ptamigos, topo->nome)!=NULL) ||
		(Consulta_amigo_inimigo(t->ptinimigos, topo->nome)!=NULL))
	    {
	        fprintf(saida,"\n\"%s\" %s", topo->texto, topo->nome);
	        *achou=1;
	    }
	    Imprime_feed_amigos_inimigos(topo->prox, t, top-1, achou, saida);
	}
}
