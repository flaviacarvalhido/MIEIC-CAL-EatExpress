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
            for(unsigned int k=0; j<c.getDeliveries()[i].getRestaurant().size();k++){
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
    parsePorto();
    GraphViewer gv = GraphViewer(900,900,false);
    gv = buildGraphViewer(graph);
    for(int i=0;i<c.getRestaurants().size();i++){
        gv.setVertexColor(c.getRestaurants()[i].getId(), "cyan");
    }




    //CASO BASE: UMA ENTREGA, UM RESTAURANTE, UM ESTAFETA, UM CLIENTE
    if(c.getDeliveries().size() == 1) {
        vector<Point> res;
        bool found=false;

        res=graph.bfs(c.getDeliveries()[0].getRestaurant()[0].getId());

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


        graph.dijkstraShortestPath(c.getDeliveries()[0].getRestaurant()[0].getId()); //for now its just unidirectional dijkstra
        perfectPath = graph.getPath(c.getDeliveries()[0].getRestaurant()[0].getId(),c.getDeliveries()[0].getClient().getId());
        for(int i=0;i<perfectPath.size();i++){
            gv.setVertexColor(perfectPath[i].getID(), "green");
        }
        gv.setVertexColor(perfectPath[0].getID(), "red");
        gv.setVertexColor(perfectPath[perfectPath.size()-1].getID(), "red");

    }

    else{
        int counter=0;

        for(int i=1; i<c.getClients().size();i++){ //Checks if every delivery belongs to the same client
            if(c.getClients()[i].getId()==c.getClients()[i-1].getId()){
                counter++ ;
            }
        }
        if(counter==c.getClients().size()){
            //TODO:Algoritmo fodido, ver os caminhos ao contrario comecando no cliente indo para os restaurantes vendo sempre qual e o caminho mais pequenos entre os varios pontos

        }
    }


    system("pause");

    return 0;
}