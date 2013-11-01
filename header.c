#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"
void input(Tusuario **ptusuario)
{
	FILE *arq;
	char opcao, nome1[100], nome2[100], texto[1000];
	int ord, top, tipo, a;
	if(arq=fopen("texto.txt","r")){
		while(!feof(arq)){
			if(opcao=getc(arq)){
				switch(opcao)
				{
					case 'i': printf("Insere Usuario\n");
							fscanf(arq, "%s", nome1);
							printf("nome1=%s\n\n", nome1);
							*ptusuario=Insere_Usuario(*ptusuario,nome1);
							break;
					case 'e': printf("Exibe\n");
							fscanf(arq, "%d%d", &ord, &top);
							printf("ord=%d, top=%d\n\n",ord, top);
							if(top!=0){
								printf("Impressao de %d usuarios:\n", top);
								if(ord==1)
									Exibe_Usuarios_Cresc(*ptusuario,&top);
								else
									Exibe_Usuarios_Decresc(*ptusuario,&top);
								printf("\n");
							}
							else{
								printf("Impressao de todos usuarios:\n", top);
								if(ord==1)
									Exibe_Todos_Usuarios_Cresc(*ptusuario);
								else
									Exibe_Todos_Usuarios_Decresc(*ptusuario);
								printf("\n");
							}
							break;
					case 'a': printf("Insere Amigo\n");
							fscanf(arq, "%s%s%d", nome1, nome2, &tipo);
							printf("nome1=%s, nome2=%s, tipo=%d\n\n", nome1, nome2, tipo);
							// insere_amigo;
							break;
					case 'm': printf("Exibe Amigos\n");
							fscanf(arq, "%s%d%d", nome1, &tipo, &top);
							printf("nome1=%s, tipo=%d, top=%d\n\n", nome1, tipo, top);
							// exibe_amigos;
							break;
					case 't': printf("Post\n");
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
					case 'p': printf("Exibe Painel\n");
							fscanf(arq, "%s%d%d", nome1, &tipo, &top);
							printf("nome1=%s, tipo=%d, top=%d\n\n", nome1, tipo, top);
							// exibe_painel;
							break;
					case 'c': printf("Ranking Popular Circulo\n");
							fscanf(arq, "%s%d%d", nome1, &tipo, &top);
							printf("nome1=%s, tipo=%d, top=%d\n\n", nome1, tipo, top);
							// ranking_popular_circulo;
							break;
					case 'r': printf("Ranking Popular\n");
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
  	if (t == NULL){
		retorno=Novo(nome,NULL,NULL);
		printf("Usuario inserido com sucesso\n");
	}
	else if (!strcmp(nome,t->nome)){
		printf("Usuario ja cadastrado");
		retorno=t;
	}
  	else if (strcmp(nome,t->nome)<0){ 
		if (t->esq == NULL){
			retorno=Novo(nome,NULL,t);
			printf("Usuario inserido com sucesso\n");
		}
		else if (!strcmp(nome,t->esq->nome)){
				printf("Usuario ja cadastrado\n");
				retorno=t;
		}
		else{
			if (strcmp(nome,t->esq->nome)<0){ 
		      	t->esq->esq = Splay(t->esq->esq, nome);
		    	t = RotDir(t);
		    }
		    else { 
		    t->esq->dir = Splay(t->esq->dir, nome);
		    t->esq = RotEsq(t->esq);
		    }
		    retorno=RotDir(t);
		}
	}
	else
	{ 
	    if (t->dir == NULL){ 
			retorno=Novo(nome,t,NULL);
			printf("Usuario inserido com sucesso\n");
		}
		else if (!strcmp(nome,t->dir->nome)){
				printf("Usuario ja cadastrado\n");
				retorno=t;
		}
		else{
			if (strcmp(nome,t->dir->nome)>0){
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
	if(t!=NULL){
		Exibe_Usuarios_Cresc(t->esq,top);
		if(*top!=0){
			printf("%s\n", t->nome);
			*top=*top-1;
		}
		Exibe_Usuarios_Cresc(t->dir,top);
	}
}

void Exibe_Usuarios_Decresc(Tusuario *t, int *top)
{
	if(t!=NULL){
		Exibe_Usuarios_Decresc(t->dir,top);
		if(*top!=0){
			printf("%s\n", t->nome);
			*top=*top-1;
		}
		Exibe_Usuarios_Decresc(t->esq,top);
	}
}

void Exibe_Todos_Usuarios_Cresc(Tusuario *t)
{
	if(t!=NULL){
		Exibe_Todos_Usuarios_Cresc(t->esq);
		printf("%s\n", t->nome);
		Exibe_Todos_Usuarios_Cresc(t->dir);
	}
}

void Exibe_Todos_Usuarios_Decresc(Tusuario *t)
{
	if(t!=NULL){
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
 	else if (strcmp(nome, t->nome)<0){
    	if (t->esq == NULL)
			retorno=t;
	  	else if (strcmp(nome, t->esq->nome)<0){
       		t->esq->esq = Consulta_Usuario(t->esq->esq, nome);
	     	t = RotDir(t);
	     	if (t->esq == NULL)
				retorno=t;
	     	else
				retorno=RotDir(t);
    	}
		else if (strcmp(t->esq->nome,nome)<0){
        	t->esq->dir = Consulta_Usuario(t->esq->dir, nome);
	        if (t->esq->dir != NULL)
			t->esq = RotEsq(t->esq);
	        retorno=RotDir(t);
        }
		else 
		retorno=RotDir(t);
 	} 
	else if(strcmp(t->nome, nome)<0) {
	    if (t->dir == NULL) 
			retorno=t;
	    else if (strcmp(t->dir->nome,nome)<0){
	        t->dir->dir = Consulta_Usuario(t->dir->dir, nome);
	        t = RotEsq(t);
	        if (t->dir == NULL) 
				retorno=t;
	        else
				retorno=RotEsq(t);
        }
		else if (strcmp(nome,t->dir->nome)<0){
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
};
