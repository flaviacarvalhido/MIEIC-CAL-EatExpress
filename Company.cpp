//
// Created by joao on 23/05/2020.
//

#include <iostream>
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
        if (temp != "::::::::::"){
            d.setClient(Client(mstoi(temp)));
            clients.push_back(Client(mstoi(temp)));
        }
        else {
            getline(delivery_file, temp);
            d.setClient(Client(mstoi(temp)));
            clients.push_back(Client(mstoi(temp)));
        }
        getline(delivery_file, temp);
        while(temp!="..........") {

            d.addRestaurant(Restaurant(mstoi(temp)));
            totalDeliveryRestaurants.push_back(Restaurant(mstoi(temp)));
            getline(delivery_file, temp);
        }

        getline(delivery_file, temp);
        temp_temp_vec = decompose(temp, ',');

        for(unsigned int i =0;i< temp_temp_vec.size();i++){
            temp_vec.push_back(mstoi(temp_temp_vec[i]));
        }

        d.setOrderedItems(temp_vec);
        temp_vec= vector<int>();
        deliveries.push_back(d);
    }
}

void Company::readDelivererFile(string file) {
    string temp;
    ifstream deliverer_file;
    deliverer_file.open(file);
    while (!deliverer_file.eof()) {
        Deliverer d = Deliverer();
        getline(deliverer_file, temp);
        if (temp != "::::::::::") d.setID(mstoi(temp));
        else {
            getline(deliverer_file, temp);
            d.setID(mstoi(temp));
        }
        getline(deliverer_file, temp);
        d.setvMed(stof(temp));
        getline(deliverer_file, temp);
        d.setEspaco(mstoi(temp));
        getline(deliverer_file, temp);
        d.setIsFree(mstoi(temp));
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

void Company::setDeliveries(vector<Delivery> d) {
    this->deliveries=d;
}

void Company::setClients(vector<Client> c) {
    this->clients=c;
}



Deliverer Company::decideDeliverer(double distancia,int espaco) {
    Deliverer d = deliverers[0];
    for(int i =0 ;i<deliverers.size(); i++){
        if(deliverers[i].getEspaco()>=espaco){
            if(((distancia/1000)/deliverers[i].getvMed())*60<=30){
                d=deliverers[i];
                break;
            }
        }
    }
    return d;

}

vector<Restaurant> Company::getTotalDeliveryRestaurants() {
    return totalDeliveryRestaurants;
}

void Company::setTotalDeliveryRestaurants(vector<Restaurant> r) {
    this->totalDeliveryRestaurants=r;
}


