//Claudio Rodrigo Gisch   Nº228366
//Marcos Henrique Backes  Nº228483

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

int main()
{
    //incialização de dados e variaveis
    Tusuario *ptusuario=NULL, *amigoinimigo;
    FILE *entrada, *saida;
    Tamigo_inimigo* ret_ins_amigo = NULL;
    Tranking_circulo* ptlista = NULL;
    Tranking_popular* ptranking = NULL;
    int ok=0;
    char opcao, nome1[100], nome2[100], texto[81], nome_arq[100];
    int ord, top, tipo, achou=0;

    printf("Digite o nome do arquivo de entrada:\n");
    gets(nome_arq);

    //abertura do arquvio
    if(entrada=fopen(nome_arq,"r"))
    {
        printf("Arquivo aberto com sucesso\n");
        saida=fopen("saida.txt","w");
        while(!feof(entrada))
        {
            if(opcao=getc(entrada))
            {
                //switch case para selecionar a operação a ser feita
                switch(opcao)
                {

                //i = inserção de novo usuario
                case 'i':
                    printf("Insere Usuario\n");
                    fscanf(entrada, "%s", nome1); //busca dos dados no arquivo texto
                    printf("nome1=%s\n\n", nome1);
                    ptusuario=Insere_Usuario(ptusuario,nome1, saida);
                    break;

                //e =  impressão dos usuarios
                case 'e':
                    printf("Exibe\n");
                    fscanf(entrada, "%d%d", &ord, &top); //busca dos dados no arquivo texto
                    printf("ord=%d, top=%d\n\n",ord, top);
                    fprintf(saida,"e");
                    if(ptusuario!=NULL)
                    {
                        if(top!=0) //imprime um número X (definido por top) de usuarios
                        {
                            if(ord==1) //ordem crescente
                                Exibe_Usuarios_Cresc(ptusuario,&top,saida);
                            else
                                Exibe_Usuarios_Decresc(ptusuario,&top,saida);
                            fprintf(saida,"\n");
                        }
                        else  // imprime todos os usuarios
                        {
                            if(ord==1) //ordem crescente
                                Exibe_Todos_Usuarios_Cresc(ptusuario,saida);
                            else //ordem decrescente
                                Exibe_Todos_Usuarios_Decresc(ptusuario,saida);
                            fprintf(saida,"\n");
                        }
                    }
                    else
                        fprintf(saida," ERRO nenhum usuario cadastrado\n"); //imprime mensagem de erro no arquivo texto
                    break;

                //a = insere amigo ou rival na lista de amigos ou rivais de um usuario
                case 'a':
                    printf("\nInsere Amigo\n");
                    fscanf(entrada, "%s%s%d", nome1, nome2, &tipo); //busca dos dados no arquivo texto
                    printf("nome1=%s, nome2=%s, tipo=%d\n\n", nome1, nome2, tipo);
                    if(ptusuario=Consulta_Usuario(ptusuario,nome2))
                    {
                        if(!(strcmp(nome2,(ptusuario)->nome))) //verifica se nome2 está na lista de usuarios
                        {
                            amigoinimigo=ptusuario; //salva ponteiro para usuario nome2
                            if(ptusuario=Consulta_Usuario(ptusuario,nome1))
                            {
                                if(!(strcmp(nome1,(ptusuario)->nome))) //verifica se nome1 está na lista de usuarios
                                {
                                    if(tipo == 1) //insere na arvore de amigos
                                    {
                                        ptusuario->ptamigos=Insere_amigo(ptusuario->ptamigos, amigoinimigo, &ok, saida);

                                    }
                                    else //insere na arvore de rivais
                                    {
                                        ptusuario->ptinimigos=Insere_inimigo(ptusuario->ptinimigos, amigoinimigo, &ok, saida);
                                    }
                                }
                                else
                                {
                                    fprintf(saida, "a ERRO usuario nao cadastrado\n");  //imprime mensagem de erro no arquivo texto
                                }
                            }
                        }
                        else
                        {
                            fprintf(saida, "a ERRO usuario nao cadastrado\n"); //imprime mensagem de erro no arquivo texto
                        }
                    }
                    break;

                //m = exibe lista de amigos e/ou rivais
                case 'm':
                    printf("Exibe Amigos\n");
                    fscanf(entrada, "%s%d%d", nome1, &tipo, &top); //busca dos dados no arquivo texto
                    printf("nome1=%s, tipo=%d, top=%d\n\n", nome1, tipo, top);
                    if(ptusuario=Consulta_Usuario(ptusuario,nome1))
                    {
                        if(!(strcmp(nome1,(ptusuario)->nome))) //verifica se nome1 está na lista de usuarios
                        {
                            Exibe_Amigos(ptusuario, tipo, top, saida);
                        }
                        else
                        {
                            fprintf(saida,"m ERRO usuario nao cadastrado\n"); //imprime mensagem de erro no arquivo texto
                        }
                    }
                    break;

                //t = insere um post na pilha de posts
                case 't':
                    printf("Post\n");
                    //busca dos dados no arquivo texto
                    fscanf(entrada, "%s", nome1);
                    fseek(entrada, 2, SEEK_CUR);
                    fgets(texto, 81, entrada);
                    strtok(texto,"\"");
                    fseek(entrada, -3, SEEK_CUR);
                    fscanf(entrada, "%d", &tipo);
                    printf("nome1=%s, texto=%s, tipo=%d\n\n", nome1, texto, tipo);
                    if(ptusuario=Consulta_Usuario(ptusuario,nome1))
                    {
                        if(!(strcmp(nome1,(ptusuario)->nome))) //verifica se nome1 está na lista de usuarios
                        {
                            if(tipo == 0) //insere o post na lista de amigos ,rivais e do próprio usuário
                            {
                                Insere_Post_Todos(ptusuario, texto, nome1);
                            }
                            else if(tipo == 1) //insere o post na lista de amigos e do próprio usuário
                            {
                                Insere_Post_Amigo_Inimigo(ptusuario->ptamigos, texto, nome1);
                                ptusuario->ptfeed=Pushfeed(ptusuario->ptfeed, texto, nome1);
                            }
                            else //insere o post na lista de rivais e do próprio usuário
                            {
                                Insere_Post_Amigo_Inimigo(ptusuario->ptinimigos, texto, nome1);
                                ptusuario->ptfeed=Pushfeed(ptusuario->ptfeed, texto, nome1);
                            }
                            fprintf(saida, "t post inserido com sucesso\n");  //imprime mensagem no arquivo texto de que a operação ocorreu com sucesso
                        }
                        else
                        {
                            fprintf(saida, "t ERRO usuario nao cadastrado\n"); //imprime mensagem de erro no arquivo texto
                        }
                    }
                    break;

                //p = imprime os posts de um dado usuario
                case 'p':
                    printf("Exibe Painel\n");
                    fscanf(entrada, "%s%d%d", nome1, &tipo, &top); //busca dos dados no arquivo texto
                    printf("nome1=%s, tipo=%d, top=%d\n\n", nome1, tipo, top);
                    if(ptusuario=Consulta_Usuario(ptusuario,nome1))
                    {
                        if(!(strcmp(nome1,(ptusuario)->nome))) //verifica se nome1 está na lista de usuarios
                        {
                            if(ptusuario->ptfeed==NULL) //se a lista de feeds do usuario estiver vazia
                                fprintf(saida, "p ERRO feed vazio\n"); //imprime mensagem de erro no arquivo texto
                            else
                            {
                                fprintf(saida,"p");
                                if(tipo==0) //imprime post dos amigos e rivais
                                {
                                    if(top==0) //imprime todos os post dos amigos e rivais
                                        Imprime_feed_todos_amigos_inimigos(ptusuario->ptfeed, ptusuario, &achou, saida);
                                    else //imprime um número X (definido pela variavel top) de post dos amigos e rivais
                                        Imprime_feed_amigos_inimigos(ptusuario->ptfeed, ptusuario, top, &achou, saida);
                                }
                                else if(tipo==1) //imprime post dos amigos
                                {
                                    if(top==0) //imprime todos os post dos amigos
                                        Imprime_feed_todos_amigos(ptusuario->ptfeed, ptusuario, &achou, saida);
                                    else //imprime um número X (definido pela variavel top) de post dos amigos
                                        Imprime_feed_amigos(ptusuario->ptfeed, ptusuario, top, &achou, saida);
                                }
                                else //imprime post dos rivais
                                {
                                    if(top==0) //imprime todos os post dos  rivais
                                        Imprime_feed_todos_inimigos(ptusuario->ptfeed, ptusuario, &achou, saida);
                                    else //imprime um número X (definido pela variavel top) de post dos rivais
                                        Imprime_feed_inimigos(ptusuario->ptfeed, ptusuario, top, &achou, saida);;
                                }
                                if(achou==0) //flag em caso de não achar feed nos amigos e/ou rivais
                                {
                                    fprintf(saida, " ERRO feed vazio\n"); //imprime mensagem de erro no arquivo texto
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
                            fprintf(saida, "p ERRO usuario nao cadastrado\n"); //imprime mensagem de erro no arquivo texto
                        }
                    }
                    break;

                //c = imprime os usuarios mais populares apartir de um usuario e suas relações com outros usuarios
                case 'c':
                    printf("Ranking Popular Circulo\n");
                    fscanf(entrada, "%s%d%d", nome1, &tipo, &top); //busca dos dados no arquivo texto
                    printf("nome1=%s, tipo=%d, top=%d\n\n", nome1, tipo, top);
                    if(ptusuario=Consulta_Usuario(ptusuario,nome1))
                    {
                        if(!(strcmp(nome1,(ptusuario)->nome))) //verifica se nome1 está na lista de usuarios
                        {
                            fprintf(saida,"c");
                            if(tipo == 1) //leva em conta apenas as relações de amizade do usuario
                            {
                                if(ptusuario->ptamigos != NULL)
                                {
                                    Percorre_amigos_amigos_circular(ptusuario->ptamigos, &ptlista);
                                    Percorre_amigos_circular(ptusuario->ptamigos, &ptlista);
                                }
                                else
                                {
                                    fprintf(saida, " ERRO lista vazia"); //imprime mensagem de erro no arquivo texto
                                }
                            }
                            else
                            {
                                if(tipo == 2) //leva em conta apenas as relações de rivalidade do usuario
                                {
                                    if(ptusuario->ptinimigos != NULL)
                                    {
                                        Percorre_rivais_rivais_circular(ptusuario->ptinimigos, &ptlista);
                                        Percorre_rivais_circular(ptusuario->ptinimigos, &ptlista);
                                    }
                                    else
                                    {
                                        fprintf(saida, " ERRO lista vazia"); //imprime mensagem de erro no arquivo texto
                                    }

                                }
                                else //leva em conta todas relações do usuario
                                {
                                    if((ptusuario->ptinimigos != NULL) || (ptusuario->ptamigos != NULL))
                                    {
                                        Percorre_rivais_rivais_circular(ptusuario->ptinimigos, &ptlista);
                                        Percorre_amigos_amigos_circular(ptusuario->ptamigos, &ptlista);
                                        Percorre_amigos_rivais_circular(ptusuario->ptamigos, &ptlista);
                                        Percorre_amigos_rivais_circular(ptusuario->ptinimigos, &ptlista);

                                    }
                                    else
                                    {
                                        fprintf(saida, " ERRO lista vazia"); //imprime mensagem de erro no arquivo texto
                                    }
                                }
                            }
                            if(top == 0) //imprime todos os usuarios por ordem de popularidade
                            {
                                Imprime_todos_ranking_circulo(ptlista, saida);
                                fprintf(saida,"\n");
                            }
                            else //imprime um número X (definido pela variavel top) de usuarios por ordem de popularidade
                            {
                                Imprime_ranking_circulo(ptlista, top, saida);
                                fprintf(saida,"\n");
                            }
                        }
                        else
                        {
                            fprintf(saida, "p ERRO usuario nao cadastrado\n"); //imprime mensagem de erro no arquivo texto
                        }
                    }
                    ptlista = Exclui_ranking_circulo(ptlista); //desaloca o espaço alocado por essa operação
                    break;

                //r = imprime os usuarios mais populares de toda a rede like.unlike.net
                case 'r':
                    printf("Ranking Popular\n");
                    fscanf(entrada, "%d%d", &tipo, &top); //busca dos dados no arquivo texto
                    printf("tipo=%d, top=%d\n\n", tipo, top);
                    if(ptusuario==NULL)
                        fprintf(saida,"r ERRO nenhum usuario cadastrado"); //imprime mensagem de erro no arquivo texto
                    else
                    {
                        if(tipo==0) //cria ranking dos usuarios que mais aparecem na lista de amigos e rivais
                            Cria_Ranking_amigo_inimigo(&ptranking,ptusuario);
                        else if(tipo==1) //cria ranking dos usuarios que mais aparecem na lista de amigos
                            Cria_Ranking_amigo(&ptranking,ptusuario);
                        else //cria ranking dos usuarios que mais aparecem na lista de rivais
                            Cria_Ranking_inimigo(&ptranking,ptusuario);
                        if(ptranking!=NULL)
                        {
                            fprintf(saida,"r");
                            if(top==0) //imprime todos usuarios do ranking
                                Imprime_Todos_Ranking(ptranking,saida);
                            else // imprime um número X (definido pela variavel top) de usuarios do ranking
                                Imprime_Ranking(ptranking,&top,saida);
                            fprintf(saida,"\n");
                            ptranking=Exclui_Ranking(ptranking); //desaloca o espaço alocado por essa operação
                        }
                        else
                            fprintf(saida,"r ERRO nenhum usuario popular\n"); //imprime mensagem de erro no arquivo texto
                    }
                }
                getc(entrada); //pega próxima operação
                fflush(saida); //salva modificaçoes do arquivo de saida
            }
        }
        fclose(entrada); //fecha o arquivo texto
        fclose(saida); //fecha o arquivo texto
    }
    else
    {
        printf("Arquivo nao encontrado"); //imprime mensagem de erro
    }
    return 0;
}
