

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
    Restaurant restaurant;
    vector <int> orderedItems;


public:

    Delivery();
    Delivery(Client c, Restaurant r, vector <int> i);
    ~Delivery();
    void setClient(Client client);
    void setRestaurant(Restaurant restaurant);
    void setOrderedItems(vector<int> p);
    Client getClient();
    Restaurant getRestaurant();
    vector <int> getOrderedItems();
    void addItem(int space);
    void setID(int id);
    int getID();


    int calculateOccupiedSpace();
};


#endif //EATEXPRESS_DELIVERY_H
