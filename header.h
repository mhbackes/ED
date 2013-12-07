typedef struct feed Tfeed;
typedef struct usuario Tusuario;
typedef struct amigo_inimigo Tamigo_inimigo;
typedef struct ranking_circulo Tranking_circulo;
typedef struct ranking_popular Tranking_popular;

struct feed{
	char texto[1000]; //campo para armazenar o post
	char nome[100]; //nome do usuario que postou
	Tfeed *prox; //elo com o proximo post da pilha
};

struct usuario{
	char nome[100]; //nome do usuario
	Tfeed *ptfeed; //ponteiro para pilha de post
	int	numamigos; //contador do número de amigos
	int numinimigos; //contador do número de rivais
	Tamigo_inimigo *ptamigos; //ponteiro para a AVL de amigos
	Tamigo_inimigo *ptinimigos; //ponteiro para a AVL de rivais
	Tusuario *esq, *dir; //elo com o usuário a direita e a esquerda da árvore Splay
};

struct amigo_inimigo{
	Tusuario *info;
	int FB;
	Tamigo_inimigo *esq, *dir;
};

struct ranking_circulo{
	char nome[100];
	int num;
	Tranking_circulo *ant;
	Tranking_circulo *prox;
};

struct ranking_popular{
	char nome[100]; //nome do usuario
	int num; //número responsável pela 'popularidade'
	Tranking_popular *esq; //elo com o usuario a esquerda
	Tranking_popular *dir; //elo com o usuario a direita
};

//todas funções abaixo estão explicadas no header.c
Tusuario* Insere_Usuario(Tusuario *t, char nome[], FILE *saida);
Tusuario* Splay(Tusuario* t, char nome[], FILE *saida);
Tusuario* RotDir(Tusuario* t);
Tusuario* RotEsq(Tusuario* t);
void Exibe_Usuarios_Cresc(Tusuario *t, int *top, FILE *saida);
void Exibe_Usuarios_Decresc(Tusuario *t, int *top, FILE *saida);
void Exibe_Todos_Usuarios_Cresc(Tusuario *t, FILE *saida);
void Exibe_Todos_Usuarios_Decresc(Tusuario *t, FILE *saida);
Tusuario* Consulta_Usuario(Tusuario* t, char nome[]);
Tamigo_inimigo* InsereAmigo(Tamigo_inimigo* ptamigos, Tusuario* amigo, FILE *saida);
Tamigo_inimigo* InsereInimigo (Tamigo_inimigo* ptinimigos, Tusuario* inimigo, FILE *saida);
Tusuario* consultaAmigo(Tamigo_inimigo* pt, char nome[]);
Tusuario* consultaInimigo(Tamigo_inimigo* pt, char nome[]);
void Exibe_Todos_Amigos_Cresc(Tamigo_inimigo *t, FILE *saida);
void Exibe_Amigos_Cresc(Tamigo_inimigo *t, int *top, FILE *saida);
void Exibe_Amigos(Tusuario* t, int tipo, int top, FILE *saida);
void Cria_Ranking_amigo_inimigo (Tranking_popular **ptranking, Tusuario *ptusuario);
Tranking_popular* Insere_Ranking_amigo_inimigo (Tranking_popular *ptranking, Tusuario *ptusuario);
void Cria_Ranking_amigo (Tranking_popular **ptranking, Tusuario *ptusuario);
Tranking_popular* Insere_Ranking_amigo (Tranking_popular *ptranking, Tusuario *ptusuario);
void Cria_Ranking_inimigo (Tranking_popular **ptranking, Tusuario *ptusuario);
Tranking_popular* Insere_Ranking_inimigo (Tranking_popular *ptranking, Tusuario *ptusuario);
void Imprime_Todos_Ranking (Tranking_popular *ptranking, FILE *saida);
void Imprime_Ranking (Tranking_popular *ptranking, int *top, FILE *saida);
void Desenha(Tusuario* t, int nivel, int num);
void imprime_arvore (Tusuario*a);

Tamigo_inimigo* Insere_amigo (Tamigo_inimigo *a, Tusuario *x, int *ok, FILE *saida);
Tamigo_inimigo* Insere_inimigo (Tamigo_inimigo *a, Tusuario *x, int *ok, FILE *saida);
Tamigo_inimigo* Caso2 (Tamigo_inimigo *a , int *ok);
Tamigo_inimigo* Caso1 (Tamigo_inimigo* a , int *ok);
Tamigo_inimigo* rotacao_dupla_esquerda (Tamigo_inimigo* pt);
Tamigo_inimigo* rotacao_dupla_direita (Tamigo_inimigo* pt);
Tamigo_inimigo* rotacao_esquerda(Tamigo_inimigo *pt);
Tamigo_inimigo* rotacao_direita(Tamigo_inimigo *pt);
Tamigo_inimigo* Consulta_amigo_inimigo (Tamigo_inimigo *t, char nome[]);

Tfeed* Pushfeed(Tfeed* topo, char post[], char nome[]);
void Insere_Post_Amigo_Inimigo(Tamigo_inimigo *t, char post[], char nome[]);
void Insere_Post_Todos(Tusuario* t, char post[], char nome[]);
void Imprime_feed_todos_amigos(Tfeed* topo, Tusuario *t, int *achou, FILE* saida);
void Imprime_feed_todos_inimigos(Tfeed* topo, Tusuario *t, int *achou, FILE* saida);
void Imprime_feed_todos_amigos_inimigos(Tfeed* topo, Tusuario *t, int *achou, FILE* saida);

Tranking_circulo* Insere_ranking_circulo(Tranking_circulo *ptlista, char nome[]);
Tranking_circulo* Exclui_ranking_circulo(Tranking_circulo *ptlista);
void Percorre_amigos_rivais_circular(Tamigo_inimigo *t, Tranking_circulo **ptlista);
void Percorre_amigos_circular(Tamigo_inimigo *t, Tranking_circulo **ptlista);
void Percorre_amigos_amigos_circular(Tamigo_inimigo *t, Tranking_circulo **ptlista);
void Percorre_rivais_circular(Tamigo_inimigo *t, Tranking_circulo **ptlista);
void Percorre_rivais_rivais_circular(Tamigo_inimigo *t, Tranking_circulo **ptlista);
void Imprime_todos_ranking_circulo(Tranking_circulo *ptlista, FILE *saida);
void Imprime_ranking_circulo(Tranking_circulo *ptlista, int top, FILE *saida);

