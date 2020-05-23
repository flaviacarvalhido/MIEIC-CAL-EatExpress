//
// Created by shit on 20/05/2020.
//

#include "Delivery.h"

Delivery::Delivery() {
    this->client = Client();
    this->restaurants = vector<Restaurant>();
}

Delivery::Delivery(Client c, vector<Restaurant> r, vector<int> i) {
    this->client = c;
    this->restaurants = r;
    this->orderedItems = i;
}

void Delivery::setClient(Client client) {
    this->client = client;
}

void Delivery::addRestaurant(Restaurant restaurant) {
    this->restaurants.push_back(restaurant);
}

void Delivery::setOrderedItems(vector<int> p) {
    this->orderedItems = p;
}

Client Delivery::getClient() {
    return client;
}

vector<Restaurant> Delivery::getRestaurant() {
    return restaurants;
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

void Delivery::removeRestaurant(int i) {
    restaurants.erase(restaurants.begin()+i);
}


