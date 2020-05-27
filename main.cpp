#include <iostream>

#include <string>
#include <GraphViewer/graphviewer.h>
#include "Utils.h"
#include "Point.h"
#include "Graph.h"
#include "Company.h"
#include "Menu.h"
#include "NearestNeighbourAlgorithms.h"

using namespace std;

Graph<Point> graph;


int main()
{
    cout << "Welcome to EatExpress!" << endl;
    cout << endl;
    Company c;

    c.readDelivererFile("../Deliverers.txt");

    //VER SE ID DOS RESTAURANTES DAS DELIVERIES É UM RESTAURANTE NO RESTAURANTES TXT, se não erro
    bool found=false;
    for(unsigned int i =0; i<c.getDeliveries().size();i++){
        for(unsigned int j=0; j<c.getRestaurants().size();j++){
            for(unsigned int k=0; k<c.getDeliveries()[i].getRestaurant().size();k++){
                if(c.getDeliveries()[i].getRestaurant()[k].getId() == c.getRestaurants()[j].getId()){
                    found =true;
                    break;
                }
            }
        }
        if(!found){
            cout << "One of the deliveries doesn't have a restaurant as its origin. Please check the ID of the restaurant." << endl;
            return -1;
        }
    }




    //menus -> leitura dos mapas para grafo
    int city=opcaoCidade(c);
    if(city==0){return 0;}

    int caso=opcaoCaso(c,city);
    if(caso==0){return 0;}


    //análise da conectividade
    graph.bfs(c.getDeliveries()[0].getClient().getId());

    //iniciar GRAPHVIEWER
    GraphViewer gv = buildGraphViewer(graph);
    for(int i=0;i<c.getRestaurants().size();i++){
        gv.setVertexColor(c.getRestaurants()[i].getId(), "cyan");
    }

    //Exit program
    if(caso==0){
        return 0;
    }

    //CASO BASE: UMA ENTREGA, UM RESTAURANTE, UM ESTAFETA, UM CLIENTE
    if(caso==1) {
        int i;
        if((i=case1(c,graph,gv)) != 0){return i;}
    }


    //Caso 2: mesmo cliente, várias deliveries de vários restaurantes
    if(caso==2) {
        int i;
        if((i=case2(c,graph,gv)) != 0){return i;}
    }


    //Caso 3: mesmo restaurante, vários clientes
    if(caso==3){
        int i;
        if((i=case3(c,graph,gv)) != 0){return i;}
    }


    //Caso 4: vários restaurantes, vários clientes
    if(caso==4){
        int i;
        if((i=case4(c,graph,gv)) != 0){return i;}
    }


    //Caso 5: Cálculo de várias rotas simples, vários estafetas a efetuar entregas do tipo 1
    if(caso==5){
        int i;
        if((i=case5(c,graph,gv)) != 0){return i;}
    }


    //Caso 6: Cálculo de várias rotas do caso 2 para vários estafetas
    if(caso==6){
        int i;
        if((i=case6(c,graph,gv)) != 0){return i;}
    }


    //Caso 7: Cálculo de várias rotas do caso 3 para vários estafetas
    if(caso==7){
        int i;
        if((i=case7(c,graph,gv)) != 0){return i;}
    }

    return 0;
}