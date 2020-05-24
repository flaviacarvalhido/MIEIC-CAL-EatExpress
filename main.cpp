#include <iostream>

#include <string>
#include <vector>
#include <GraphViewer/graphviewer.h>
#include "Utils.h"
#include "Point.h"
#include "Graph.h"
#include "parse.h"
#include "Company.h"

using namespace std;



Graph<Point> graph;




int main()
{
    cout << "Welcome to EatExpress!" << endl;
    cout << endl;
    Company c;




	string filename;
	fstream file;

	cout << "Input the name of the file of deliveries you want to read (input 0 to leave): " << endl;

	getline(cin, filename);

	file.open("../"+filename);

	while (filename != "0" && !file.is_open()) {
		cout << "Invalid name. Input name again + '.txt' or input 0 to leave program" << endl;
        getline(cin, filename);
        file.open("../"+filename);
	}

	if(filename == "0") return 0;

	c.readDeliveriesFile("../"+filename);
    c.readDelivererFile("../Deliverers.txt");
    c.readRestaurantFile("../Restaurants.txt");


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
    //vector<Point> res;

    parsePorto();
    GraphViewer gv = GraphViewer(900,900,false);

    graph.bfs(c.getDeliveries()[0].getRestaurant()[0].getId());

    gv = buildGraphViewer(graph);
    for(int i=0;i<c.getRestaurants().size();i++){
        gv.setVertexColor(c.getRestaurants()[i].getId(), "cyan");
    }

    //cout<<res.size()<<endl;


    //CASO BASE: UMA ENTREGA, UM RESTAURANTE, UM ESTAFETA, UM CLIENTE
    if((c.getDeliveries().size() == 1)&&(c.getDeliveries()[0].getRestaurant().size()==1)) {



        cout<<(graph.findVertex(c.getDeliveries()[0].getClient().getId())->getVisited())<<endl;
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
    }

    else{


        //Caso 2: mesmo cliente, várias deliveries de vários restaurantes
        if(c.getClients().size()==1) {

            vector<Point> temp_result, result;

            vector<Restaurant> deliveryRestaurants = c.getDeliveries()[0].getRestaurant();

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

                result.insert(result.end(),temp_result.begin(),temp_result.end());
                vector <Restaurant> r = c.getDeliveries()[0].getRestaurant();
                r.erase(r.begin()+smallest_distance_index);
                vector<Delivery> d = c.getDeliveries();
                d[0].setRestaurant(r);
                c.setDeliveries(d);
                smallest_distance_index = smallest_restaurant_distance;

            }

            for(int i=0;i<result.size();i++){
                gv.setVertexColor(result[i].getID(), "green");
            }
            gv.setVertexColor(result[0].getID(), "red");

            for(unsigned int i = 0;i<deliveryRestaurants.size();i++){
                gv.setVertexColor(deliveryRestaurants[i].getId(), "red");
            }
        }





        //Caso 3: mesmo restaurante, vários clientes
        bool same_r=true;
        for(unsigned int i=1; i< c.getDeliveries().size();i++){
            for(unsigned int j=0; j < c.getDeliveries()[i].getRestaurant().size();j++){
                if(c.getDeliveries()[i].getRestaurant()[j].getId() != c.getDeliveries()[i-1].getRestaurant()[j].getId() || c.getDeliveries()[i].getRestaurant().size() != 1){
                    same_r = false;
                }
            }
        }

        if(c.getClients().size()!=1 && same_r){

            cout << "sou o caso 3" << endl;
            vector<Point> temp_result, result;

            vector<Client> deliveryClients = c.getClients();

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

                result.insert(result.end(),temp_result.begin(),temp_result.end());
                vector <Client> cli = c.getClients();
                cli.erase(cli.begin()+smallest_distance_index);
                c.setClients(cli);
                smallest_distance_index = smallest_client_distance;

            }

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