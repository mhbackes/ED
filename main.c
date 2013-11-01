#include <stdio.h>
#include <stdlib.h>
#include "header.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	Tusuario *ptusuario=NULL;
	input(&ptusuario);
	ptusuario=Consulta_Usuario(ptusuario,"amendoim");
	if(!strcmp("amendoim",ptusuario->nome))
		printf("%s\n",ptusuario->nome);
	Desenha(ptusuario,0,0);
	ptusuario=Consulta_Usuario(ptusuario,"luiza");
	if(!strcmp("amendoim",ptusuario->nome))
		printf("%s\n",ptusuario->nome);
	Desenha(ptusuario,0,0);
	ptusuario=Consulta_Usuario(ptusuario,"goku");
	if(!strcmp("amendoim",ptusuario->nome))
		printf("%s\n",ptusuario->nome);
	else
		printf("Usuario nao encontrado\n");
	Desenha(ptusuario,0,0);
	return 0;
}
