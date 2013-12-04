

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
Tusuario* Insere_Usuario(Tusuario *t, char nome[]);
Tusuario* Splay(Tusuario* t, char nome[]);
Tusuario* RotDir(Tusuario* t);
Tusuario* RotEsq(Tusuario* t);
void Exibe_Usuarios_Cresc(Tusuario *t, int *top);
void Exibe_Usuarios_Decresc(Tusuario *t, int *top);
void Exibe_Todos_Usuarios_Cresc(Tusuario *t);
void Exibe_Todos_Usuarios_Decresc(Tusuario *t);
Tusuario* Consulta_Usuario(Tusuario* t, char nome[]);
Tamigo_inimigo* InsereAmigoInimigo(Tusuario* t, Tusuario* amigo, int tipo);
Tusuario* consultaAmigo(Tamigo_inimigo* pt, char nome[]);
Tusuario* consultaInimigo(Tamigo_inimigo* pt, char nome[]);
void Exibe_Amigos(Tusuario* t, int tipo, int top);
void Desenha(Tusuario* t, int nivel, int num);


