#include <iostream>

#include <string>
#include <vector>
#include <GraphViewer/graphviewer.h>
#include "Utils.h"
#include "Point.h"
#include "Graph.h"
#include "parse.h"
#include "Company.h"
#include "Menu.h"

using namespace std;



Graph<Point> graph;




int main()
{
    cout << "Welcome to EatExpress!" << endl;
    cout << endl;
    Company c;









    c.readDelivererFile("../Deliverers.txt");



    //VER SE ID DOS RESTAURANTES DAS DELIVERIES É UM RESTAURANTE NO RESTAURANTES TXT, se não erro
    /*
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
    */

    //LER GRAFOS
    //iniciar GRAPHVIEWER
    //vector<Point> res;


    int city=opcaoCidade(c);
    int caso=opcaoCaso(c,city);

    graph.bfs(c.getDeliveries()[0].getClient().getId());

    GraphViewer gv = buildGraphViewer(graph);
    for(int i=0;i<c.getRestaurants().size();i++){
        gv.setVertexColor(c.getRestaurants()[i].getId(), "cyan");
    }

    if(caso==0){
        return 0;
    }


    //CASO BASE: UMA ENTREGA, UM RESTAURANTE, UM ESTAFETA, UM CLIENTE
    if(caso==1) {


        if(!graph.findVertex(c.getDeliveries()[0].getClient().getId())->getVisited()){
            cout << "Client address is not reacheable from restaurant. Delivery cannot be made" << endl;
            return -2;
        }

        cout << "Calculating route, please wait..." << endl;

        //TODO:bidirectional dijkstra

        vector<Point> perfectPath;


        graph.dijkstraShortestPath(c.getDeliveries()[0].getRestaurant()[0].getId()); //for now its just unidirectional dijkstra
        perfectPath = graph.getPath(c.getDeliveries()[0].getRestaurant()[0].getId(),c.getDeliveries()[0].getClient().getId());
        for(int i=0;i<perfectPath.size();i++){
            gv.setVertexColor(perfectPath[i].getID(), "green");
        }
        gv.setVertexColor(perfectPath[0].getID(), "red");
        gv.setVertexColor(perfectPath[perfectPath.size()-1].getID(), "red");

        double dist=graph.findVertex(perfectPath[perfectPath.size()-1].getID())->getDist();
        cout<<"O estafeta encarregado da sua entrega e: "<<c.decideDeliverer(dist,c.getDeliveries()[0].calculateOccupiedSpace()).getID()<<endl;

    }

    else{


        //Caso 2: mesmo cliente, várias deliveries de vários restaurantes
        if(caso==2) {

            vector<Point> temp_result, result;

            vector<Restaurant> deliveryRestaurants = c.getDeliveries()[0].getRestaurant();
            double dist= 0;
            int min_distance = 999999999;
            int smallest_distance_index = 0;

            for (int i = 0; i < c.getDeliveries()[0].getRestaurant().size(); i++) {
                graph.Astar(c.getClients()[0].getId(), c.getDeliveries()[0].getRestaurant()[i].getId());

                if (graph.findVertex(c.getDeliveries()[0].getRestaurant()[i].getId())->getDist() < min_distance) {
                    temp_result = graph.getPath(c.getClients()[0].getId(), c.getDeliveries()[0].getRestaurant()[i].getId());
                    smallest_distance_index = i;
                    min_distance = graph.findVertex(c.getDeliveries()[0].getRestaurant()[i].getId())->getDist();
                }
            }

            result.insert(result.end(),temp_result.begin(),temp_result.end());     //caminho mais rápido da casa do cliente ao primeiro restaurante


            dist+=min_distance;
            min_distance = 999999999;   //reset min_distance

            int smallest_restaurant_distance = 0;
            //percorrer restantes restaurantes e ver caminho mais rápido entre cada um deles; adicionar ao resultado final até terem sido visitados todos os restaurantes
            while (c.getDeliveries()[0].getRestaurant().size() != 1){

                min_distance = 999999999;


                for (int i = 0; i < c.getDeliveries()[0].getRestaurant().size(); i++) {
                    if(i==smallest_distance_index) continue;

                    graph.Astar(c.getDeliveries()[0].getRestaurant()[smallest_distance_index].getId(), c.getDeliveries()[0].getRestaurant()[i].getId());

                    if (graph.findVertex(c.getDeliveries()[0].getRestaurant()[i].getId())->getDist() < min_distance) {
                        temp_result = graph.getPath(c.getDeliveries()[0].getRestaurant()[smallest_distance_index].getId(), c.getDeliveries()[0].getRestaurant()[i].getId());
                        smallest_restaurant_distance = i;
                        min_distance = graph.findVertex(c.getDeliveries()[0].getRestaurant()[i].getId())->getDist();
                    }
                }
                dist+=min_distance;
                result.insert(result.end(),temp_result.begin(),temp_result.end());
                vector <Restaurant> r = c.getDeliveries()[0].getRestaurant();
                r.erase(r.begin()+smallest_distance_index);
                vector<Delivery> d = c.getDeliveries();
                d[0].setRestaurant(r);
                c.setDeliveries(d);
                smallest_distance_index = smallest_restaurant_distance;

            }

            cout<<"O estafeta encarregado da sua entrega tem o ID: "<<c.decideDeliverer(dist,c.getDeliveries()[0].calculateOccupiedSpace()).getID()<<endl;
            for(int i=0;i<result.size();i++){
                gv.setVertexColor(result[i].getID(), "green");
            }
            gv.setVertexColor(result[0].getID(), "red");

            for(unsigned int i = 0;i<deliveryRestaurants.size();i++){
                gv.setVertexColor(deliveryRestaurants[i].getId(), "red");
            }

        }





        //Caso 3: mesmo restaurante, vários clientes


        if(caso==3){


            vector<Point> temp_result, result;

            vector<Client> deliveryClients = c.getClients();
            double dist= 0;
            int min_distance = 999999999;
            int smallest_distance_index = 0;

            for (int i = 0; i < c.getClients().size(); i++) {
                graph.Astar(c.getDeliveries()[0].getRestaurant()[0].getId(), c.getClients()[i].getId());
                if (graph.findVertex(c.getClients()[i].getId())->getDist() < min_distance) {
                    temp_result = graph.getPath(c.getDeliveries()[0].getRestaurant()[0].getId(),c.getClients()[i].getId());
                    smallest_distance_index = i;
                    min_distance = graph.findVertex(c.getClients()[i].getId())->getDist();
                }
            }
            dist+=min_distance;
            result.insert(result.end(),temp_result.begin(),temp_result.end());


            min_distance = 999999999;   //reset min_distance

            int smallest_client_distance = 0;

            while (c.getClients().size() != 1){

                min_distance = 999999999;


                for (int i = 0; i < c.getClients().size(); i++) {
                    if(i==smallest_distance_index) continue;

                    graph.Astar(c.getClients()[smallest_distance_index].getId(), c.getClients()[i].getId());

                    if (graph.findVertex(c.getClients()[i].getId())->getDist() < min_distance) {
                        temp_result = graph.getPath(c.getClients()[smallest_distance_index].getId(), c.getClients()[i].getId());
                        smallest_client_distance = i;
                        min_distance = graph.findVertex(c.getClients()[i].getId())->getDist();
                    }
                }
                dist+=min_distance;
                result.insert(result.end(),temp_result.begin(),temp_result.end());
                vector <Client> cli = c.getClients();
                cli.erase(cli.begin()+smallest_distance_index);
                c.setClients(cli);
                smallest_distance_index = smallest_client_distance;

            }
            cout<<"O estafeta encarregado da sua entrega tem o ID: "<<c.decideDeliverer(dist,c.getDeliveries()[0].calculateOccupiedSpace()).getID()<<endl;
            for(int i=0;i<result.size();i++){
                gv.setVertexColor(result[i].getID(), "green");
            }
            gv.setVertexColor(result[0].getID(), "red");

            for(unsigned int i = 0;i<deliveryClients.size();i++){
                gv.setVertexColor(deliveryClients[i].getId(), "red");
            }
        }
    }


    system("pause");
    return 0;
}