

#ifndef EATEXPRESS_DELIVERY_H
#define EATEXPRESS_DELIVERY_H


#include <vector>
#include "Client.h"
#include "Restaurant.h"
#include "Deliverer.h"

class Delivery {
private:
    int id;
    Client client;
    vector<Restaurant> restaurants;
    vector <int> orderedItems;


public:

    Delivery();
    Delivery(Client c, vector<Restaurant> r, vector <int> i);
    ~Delivery();
    void setClient(Client client);
    void addRestaurant(Restaurant restaurant);
    void removeRestaurant(Restaurant restaurant);
    void setOrderedItems(vector<int> p);
    Client getClient();
    vector<Restaurant> getRestaurant();
    vector <int> getOrderedItems();
    void addItem(int space);
    void setID(int id);
    int getID();


    int calculateOccupiedSpace();
};


#endif //EATEXPRESS_DELIVERY_H
