//
// Created by shit on 20/05/2020.
//

#ifndef EATEXPRESS_DELIVERER_H
#define EATEXPRESS_DELIVERER_H


class Deliverer {
private:
    int id;
    bool isFree;
    Vehicle vehicle;

public:
    Deliverer();
    Deliverer(int id, Vehicle v);
    ~Deliverer();

    void setID(int id);
    int getID();

    void setVehicle(Vehicle v);
    Vehicle getVehicle();

    void setIsFree(bool free);
    bool getIsFree();

};


#endif //EATEXPRESS_DELIVERER_H
