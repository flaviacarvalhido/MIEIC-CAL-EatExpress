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
            if(c.getDeliveries()[i].getRestaurant().getId() == c.getRestaurants()[j].getId()){
                found =true;
                break;
            }
        }
        if(!found){
            cout << "One of the deliveries doesn't have a restaurant as its origin. Please check the ID of the restaurant." << endl;
            return -1;
        }
    }


    //LER GRAFOS
    //iniciar GRAPHVIEWER
    vector<Point> res;

    parsePorto();
    GraphViewer gv = GraphViewer(900,900,false);

    res=graph.bfs(c.getDeliveries()[0].getRestaurant().getId());

    gv = buildGraphViewer(graph);
    for(int i=0;i<c.getRestaurants().size();i++){
        gv.setVertexColor(c.getRestaurants()[i].getId(), "cyan");
    }




    //CASO BASE: UMA ENTREGA, UM RESTAURANTE, UM ESTAFETA, UM CLIENTE
    if(c.getDeliveries().size() == 1) {

        bool found=false;

        for(unsigned int i=0;i<res.size();i++){
            if(res[i].getID() == c.getDeliveries()[0].getClient().getId()){
                found=true;
                break;
            }
        }
        if(!found){
            cout << "Client address is not reacheable from restaurant. Delivery cannot be made" << endl;
            return -2;
        }

        cout << "Calculating route, please wait..." << endl;

        //TODO:bidirectional dijkstra
        vector<Point> perfectPath;

        graph.dijkstraShortestPath(c.getDeliveries()[0].getRestaurant().getId()); //for now its just unidirectional dijkstra
        perfectPath = graph.getPath(c.getDeliveries()[0].getRestaurant().getId(),c.getDeliveries()[0].getClient().getId());
        for(int i=0;i<perfectPath.size();i++){
            gv.setVertexColor(perfectPath[i].getID(), "green");
        }
        gv.setVertexColor(perfectPath[0].getID(), "red");
        gv.setVertexColor(perfectPath[perfectPath.size()-1].getID(), "red");
    }

    else{
        int counter=1;

        for(int i=1; i<c.getClients().size();i++){ //Checks if every delivery belongs to the same client
            if(c.getClients()[i].getId()==c.getClients()[i-1].getId()){
                counter++ ;
            }
        }

        //Caso 2: mesmo cliente, várias deliveries de vários restaurantes

        if(counter==c.getClients().size()) {

            vector<Point> temp_result, result;
            int min_distance = 999999999;
            int smallest_distance_index = 0;

            for (int i = 0; i < c.getdeliveryRestaurant().size(); i++) {
                graph.Astar(c.getClients()[0].getId(), c.getdeliveryRestaurant()[i].getId());           //segmentation fault when running second time, check if we can run algorithm more than once and if not whats the origin and the destination to calculate every closest path

                if ((Vertex<Point>(c.getdeliveryRestaurant()[i].getId())).getDist() < min_distance) {
                    temp_result = graph.getPath(c.getClients()[0].getId(), c.getdeliveryRestaurant()[i].getId());
                    smallest_distance_index = i;
                }
            }

            result = temp_result;       //caminho mais rápido da casa do cliente ao primeiro restaurante



            min_distance = 999999999;   //reset min_distance

            int smallest_restaurant_distance = 0;
            //percorrer restantes restaurantes e ver caminho mais rápido entre cada um deles; adicionar ao resultado final até terem sido visitados todos os restaurantes
            while (!c.getdeliveryRestaurant().empty()){

                min_distance = 999999999;

                for (int i = 0; i < c.getdeliveryRestaurant().size(); i++) {
                    if(i==smallest_distance_index) continue;

                    graph.Astar(c.getdeliveryRestaurant()[smallest_distance_index].getId(), c.getdeliveryRestaurant()[i].getId());

                    if ((Vertex<Point>(c.getdeliveryRestaurant()[i].getId())).getDist() < min_distance) {
                        temp_result = graph.getPath(c.getdeliveryRestaurant()[smallest_distance_index].getId(), c.getdeliveryRestaurant()[i].getId());
                        smallest_restaurant_distance = i;
                    }
                }

                result.insert(result.end(),temp_result.begin(),temp_result.end());
                c.erasedeliveryRestaurant(smallest_distance_index);
                smallest_distance_index = smallest_restaurant_distance;

            }

            for(int i=0;i<result.size();i++){
                gv.setVertexColor(result[i].getID(), "green");
            }
            gv.setVertexColor(result[0].getID(), "red");
            gv.setVertexColor(result[result.size()-1].getID(), "red");
        }
    }


    system("pause");
    return 0;
}