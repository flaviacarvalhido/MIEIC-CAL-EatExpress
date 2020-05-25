#include <iostream>

#include <string>
#include <vector>
#include <GraphViewer/graphviewer.h>
#include "Utils.h"
#include "Point.h"
#include "Graph.h"
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


    //LER GRAFOS
    //iniciar GRAPHVIEWER

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
            cout << "Client with ID " << c.getDeliveries()[0].getClient().getId() << "is not reacheable. Can't reach this destination, try another one."<<endl;
            return -3;
        }

        if(!graph.findVertex(c.getDeliveries()[0].getRestaurant()[0].getId())->getVisited()){
            cout << "Restaurant with ID " << c.getDeliveries()[0].getRestaurant()[0].getId() << "is not reacheable. Can't reach this destination, try another one."<<endl;
            return -3;
        }

        cout << "Calculating route, please wait..." << endl;

        vector<Point> perfectPath;


        graph.dijkstraShortestPath(c.getDeliveries()[0].getRestaurant()[0].getId());
        perfectPath = graph.getPath(c.getDeliveries()[0].getRestaurant()[0].getId(),c.getDeliveries()[0].getClient().getId());
        for(int i=0;i<perfectPath.size();i++){
            gv.setVertexColor(perfectPath[i].getID(), "green");
        }

        gv.setVertexColor(perfectPath[perfectPath.size()-1].getID(), "red");

        gv.setVertexColor(perfectPath[0].getID(),"black");
        gv.setVertexLabel(perfectPath[0].getID(),"origin");

        double dist=graph.findVertex(perfectPath[perfectPath.size()-1].getID())->getDist();
        cout<<"O estafeta encarregado da sua entrega e: "<<c.decideDeliverer(dist,c.getDeliveries()[0].calculateOccupiedSpace()).getID()<<endl;

    }




    //Caso 2: mesmo cliente, várias deliveries de vários restaurantes
    if(caso==2) {

        vector<Point> temp_result, result;

        vector<Restaurant> deliveryRestaurants = c.getDeliveries()[0].getRestaurant();
        double dist= 0;
        int min_distance = 999999999;
        int smallest_distance_index = 0;

        for(unsigned int i=0;i<deliveryRestaurants.size();i++){
            if(!graph.findVertex(deliveryRestaurants[i].getId())->getVisited()){
                cout << "Restaurant with ID " << deliveryRestaurants[i].getId() << "is not reacheable. Can't reach this destination, try another one."<<endl;
                return -3;
            }
        }
        if(!graph.findVertex(c.getClients()[0].getId())->getVisited()){
            cout << "Client with ID " << c.getClients()[0].getId() << "is not reacheable. Can't reach this destination, try another one."<<endl;
            return -3;
        }

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

            if(smallest_restaurant_distance > smallest_distance_index){
                smallest_restaurant_distance--;
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

        gv.setVertexColor(result[result.size()-1].getID(),"black");
        gv.setVertexLabel(result[result.size()-1].getID(),"origin");
    }



    //Caso 3: mesmo restaurante, vários clientes
    if(caso==3){


        vector<Point> temp_result, result;

        vector<Client> deliveryClients = c.getClients();
        double dist= 0;
        int min_distance = 999999999;
        int smallest_distance_index = 0;

        for(unsigned int i=0;i<deliveryClients.size();i++){
            if(!graph.findVertex(deliveryClients[i].getId())->getVisited()){
                cout << "Client with ID " << deliveryClients[i].getId() << "is not reacheable. Can't reach this destination, try another one."<<endl;
                return -3;
            }
        }
        if(!graph.findVertex(c.getDeliveries()[0].getRestaurant()[0].getId())->getVisited()){
            cout << "Restaurant with ID " << c.getDeliveries()[0].getRestaurant()[0].getId() << "is not reacheable. Can't reach this destination, try another one."<<endl;
            return -3;
        }

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

            if(smallest_client_distance > smallest_distance_index){
                smallest_client_distance--;
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

        gv.setVertexColor(result[0].getID(),"black");
        gv.setVertexLabel(result[0].getID(),"origin");
    }


    if(caso==4){


        //make restaurant vector and client vector only have unique values
        vector<Restaurant> r = c.getTotalDeliveryRestaurants();
        sort(r.begin(),r.end());
        for(unsigned int i=1; i< r.size();i++){
            if(r[i-1].getId() == r[i].getId()){
                r.erase(r.begin()+i);
            }
        }
        for(unsigned int i=0;i<r.size();i++){
            if(!graph.findVertex(r[i].getId())->getVisited()){
                cout << "Restaurant with ID " << r[i].getId() << "is not reacheable. Can't reach this destination, try another one."<<endl;
                return -3;
            }
        }
        c.setTotalDeliveryRestaurants(r);

        vector<Client> cli = c.getClients();
        sort(cli.begin(),cli.end());
        for(unsigned int j=1;j<cli.size();j++){
            if(cli[j-1].getId() == cli[j].getId()){
                cli.erase(cli.begin()+j);
            }
        }
        for(unsigned int i=0;i<cli.size();i++){
            if(!graph.findVertex(cli[i].getId())->getVisited()){
                cout << "Client with ID " << cli[i].getId() << "is not reacheable. Can't reach this destination, try another one."<<endl;
                return -3;
            }
        }
        c.setClients(cli);


        vector<Point> temp_result, result;
        double dist= 0;
        int min_distance = 999999999;
        int smallest_distance_index = 0, temp_distance_index=0;


        //goes to all restaurants first
        while(c.getTotalDeliveryRestaurants().size() != 1) {


            for (unsigned int i = 0; i < c.getTotalDeliveryRestaurants().size(); i++) {
                if(smallest_distance_index == i) continue;

                graph.Astar(c.getTotalDeliveryRestaurants()[smallest_distance_index].getId(),c.getTotalDeliveryRestaurants()[i].getId());

                if (graph.findVertex(c.getTotalDeliveryRestaurants()[i].getId())->getDist() < min_distance && graph.findVertex(c.getTotalDeliveryRestaurants()[i].getId())->getVisited()) {
                    temp_result = graph.getPath(c.getTotalDeliveryRestaurants()[smallest_distance_index].getId(),
                                                c.getTotalDeliveryRestaurants()[i].getId());
                    temp_distance_index = i;
                    min_distance = graph.findVertex(c.getClients()[i].getId())->getDist();
                }

            }
            if(smallest_distance_index<temp_distance_index){
                temp_distance_index--;
            }
            vector<Restaurant> r = c.getTotalDeliveryRestaurants();
            r.erase(r.begin()+smallest_distance_index);
            c.setTotalDeliveryRestaurants(r);

            smallest_distance_index = temp_distance_index;
            min_distance=999999999;

            result.insert(result.end(),temp_result.begin(),temp_result.end());

        }

        //then goes to all clients ( first to nearest client, then to the others)
        min_distance=999999999;
        int last_restaurant_index = 0;


        for(unsigned int i=0;i<c.getClients().size();i++){
            graph.Astar(c.getTotalDeliveryRestaurants()[last_restaurant_index].getId(),c.getClients()[i].getId());

            if (graph.findVertex(c.getClients()[i].getId())->getDist() < min_distance) {
                temp_result = graph.getPath(c.getTotalDeliveryRestaurants()[last_restaurant_index].getId(),
                                            c.getClients()[i].getId());
                smallest_distance_index = i;
                min_distance = graph.findVertex(c.getClients()[i].getId())->getDist();
            }
        }


        result.insert(result.end(),temp_result.begin(),temp_result.end());


        //percorrer restantes clientes
        while(c.getClients().size()!=1) {

            for (unsigned int i = 0; i < c.getClients().size(); i++) {
                if(smallest_distance_index == i)continue;

                graph.Astar(c.getClients()[smallest_distance_index].getId(),c.getTotalDeliveryRestaurants()[i].getId());

                if (graph.findVertex(c.getClients()[i].getId())->getDist() < min_distance && graph.findVertex(c.getClients()[i].getId())->getVisited()) {
                    temp_result = graph.getPath(c.getClients()[smallest_distance_index].getId(),
                                                c.getClients()[i].getId());
                    temp_distance_index = i;
                    min_distance = graph.findVertex(c.getClients()[i].getId())->getDist();
                }

            }


            if(smallest_distance_index<temp_distance_index){
                temp_distance_index--;
            }

            vector<Client> cli = c.getClients();
            cli.erase(cli.begin()+smallest_distance_index);
            c.setClients(cli);

            smallest_distance_index = temp_distance_index;
            min_distance=999999999;

            result.insert(result.end(),temp_result.begin(),temp_result.end());

        }

        for(int i=0;i<result.size();i++){
            gv.setVertexColor(result[i].getID(), "green");
        }

        for(unsigned int i=0;i<r.size();i++){
            gv.setVertexColor(r[i].getId(), "red");
        }

        for(unsigned int i=0;i<cli.size();i++){
            gv.setVertexColor(cli[i].getId(), "red");
        }

        gv.setVertexColor(result[0].getID(),"black");
        gv.setVertexLabel(result[0].getID(),"origin");

    }



    system("pause");
    return 0;
}