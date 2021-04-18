#include <iostream>
#include <stdio.h>
#include <string.h>
#include "Robo.h"
//g++ main.cpp Robo.cpp Robo.h -o Robo.exe

#define MAX 100

using namespace std;



int main(){

    FILE *mapa;
    FILE *comandos;
    FILE *saida;

    mapa = fopen("mapa.txt","r");
    comandos = fopen("comandos.txt","r");
    saida = fopen("saida.txt","w");
    if(mapa == NULL){
        cout << "Nao foi possivel abrir o arquivo do mapa \n";
        exit(0);
    }

    if(comandos == NULL){
        cout << "Nao foi possivel abrir o arquivo dos comandos \n";
        exit(0);
    } 



    if(saida == NULL){
        cout << "Nao foi possivel abrir o arquivo das saidas \n";
        exit(0);
    }

    Mapa m1(mapa);
    m1.printMapa();
    cout<<"\n \n";

    ListaEncadeada ldeC;
    ListaEncadeada ldeE;
    
    criar_listaC(&ldeC, comandos);
    Robo **array_de_Robos = criar_robos();

    iniciar(&ldeC, &ldeE, array_de_Robos, &m1, saida);
   

fclose(mapa);
fclose(comandos);
fclose(saida);
destruir_robos(array_de_Robos);




cout<<"fim \n";

return 0;

}
   
 