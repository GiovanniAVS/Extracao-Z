#include <iostream>
#include <math.h>
#include "Robo.h"
#include <string.h> //string::find string::substr string::erase std::stoi
#include <stdio.h>

#define MAX 100
#define MAXR 50

using namespace std;

Robo::Robo(){
    this->setX(0);
    this->setY(0);
    this->setId(51);
    this->setAtivacao(false);
    this->setExecucao(false);
    this->resetAliensM();
    this->resetRecursosC();
}

Robo::~Robo(){
   
}

Mapa::Mapa(FILE *mapa){
    int l,i,j,car,c; 

   
   
    fscanf(mapa, "%i %i", &l, &c);
    this->ncolunas = c;
    this->nlinhas = l;
    this->m = new char *[l]; 
    
    for(i = 0 ; i < nlinhas; i++){ 
        this->m[i] = new char[c];
        for(j = 0; j < ncolunas; j++){
            car = fgetc(mapa);
            if (car == ' ' || car == '\n' || car == '\r') {
                j--;
                continue;
            }
            m[i][j] = car;
        }      
    }
}

Mapa::~Mapa(){

}

void Mapa::printMapa(){
    int i,j;

    cout<< this->nlinhas <<" "<< this->ncolunas << endl;

    for(i = 0; i < nlinhas; i++){
        for(j = 0; j < ncolunas; j++){
            cout << m[i][j] << " ";
        }
        cout << "\n";

    }
}

ListaEncadeada::ListaEncadeada(){
     this-> num_elementos = 0;
     this-> inicio = nullptr;
     this-> final = nullptr;
 };

ListaEncadeada::~ListaEncadeada(){
     while(this->num_elementos != 0){
         remove_iesimo(0); 
     }
 };

Robo **criar_robos(){
    
    Robo **all = new Robo*[50];
    
        for(int i = 0; i<50; i++){
            all[i] = new Robo();
            all[i]->setId(i);
        }   

    return all;
}

void destruir_robos(Robo **array_de_Robos){
    for(int i = 0; i < 50; i++){
        delete array_de_Robos[i];
    }
    delete array_de_Robos;


}



void criar_listaC(ListaEncadeada *ldeC, FILE *comandos){
    int comeco = 0;
    int count = 0;
    char *comando;

    while (true){ 
        comando = new char[20];
        if(fgets(comando, 20, comandos) == NULL){ 
            break;
        }

        if (comando[0] == '*')
            ldeC->insere_iesimo(comando,(comeco+1));
        else if(comando[0] == 'E' && comando [1] == 'X'){
                comeco=count;
                ldeC->insere_elemento(comando);
        }

        else
            ldeC->insere_elemento(comando);
        count++;

    }

    int tam = ldeC->tamanho();

    for (int i = 0; i < tam; i++){
        cout << ldeC->get_iesimo(i);
    }
    

}

int criar_listaE(ListaEncadeada *ldeC, ListaEncadeada *ldeE, int *pos_comeco){

    int i = 0;
    char *aux;
    int tam = ldeC->tamanho();
    int id_ex = 0;

    node_t *atual = ldeC->get_inicio();

    while(i<tam){
        aux = atual->elemento;
        char* comando = new char[20];
        strcpy(comando,aux);
        if(comando[0] == 'E' && comando[1] == 'X'){
                *pos_comeco = i + 1; //TALVEZ TIRAR ESSA PARTE
                ldeE->insere_elemento(comando);
                id_ex =  atoi(&comando[9]);
                break;
        }
        
        else
            ldeE->insere_elemento(comando);
        i++;

        atual = atual->proximo;
    }

    return id_ex;

}

void printRelatorio(FILE *SAIDA, int id_comando, Robo **array_de_Robos){
    int i;
    int tam = array_de_Robos[id_comando]->exits.tamanho();
    node_t *atual = array_de_Robos[id_comando]->exits.get_inicio();
    for (i = 0; i < tam; i++){
        fprintf(SAIDA,"%s \n",atual->elemento);
        atual = atual->proximo;
    }

    for(i = 0; i<(tam-1); i++){
        array_de_Robos[id_comando]->exits.remove_iesimo(0);
    }
    array_de_Robos[id_comando]->exits.apaga_lista();

}

void iniciar(ListaEncadeada *ldeC, ListaEncadeada *ldeE, Robo **array_de_Robos, Mapa *mapa, FILE *SAIDA){
    int tamC =ldeC->tamanho();
    int tamE;
    int id_comando, pos_X, pos_Y, id_ex, aliensT = 0, recursosT = 0;
    char *ordem;
    char *saida;
    int i;
    char **MAPA = mapa->getmapa();
    int pos_comeco = 0;
    int contador = 0;
    int aux = 0;


while(tamC != 1){ 


    criar_listaE(ldeC, ldeE, &pos_comeco);


    if (pos_comeco < ldeC->tamanho()){
        for ( i = 0; i < pos_comeco; i++){
            ldeC->remove_primeiro();
        }
    }
    else{
        for(i = 0; i < ldeC->tamanho(); i++){
            ldeC->remove_iesimo(aux);
        }
    }

    tamC =ldeC->tamanho();
    node_t *atual = ldeE->get_inicio();
    tamE = ldeE->tamanho();

    for(i = 0; i<tamE; i++){
        ordem = new char[13];
        saida = new char[50];
        ordem = atual->elemento;
        if(ordem[0] == 'A' ){   //ATIVAR
            if(isdigit(ordem[8]))
                id_comando = (10*(ordem[7] - 48) +(ordem[8] - 48));
            if(isdigit(ordem[8]) == 0)
                id_comando = (ordem[7] - 48);
            if(array_de_Robos[id_comando]->getAtivacao()){
                sprintf(saida,"BASE: ROBO %d JA ESTA EM MISSAO",id_comando);
                fprintf(SAIDA,"%s \n",saida);
                
            }
            else{
                sprintf(saida,"BASE: ROBO %d SAIU EM MISSAO",id_comando);
                array_de_Robos[id_comando]->setAtivacao(true);
                fprintf(SAIDA,"%s \n",saida);

            }
        }
        else if(ordem[0] == 'E' && ordem[1] == 'X'){ //EXECUTAR
            if(isdigit(ordem[10]))
                id_comando = (10*(ordem[9] - 48) +(ordem[10] - 48));
            if(isdigit(ordem[10]) == 0)
                id_comando = (ordem[9] - 48);
            if(array_de_Robos[id_comando]->getAtivacao() == 0){
                sprintf(saida,"BASE: ROBO %d NAO ESTA EM MISSAO",id_comando);
                fprintf(SAIDA,"%s \n",saida);
            }
            else{
                array_de_Robos[id_comando]->setExecucao(true);
            }
        }
        else if(ordem[0] == 'R' && ordem[2] == 'L'){  //RELATORIO 
            if(isdigit(ordem[11]))
                id_comando = (10*(ordem[10] - 48) +(ordem[11] - 48));
            if(isdigit(ordem[11]) == 0)
                id_comando = (ordem[10] - 48);
            if(array_de_Robos[id_comando]->getExecucao() == true){
                printRelatorio(SAIDA, id_comando, array_de_Robos);
            }
        } 
        else if(ordem[2] == 'T'){ //RETORNAR 
            if(isdigit(ordem[10]))
                id_comando = (10*(ordem[9] - 48) +(ordem[10] - 48));
            if(isdigit(ordem[10]) == 0)
                id_comando = (ordem[9] - 48);
            if(array_de_Robos[id_comando]->getAtivacao() == 0){
                sprintf(saida,"BASE: ROBO %d NAO ESTA EM MISSAO",id_comando);
                fprintf(SAIDA,"%s \n",saida);
            }
            else{
                array_de_Robos[id_comando]->setX(0);
                array_de_Robos[id_comando]->setX(0);
                array_de_Robos[id_comando]->setAtivacao(false);
                sprintf(saida,"BASE: ROBO %d RETORNOU ALIENS %d RECURSOS %d",id_comando,array_de_Robos[id_comando]->getAliensM(), array_de_Robos[id_comando]->getRecursosC());
                fprintf(SAIDA,"%s \n",saida);
                aliensT = aliensT + array_de_Robos[id_comando]->getAliensM();
                recursosT = recursosT + array_de_Robos[id_comando]->getRecursosC();
                array_de_Robos[id_comando]->resetAliensM();
                array_de_Robos[id_comando]->resetRecursosC();

            }
        }
        else if(ordem[0] == 'M' && array_de_Robos[id_comando]->getAtivacao() == true){ //MOVER 
            if(isdigit(ordem[7])){
                id_comando = (10*(ordem[6] - 48) +(ordem[7] - 48));
                pos_X = ordem[10] - 48;
                pos_Y = ordem[12] - 48;
            }
            if(isdigit(ordem[7]) == 0){
                id_comando = (ordem[6] - 48);
                pos_X = ordem[9] - 48;
                pos_Y = ordem[11] - 48;
            }

            if(MAPA[pos_X][pos_Y] == 'O'){ 
                sprintf(saida,"ROBO %d: IMPOSSIVEL MOVER PARA (%d,%d)",id_comando,pos_X,pos_Y);
                array_de_Robos[id_comando]->exits.insere_elemento(saida);
            }
            else{
                array_de_Robos[id_comando]->setX(pos_X);
                array_de_Robos[id_comando]->setY(pos_Y);
                sprintf(saida,"ROBO %d: MOVEU PARA (%d,%d)",id_comando,pos_X,pos_Y);
                array_de_Robos[id_comando]->exits.insere_elemento(saida);
            } 
        }
        else if(ordem[0] == 'C' && array_de_Robos[id_comando]->getAtivacao() == true){ //COLETAR 
            if(isdigit(ordem[9]))
                id_comando = (10*(ordem[8] - 48) +(ordem[9] - 48));
            if(isdigit(ordem[9]) == 0)
                id_comando = (ordem[8] - 48);
            pos_X = array_de_Robos[id_comando]->getX();
            pos_Y = array_de_Robos[id_comando]->getY();
            if(MAPA[pos_X][pos_Y] == 'R'){
                array_de_Robos[id_comando]->setRecursosC(1);
                sprintf(saida,"ROBO %d: RECURSOS COLETADOS EM (%d,%d)",id_comando , pos_X, pos_Y);
                array_de_Robos[id_comando]->exits.insere_elemento(saida);
                MAPA[pos_X][pos_Y] = '.';

            } 
            else{
                sprintf(saida,"ROBO %d: IMPOSSIVEL COLETAR RECURSOS EM (%d,%d)",id_comando , pos_X, pos_Y);
                array_de_Robos[id_comando]->exits.insere_elemento(saida);
            }

                
        }
        else if(ordem[0] == 'E' && ordem[1] == 'L'  && array_de_Robos[id_comando]->getAtivacao() == true){ //ELIMINAR
            if(isdigit(ordem[10]))
                id_comando = (10*(ordem[9] - 48) +(ordem[10] - 48));
            if(isdigit(ordem[10]) == 0)
                id_comando = (ordem[9] - 48); 
            pos_X = array_de_Robos[id_comando]->getX();
            pos_Y = array_de_Robos[id_comando]->getY();
            if(MAPA[pos_X][pos_Y] == 'H'){
                array_de_Robos[id_comando]->setAliensM(1);
                sprintf(saida,"ROBO %d: ALIEN ELIMINADO EM (%d,%d)",id_comando , pos_X, pos_Y);
                array_de_Robos[id_comando]->exits.insere_elemento(saida);
                MAPA[pos_X][pos_Y] = '.';

            } 
            else{
                sprintf(saida,"ROBO %d: IMPOSSIVEL ELIMINAR ALIEN EM (%d,%d)", id_comando, pos_X, pos_Y);
                array_de_Robos[id_comando]->exits.insere_elemento(saida);
            }
        }
        else if(ordem[1] == 'M' && ordem[0] == '*'  && array_de_Robos[id_comando]->getAtivacao() == true){ //MOVER
            if(isdigit(ordem[8])){
                id_comando = (10*(ordem[7] - 48) +(ordem[8] - 48));
                pos_X = ordem[11] - 48;
                pos_Y = ordem[13] - 48;
            }
            if(isdigit(ordem[8]) == 0){
                id_comando = ordem[7] - 48;
                pos_X = ordem[10] - 48;
                pos_Y = ordem[12] - 48;
            }
            

            if(MAPA[pos_X][pos_Y] == 'O'){ 
                sprintf(saida,"ROBO %d: IMPOSSIVEL MOVER PARA (%d,%d)",id_comando, pos_X, pos_Y);
                array_de_Robos[id_comando]->exits.insere_elemento(saida);
            }
            else{
                array_de_Robos[id_comando]->setX(pos_X);
                array_de_Robos[id_comando]->setY(pos_Y);
                sprintf(saida,"ROBO %d: MOVEU PARA (%d,%d)", id_comando, pos_X, pos_Y);
                array_de_Robos[id_comando]->exits.insere_elemento(saida);
            } 
        }
        else if(ordem[1] == 'C' && ordem[0] == '*'  && array_de_Robos[id_comando]->getAtivacao() == true){ //COLETAR 
            if(isdigit(ordem[10]))
                id_comando = (10*(ordem[9] - 48) +(ordem[10] - 48));
            if(isdigit(ordem[9]) == 0)
                id_comando = (ordem[9] - 48);
            pos_X = array_de_Robos[id_comando]->getX();
            pos_Y = array_de_Robos[id_comando]->getY();
            if(MAPA[pos_X][pos_Y] == 'R'){
                array_de_Robos[id_comando]->setRecursosC(1);
                sprintf(saida,"ROBO %d: RECURSOS COLETADOS EM (%d,%d)", id_comando, pos_X, pos_Y);
                array_de_Robos[id_comando]->exits.insere_elemento(saida);
                MAPA[pos_X][pos_Y] = '.';
            } 
            else{
                sprintf(saida,"ROBO %d: IMPOSSIVEL MOVER PARA (%d,%d)", id_comando, pos_X, pos_Y);
                array_de_Robos[id_comando]->exits.insere_elemento(saida);
            }
        }
        else if(ordem[0] == '*' && ordem[1] == 'E' && ordem[2] == 'L' ){ //ELIMINAR
            if(isdigit(ordem[11]))
                id_comando = (10*(ordem[10] - 48) +(ordem[11] - 48));
            if(isdigit(ordem[11]) == 0)
                id_comando = (ordem[10] - 48); 
            pos_X = array_de_Robos[id_comando]->getX();
            pos_Y = array_de_Robos[id_comando]->getY();
            if(MAPA[pos_X][pos_Y] == 'H'){
                array_de_Robos[id_comando]->setAliensM(1);
                sprintf(saida,"ROBO %d: ALIEN ELIMINADO EM (%d,%d)",id_comando , pos_X, pos_Y);
                array_de_Robos[id_comando]->exits.insere_elemento(saida);
                MAPA[pos_X][pos_Y] = '.';

            } 
            else{
                sprintf(saida,"ROBO %d: IMPOSSIVEL ELIMINAR ALIEN EM (%d,%d)", id_comando, pos_X, pos_Y);
                array_de_Robos[id_comando]->exits.insere_elemento(saida);
            }
        }

        else{
            cout <<"COMANDO ERRADO OU O ROBO NAO ESTA ATIVADO \n";
        }

        atual = atual->proximo;
    }

    for(i = 0; i<(tamE-1); i++){
        ldeE->remove_iesimo(aux);
    }
    ldeE->apaga_lista();
    tamC= ldeC->tamanho(); 
    contador++;
}

    cout << "\n";
    cout << "\n";
    mapa->printMapa();

    sprintf(saida,"BASE: TOTAL ALIENS %d RECURSOS %d",aliensT, recursosT);
    fprintf(SAIDA,"%s \n",saida);
}

node_t* ListaEncadeada::get_inicio(){
    return this->inicio;
}


void ListaEncadeada::insere_elemento(char *dado){
     node_t *novo  =  new node_t();
     novo->elemento = dado;

     if(this->num_elementos == 0){
         this->inicio =  novo;
         this->final =  novo;
     }
     else{
         this->final->proximo = novo;
         novo->anterior = final;
         this->final = novo;
     }
     this->num_elementos++;
 };
 
 void ListaEncadeada::insere_primeiro(char *dado){
     node_t *novo = new node_t();
     novo->elemento = dado;
     if(this->num_elementos == 0){
         this->inicio = novo;
         this->final = novo;
     }
     else{
         this->inicio->anterior = novo;
         novo->proximo = inicio;
         inicio = novo;
     }
     this->num_elementos++;
 };

char *ListaEncadeada::get_iesimo(int i){
     if(i >= this->num_elementos){
         return NULL;
     }
     node_t *atual = this->inicio;
     for(int j = 0; j<i; j++){
         atual= atual->proximo;
     }

     return atual->elemento;
         
 };

 int ListaEncadeada::tamanho(){
     return this->num_elementos;
 };

 void ListaEncadeada::remove_iesimo(int i){
    if (i >= this->num_elementos)
        return;
    node_t *atual = this->inicio;
    node_t *anterior = nullptr;
    if (i == this->num_elementos - 1){
        atual = this->final;
        this->final = this->final->anterior;
        delete atual->elemento;
        delete atual;
        return;
    }
    for (int j = 0; j < i; j++) {
        anterior = atual;
        atual = atual->proximo;
    }
    if (i != 0)
        anterior->proximo = atual->proximo;
    else if (i == 0)
        this->inicio = atual->proximo;
    this->num_elementos--;
    delete atual->elemento;
    delete atual;
 };

void ListaEncadeada::apaga_lista(){
    this->inicio = nullptr;
    this->final = nullptr;
    this->num_elementos = 0;
}

 void ListaEncadeada::remove_primeiro(){
     this->inicio = inicio->proximo;
     this->inicio->anterior = nullptr;
     if (this->tamanho() == 1){
        this->inicio->anterior = nullptr;
        this->inicio->proximo = nullptr;
        
     }
     num_elementos--;
     
 };


 void ListaEncadeada::insere_iesimo(char *dado, int i){
     if(i > num_elementos){
         return;
     }
     node_t *novo = new node_t();
     novo->elemento = dado;
     if(i == 0){
         this->inicio = novo;
         this->final = novo;
         num_elementos++;
         return;
     }
     else if(i == num_elementos){
         this->final->proximo = novo;
         novo->anterior = this->final;
         num_elementos++;
         return;
     }
     else{
         node_t *atual = this->inicio;
         for(int j = 0; j < i; j++){
             atual=atual->proximo;
         }
         novo->anterior = atual->anterior;
         novo->proximo = atual;
         atual->anterior = novo;
         novo->anterior->proximo = novo;
         num_elementos++;
     }
 };















