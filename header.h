typedef struct feed Tfeed;
typedef struct usuario Tusuario;
typedef struct amigo_inimigo Tamigo_inimigo;

void imprime_arvore (Tusuario*a);
struct feed{
	char texto[1000];
	Tfeed *prox;
};

struct usuario{
	char nome[100];
	Tfeed *ptfeed;
	Tamigo_inimigo *ptamigos;
	Tamigo_inimigo *ptinimigos;
	Tusuario *esq, *dir;
};

struct amigo_inimigo{
	Tusuario *info;
	Tamigo_inimigo *esq, *dir;
};

void input(Tusuario **ptusuario);
Tusuario* Insere_Usuario(Tusuario *t, char nome[], FILE *saida);
Tusuario* Splay(Tusuario* t, char nome[], FILE *saida);
Tusuario* RotDir(Tusuario* t);
Tusuario* RotEsq(Tusuario* t);
void Exibe_Usuarios_Cresc(Tusuario *t, int *top, FILE *saida);
void Exibe_Usuarios_Decresc(Tusuario *t, int *top, FILE *saida);
void Exibe_Todos_Usuarios_Cresc(Tusuario *t, FILE *saida);
void Exibe_Todos_Usuarios_Decresc(Tusuario *t, FILE *saida);
Tusuario* Consulta_Usuario(Tusuario* t, char nome[]);
Tamigo_inimigo* InsereAmigoInimigo(Tusuario* t, Tusuario* amigo, int tipo, FILE *saida);
Tamigo_inimigo* InsereABP(Tusuario* amigo, Tamigo_inimigo* a, char nome[]);
Tusuario* consultaAmigo(Tamigo_inimigo* pt, char nome[]);
Tusuario* consultaInimigo(Tamigo_inimigo* pt, char nome[]);
void Exibe_Todos_Amigos_Cresc(Tamigo_inimigo *t, FILE *saida);
void Exibe_Amigos_Cresc(Tamigo_inimigo *t, int *top, FILE *saida);
void Exibe_Amigos(Tusuario* t, int tipo, int top, FILE *saida);
void Desenha(Tusuario* t, int nivel, int num);
