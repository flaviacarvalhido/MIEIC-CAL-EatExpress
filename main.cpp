#include <iostream>

#include <string>
#include <vector>
#include <GraphViewer/graphviewer.h>
#include "Client.h"
#include "Restaurant.h"
#include "Deliverer.h"
#include "Vehicle.h"
#include "Delivery.h"
#include "Utils.h"
#include "Point.h"
#include "Graph.h"
#include "parse.h"

using namespace std;


vector<Client> clients;
vector<Deliverer> deliverers;
vector<Restaurant> restaurants;
vector<Delivery> deliveries;
Graph<Point> graph;


void readClientFile(string file) {
    string temp;
    vector<string> temp_vector;
    ifstream client_file;
    client_file.open(file);
    while (!client_file.eof()) {
        Client c = Client();
        getline(client_file,temp);
        c.setId(mstoi(temp));
        clients.push_back(c);
    }
}

void readRestaurantFile(string file) {
    string temp;
    vector<string> temp_vector;
    ifstream restaurant_file;
    restaurant_file.open(file);
    while (!restaurant_file.eof()) {
        Restaurant r = Restaurant();
        getline(restaurant_file, temp);
        r.setId(mstoi(temp));
        restaurants.push_back(r);
    }
}


void readDeliveriesFile(string file) {
    string temp;
    vector<string> temp_vector;
    ifstream delivery_file;
    delivery_file.open(file);
    vector<string> temp_temp_vec;
    vector<int> temp_vec;
    while (!delivery_file.eof()) {
        Delivery d = Delivery();
        getline(delivery_file, temp);
        if (temp != "::::::::::") d.setClient(Client(mstoi(temp)));
        else {
            getline(delivery_file, temp);
            d.setClient(Client(mstoi(temp)));
        }
        getline(delivery_file, temp);
        d.setRestaurant(Restaurant(mstoi(temp)));
        getline(delivery_file, temp);
        temp_temp_vec = decompose(temp, ',');

        for(unsigned int i =0;i< temp_temp_vec.size();i++){
            temp_vec.push_back(mstoi(temp_temp_vec[i]));
        }
        d.setOrderedItems(temp_vec);
        deliveries.push_back(d);
    }
}

void readDelivererFile(string file) {
    string temp;
    ifstream deliverer_file;
    deliverer_file.open(file);
    while (!deliverer_file.eof()) {
        Deliverer d = Deliverer();
        Vehicle v = Vehicle();
        getline(deliverer_file, temp);
        if (temp != "::::::::::") d.setID(mstoi(temp));
        else {
            getline(deliverer_file, temp);
            d.setID(mstoi(temp));
        }
        getline(deliverer_file, temp);
        d.setIsFree(true);
        getline(deliverer_file, temp);
        if (temp == "::::::::::") continue;
        v.setMarca(temp);
        getline(deliverer_file, temp);
        if (temp == "::::::::::") continue;
        v.setvMed(mstoi(temp));
        getline(deliverer_file, temp);
        if (temp == "::::::::::") continue;
        v.setEspaco(mstoi(temp));
        getline(deliverer_file, temp);
        if (temp == "::::::::::") continue;
        v.setAno(mstoi(temp));
        d.setVehicle(v);
        deliverers.push_back(d);
    }
}

int main()
{
    cout << "Welcome to EatExpress!" << endl;
    cout << endl;





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

    readDeliveriesFile("../"+filename);
    readDelivererFile("../Deliverers.txt");
    readClientFile("../Clients.txt");
    readRestaurantFile("../Restaurants.txt");


    //VER SE ID DOS RESTAURANTES DAS DELIVERIES É UM RESTAURANTE NO RESTAURANTES TXT, se não erro
    bool found=false;
    for(unsigned int i =0; i<deliveries.size();i++){
        for(unsigned int j=0; j<restaurants.size();j++){
            if(deliveries[i].getRestaurant().getId() == restaurants[j].getId()){
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
    parsePorto();
    GraphViewer gv = GraphViewer(900,900,false);
    gv = buildGraphViewer(graph);
    for(int i=0;i<restaurants.size();i++){
        gv.setVertexColor(restaurants[i].getId(), "cyan");
    }




    //CASO BASE: UMA ENTREGA, UM RESTAURANTE, UM ESTAFETA, UM CLIENTE
    if(deliveries.size() == 1) {
        vector<Point> res;
        bool found=false;

        res=graph.bfs(deliveries[0].getRestaurant().getId());

        for(unsigned int i=0;i<res.size();i++){
            if(res[i].getID() == deliveries[0].getClient().getId()){
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

        graph.dijkstraShortestPath(deliveries[0].getRestaurant().getId()); //for now its just unidirectional dijkstra
        perfectPath = graph.getPath(deliveries[0].getRestaurant().getId(),deliveries[0].getClient().getId());
        for(int i=0;i<perfectPath.size();i++){
            gv.setVertexColor(perfectPath[i].getID(), "green");
        }
        gv.setVertexColor(perfectPath[0].getID(), "red");
        gv.setVertexColor(perfectPath[perfectPath.size()-1].getID(), "red");
    }


    system("pause");
    return 0;
}