//
// Created by joao on 23/05/2020.
//

#include "Company.h"


void Company::readRestaurantFile(string file) {
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


void Company::readDeliveriesFile(string file) {
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
            clients.push_back(Client(mstoi(temp)));
        }
        getline(delivery_file, temp);
        while(temp!="..........") {

            d.addRestaurant(Restaurant(mstoi(temp)));
            getline(delivery_file, temp);
        }

        getline(delivery_file, temp);
        temp_temp_vec = decompose(temp, ',');

        for(unsigned int i =0;i< temp_temp_vec.size();i++){
            temp_vec.push_back(mstoi(temp_temp_vec[i]));
        }
        d.setOrderedItems(temp_vec);
        deliveries.push_back(d);
    }
}

void Company::readDelivererFile(string file) {
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

vector<Client> Company::getClients() {
    return clients;
}

vector<Deliverer> Company::getDeliverers() {
    return deliverers;
}

vector<Restaurant> Company::getRestaurants() {
    return restaurants;
}

vector<Delivery> Company::getDeliveries() {
    return deliveries;
}
/*
void Company::decideDeliverer(Point p) {
    for(int i =0 ;i<deliverers.size(); i++){
        if(deli)
    }

}
*/

