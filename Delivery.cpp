//
// Created by shit on 20/05/2020.
//

#include "Delivery.h"

Delivery::Delivery() {
    this->client = Client();
    this->restaurant = Restaurant();
}

Delivery::Delivery(Client c, Restaurant r, vector<int> i) {
    this->client = c;
    this->restaurant = r;
    this->orderedItems = i;
}

void Delivery::setClient(Client client) {
    this->client = client;
}

void Delivery::setRestaurant(Restaurant restaurant) {
    this->restaurant = restaurant;
}

void Delivery::setOrderedItems(vector<int> p) {
    this->orderedItems = p;
}

Client Delivery::getClient() {
    return client;
}

Restaurant Delivery::getRestaurant() {
    return restaurant;
}

vector<int> Delivery::getOrderedItems() {
    return orderedItems;
}

void Delivery::addItem(int space) {
    orderedItems.push_back(space);
}

void Delivery::setID(int id) {
    this->id = id;
}

int Delivery::getID() {
    return id;
}

int Delivery::calculateOccupiedSpace() {
    int result=0;
    for(unsigned int i=0;i<orderedItems.size();i++){
        result+=orderedItems[i];
    }
    return result;
}

Delivery::~Delivery() {

}


