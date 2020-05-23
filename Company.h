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
using namespace std;
class Company {
private:
    vector<Client> clients;
    vector<Deliverer> deliverers;
    vector<Restaurant> restaurants;
    vector<Delivery> deliveries;
    vector<Restaurant> deliveryRestaurant;

public:
    void readRestaurantFile(string file);
    void readDeliveriesFile(string file);
    void readDelivererFile(string file);
    vector<Client> getClients();
    vector<Deliverer> getDeliverers();
    vector<Restaurant> getRestaurants();
    vector<Delivery> getDeliveries();
    vector<Restaurant> getdeliveryRestaurant();
    void erasedeliveryRestaurant(int i);
};
#endif //EATEXPRESS_COMPANY_H
