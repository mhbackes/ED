#include <stdio.h>
#include <stdlib.h>
#include "abp.h"

int main(int argc, char *argv[])
{
    Tusuario *ptusuario=NULL, *amigoinimigo;
    FILE *entrada, *saida;
    Tamigo_inimigo* ret_ins_amigo = NULL;
    Tranking_circulo* ptlista = NULL;
    Tranking_popular* ptranking = NULL;
    int ok=0;
    char opcao, nome1[100], nome2[100], texto[1000], nome_arq[100]= {"texto.txt"};
    int ord, top, tipo, achou=0;

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
                    if(ptusuario!=NULL)
                    {
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
                            amigoinimigo=ptusuario;
                            if(ptusuario=Consulta_Usuario(ptusuario,nome1))
                            {
                                if(!(strcmp(nome1,(ptusuario)->nome)))
                                {
                                    if(tipo == 1)
                                    {
                                        ptusuario->ptamigos=Insere_amigo(ptusuario->ptamigos, amigoinimigo, &ok, saida);

                                    }
                                    else
                                    {
                                        ptusuario->ptinimigos=Insere_inimigo(ptusuario->ptinimigos, amigoinimigo, &ok, saida);
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
                    if(ptusuario=Consulta_Usuario(ptusuario,nome1))
                    {
                        if(!(strcmp(nome1,(ptusuario)->nome)))
                        {
                            if(tipo == 0)
                            {
                                Insere_Post_Todos(ptusuario, texto, nome1);
                            }
                            else if(tipo == 1)
                            {
                                Insere_Post_Amigo_Inimigo(ptusuario->ptamigos, texto, nome1);
                                ptusuario->ptfeed=Pushfeed(ptusuario->ptfeed, texto, nome1);
                            }
                            else
                            {
                                Insere_Post_Amigo_Inimigo(ptusuario->ptinimigos, texto, nome1);
                                ptusuario->ptfeed=Pushfeed(ptusuario->ptfeed, texto, nome1);
                            }
                            fprintf(saida, "t post inserido com sucesso\n");
                        }
                        else
                        {
                            fprintf(saida, "t ERRO usuario nao cadastrado\n");
                        }
                    }
                    break;
                case 'p':
                    printf("Exibe Painel\n");
                    fscanf(entrada, "%s%d%d", nome1, &tipo, &top);
                    printf("nome1=%s, tipo=%d, top=%d\n\n", nome1, tipo, top);
                    if(ptusuario=Consulta_Usuario(ptusuario,nome1))
                    {
                        if(!(strcmp(nome1,(ptusuario)->nome)))
                        {
                            if(ptusuario->ptfeed==NULL)
                                fprintf(saida, "p ERRO feed vazio\n");
                            else
                            {
                                fprintf(saida,"p");
                                if(tipo==0)
                                {
                                    if(top==0)
                                        Imprime_feed_todos_amigos_inimigos(ptusuario->ptfeed, ptusuario, &achou, saida);
                                    else
                                        Imprime_feed_amigos_inimigos(ptusuario->ptfeed, ptusuario, top, &achou, saida);
                                }
                                else if(tipo==1)
                                {
                                    if(top==0)
                                        Imprime_feed_todos_amigos(ptusuario->ptfeed, ptusuario, &achou, saida);
                                    else
                                        Imprime_feed_amigos(ptusuario->ptfeed, ptusuario, top, &achou, saida);
                                }
                                else
                                {
                                    if(top==0)
                                        Imprime_feed_todos_inimigos(ptusuario->ptfeed, ptusuario, &achou, saida);
                                    else
                                        Imprime_feed_inimigos(ptusuario->ptfeed, ptusuario, top, &achou, saida);;
                                }
                                if(achou==0)
                                {
                                    fprintf(saida, " ERRO feed vazio\n");
                                }
                                else
                                {
                                    fprintf(saida, "\n");
                                    achou=0;
                                }
                            }
                        }
                        else
                        {
                            fprintf(saida, "p ERRO usuario nao cadastrado\n");
                        }
                    }
                    break;
                case 'c':
                    printf("Ranking Popular Circulo\n");
                    fscanf(entrada, "%s%d%d", nome1, &tipo, &top);
                    printf("nome1=%s, tipo=%d, top=%d\n\n", nome1, tipo, top);
                    if(ptusuario=Consulta_Usuario(ptusuario,nome1))
                    {
                        if(!(strcmp(nome1,(ptusuario)->nome)))
                        {
                            fprintf(saida,"c");
                            if(tipo == 1)
                            {
                                if(ptusuario->ptamigos != NULL)
                                {
                                    Percorre_amigos_amigos_circular(ptusuario->ptamigos, &ptlista);
                                    Percorre_amigos_circular(ptusuario, &ptlista);
                                }
                                else
                                {
                                    fprintf(saida, " ERRO lista vazia");
                                }
                            }
                            else
                            {
                                if(tipo == 2)
                                {
                                    if(ptusuario->ptinimigos != NULL)
                                    {
                                        Percorre_rivais_rivais_circular(ptusuario->ptinimigos, &ptlista);
                                        Percorre_rivais_circular(ptusuario, &ptlista);
                                    }
                                    else
                                    {
                                        fprintf(saida, " ERRO lista vazia");
                                    }

                                }
                                else
                                {
                                    if((ptusuario->ptinimigos != NULL) || (ptusuario->ptamigos != NULL))
                                    {
                                        Percorre_rivais_rivais_circular(ptusuario->ptinimigos, &ptlista);
                                        Percorre_amigos_amigos_circular(ptusuario->ptamigos, &ptlista);
                                        Percorre_rivais_circular(ptusuario, &ptlista);
                                        Percorre_amigos_circular(ptusuario, &ptlista);
                                    }
                                    else
                                    {
                                        fprintf(saida, " ERRO lista vazia");
                                    }
                                }
                            }
                            if(top == 0)
                            {
                                Imprime_todos_ranking_circulo(ptlista, saida);
                                fprintf(saida,"\n");
                            }
                            else
                            {
                                Imprime_ranking_circulo(ptlista, top, saida);
                                fprintf(saida,"\n");
                            }
                        }
                        else
                        {
                            fprintf(saida, "p ERRO usuario nao cadastrado\n");
                        }
                    }
                    ptlista = Exclui_ranking_circulo(ptlista);
                    break;
                case 'r':
                    printf("Ranking Popular\n");
                    fscanf(entrada, "%d%d", &tipo, &top);
                    printf("tipo=%d, top=%d\n\n", tipo, top);
                    if(ptusuario==NULL)
                        fprintf(saida,"r ERRO nenhum usuario cadastrado");
                    else
                    {
                        if(tipo==0)
                            Cria_Ranking_amigo_inimigo(&ptranking,ptusuario);
                        else if(tipo==1)
                            Cria_Ranking_amigo(&ptranking,ptusuario);
                        else
                            Cria_Ranking_inimigo(&ptranking,ptusuario);
                        if(ptranking!=NULL)
                        {
                            fprintf(saida,"r");
                            if(top==0)
                                Imprime_Todos_Ranking(ptranking,saida);
                            else
                                Imprime_Ranking(ptranking,&top,saida);
                            fprintf(saida,"\n");
                            ptranking=Exclui_Ranking(ptranking);
                        }
                        else
                            fprintf(saida,"r ERRO nenhum usuario popular\n");
                    }
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
