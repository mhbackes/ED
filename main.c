#include <stdio.h>
#include <stdlib.h>
#include "header.h"

int main(int argc, char *argv[])
{
	Tusuario *ptusuario=NULL, *amigo;
	FILE *entrada, *saida;
    Tamigo_inimigo* ret_ins_amigo = NULL;
    
    char opcao, nome1[100], nome2[100], texto[1000], nome_arq[100]={"texto.txt"};
    int ord, top, tipo;
    
    /*printf("Digite o nome do arquivo de entrada:\n");
    gets(nome_arq);*/
    
    if(entrada=fopen(nome_arq,"r"))
    {
    	printf("Arquivo aberto com sucesso\n");
    	saida=fopen("saida.txt","w");
        while(!feof(entrada))
        {
            if(opcao=getc(entrada))
            {
                switch(opcao)
                {
                case 'i':
                    printf("Insere Usuario\n");
                    fscanf(entrada, "%s", nome1);
                    printf("nome1=%s\n\n", nome1);
                    ptusuario=Insere_Usuario(ptusuario,nome1, saida);
                    break;
                case 'e':
                    printf("Exibe\n");
                    fscanf(entrada, "%d%d", &ord, &top);
                    printf("ord=%d, top=%d\n\n",ord, top);
                    fprintf(saida,"e");
                    if(ptusuario!=NULL){
	                    if(top!=0)
	                    {
	                        if(ord==1)
	                            Exibe_Usuarios_Cresc(ptusuario,&top,saida);
	                        else
	                            Exibe_Usuarios_Decresc(ptusuario,&top,saida);
	                        fprintf(saida,"\n");
	                    }
	                    else
	                    {
	                        if(ord==1)
	                            Exibe_Todos_Usuarios_Cresc(ptusuario,saida);
	                        else
	                            Exibe_Todos_Usuarios_Decresc(ptusuario,saida);
	                        fprintf(saida,"\n");
	                    }
	                }
	                else
	                	fprintf(saida," ERRO nenhum usuario cadastrado\n");
                    break;
                case 'a':
                    printf("\nInsere Amigo\n");
                    fscanf(entrada, "%s%s%d", nome1, nome2, &tipo);
                    printf("nome1=%s, nome2=%s, tipo=%d\n\n", nome1, nome2, tipo);
                    if(ptusuario=Consulta_Usuario(ptusuario,nome2))
                    {
                        if(!(strcmp(nome2,(ptusuario)->nome)))
                        {
                            amigo=ptusuario;
                            if(ptusuario=Consulta_Usuario(ptusuario,nome1))
                            {
                                if(!(strcmp(nome1,(ptusuario)->nome)))
                                {
                                    if(tipo == 1)
                                    {
                                        ptusuario->ptamigos=InsereAmigoInimigo(ptusuario->ptamigos, amigo, saida);
                                    }
                                    else
                                    {
                                        ptusuario->ptinimigos=InsereAmigoInimigo(ptusuario->ptinimigos, amigo, saida);
                                    }
                                }
                                else
                                {
                                    fprintf(saida, "a ERRO usuario nao cadastrado\n");
                                }
                            }
                        }
                        else
                        {
                            fprintf(saida, "a ERRO usuario nao cadastrado\n");
                        }
                    }
                    break;
                case 'm':
                    printf("Exibe Amigos\n");
                    fscanf(entrada, "%s%d%d", nome1, &tipo, &top);
                    printf("nome1=%s, tipo=%d, top=%d\n\n", nome1, tipo, top);
                    if(ptusuario=Consulta_Usuario(ptusuario,nome1))
                    {
                        if(!(strcmp(nome1,(ptusuario)->nome)))
                        {
                            Exibe_Amigos(ptusuario, tipo, top, saida);
                        }
                        else
                        {
                            fprintf(saida,"m ERRO usuario nao cadastrado\n", nome1);
                        }
                    }
                    break;
                case 't':
                    printf("Post\n");
                    fscanf(entrada, "%s", nome1);
                    fseek(entrada, 2, SEEK_CUR);
                    fgets(texto, 1000, entrada);
                    strtok(texto,"\"");
                    fseek(entrada, -3, SEEK_CUR);
                    fscanf(entrada, "%d", &tipo);
                    printf("nome1=%s, texto=%s, tipo=%d\n\n", nome1, texto, tipo);
                    // post;
                    break;
                case 'p':
                    printf("Exibe Painel\n");
                    fscanf(entrada, "%s%d%d", nome1, &tipo, &top);
                    printf("nome1=%s, tipo=%d, top=%d\n\n", nome1, tipo, top);
                    // exibe_painel;
                    break;
                case 'c':
                    printf("Ranking Popular Circulo\n");
                    fscanf(entrada, "%s%d%d", nome1, &tipo, &top);
                    printf("nome1=%s, tipo=%d, top=%d\n\n", nome1, tipo, top);
                    // ranking_popular_circulo;
                    break;
                case 'r':
                    printf("Ranking Popular\n");
                    fscanf(entrada, "%d%d", &tipo, &top);
                    printf("tipo=%d, top=%d\n\n", tipo, top);
                    // ranking_popular;
                }
                getc(entrada);
                fflush(saida);
            }
        }
        fclose(entrada);
        fclose(saida);
    }
    else
    {
        printf("Arquivo nao encontrado");
    }
	return 0;
}
