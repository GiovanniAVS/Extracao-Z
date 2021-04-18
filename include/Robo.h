#ifndef ROBO_H_
#define ROBO_H_
#include <iostream>
#include <math.h>

#define MAX 100

using namespace std;

struct node_t {
	char *elemento;
	node_t *proximo;
	node_t *anterior;
};

class ListaEncadeada{
    private:
        int num_elementos;
        node_t *inicio;
        node_t *final;
    public:
        ListaEncadeada();
        ~ListaEncadeada();
        int tamanho();
        node_t* get_inicio();
        char *get_iesimo(int i);
        void insere_elemento(char *dado);
        void insere_primeiro(char *dado);
        void remove_primeiro();
        void insere_iesimo(char *dado, int i);
        void remove_iesimo(int i);
        void apaga_lista();
        
};

class Robo{
    private:
        int id;
        int x;
        int y;
        bool ativado;
        bool executar;
        int aliensM;
        int recursosC;
        
    public:
        Robo();
        ~Robo();
        ListaEncadeada exits;
        void setX(int const x){ this->x = x; }
        void setY(int const y){ this->y = y; }
        void setId(int id) { this->id = id; }
        void setAtivacao(bool ativado) { this->ativado = ativado; }
        void setExecucao(bool executar) { this->executar = executar; }
        void setAliensM(int aliensM) { this->aliensM = aliensM + this->aliensM; }
        void setRecursosC(int recursosC) { this->recursosC = this->recursosC + recursosC; }
        void resetAliensM() { this->aliensM = 0; }
        void resetRecursosC() { this->recursosC = 0; }
        int getX() { return this-> x; }
        int getY() { return this-> y; }
        int getId() { return this -> id; }
        int getAtivacao() { return this->ativado; }
        int getExecucao() { return this->executar; }
        int getAliensM() { return this-> aliensM; }
        int getRecursosC() { return this-> recursosC; }

        
};

class VetorRobos{
    private:
        Robo *robos[49];
    public:
        VetorRobos();
        ~VetorRobos();

};


class Mapa{
    private:
        int ncolunas;
        int nlinhas;
        char **m; 
    public:
        Mapa(FILE *mapa);
        ~Mapa();
        void printMapa();
        char **getmapa() { return m; } 

};


void criar_listaC(ListaEncadeada *ldeC, FILE *comandos);

int criar_listaE(ListaEncadeada *ldeC, ListaEncadeada *ldeE, int *pos_comeco);

void iniciar(ListaEncadeada *ldeC, ListaEncadeada *ldeE, Robo **array_de_Robos, Mapa *mapa, FILE *SAIDA);

void destruir_robos(Robo **array_de_Robos);

Robo **criar_robos();

void printRelatorio(FILE *SAIDA, int id_comando, Robo **array_de_Robos);

#endif /*ROBO_H_*/