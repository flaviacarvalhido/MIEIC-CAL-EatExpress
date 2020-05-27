//
// Created by joao on 23/05/2020.
//

#ifndef EATEXPRESS_COMPANY_H
#define EATEXPRESS_COMPANY_H

#include <string>
#include <vector>
#include "Client.h"
#include "Restaurant.h"
#include "Deliverer.h"
#include "Utils.h"
#include "Delivery.h"
#include "Point.h"
using namespace std;
class Company {
private:
    vector<Client> clients;
    vector<Deliverer> deliverers;
    vector<Restaurant> restaurants;
    vector<Delivery> deliveries;

    vector<Restaurant> totalDeliveryRestaurants;

public:
    void readRestaurantFile(string file);
    void readDeliveriesFile(string file);
    void readDelivererFile(string file);
    vector<Client> getClients();
    vector<Deliverer> getDeliverers();
    vector<Restaurant> getRestaurants();
    vector<Delivery> getDeliveries();
    vector<Restaurant> getTotalDeliveryRestaurants();
    void setTotalDeliveryRestaurants(vector<Restaurant> r);
    void setDeliveries(vector<Delivery> d);
    void setClients(vector <Client> c);
    void setDeliverers(vector<Deliverer> d);
    Deliverer decideDeliverer(double distancia,int espaco);

};
#endif //EATEXPRESS_COMPANY_H
