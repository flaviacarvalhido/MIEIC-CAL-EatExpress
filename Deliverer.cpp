//
// Created by shit on 20/05/2020.
//

#include "Deliverer.h"

Deliverer::Deliverer() {
    this->id=0;
    this->isFree=true;
    this->vehicle=Vehicle();
}

Deliverer::Deliverer(int id, Vehicle v) {
    this->id = id;
    this->vehicle=v;
}

void Deliverer::setID(int id) {
    this->id=id;
}

int Deliverer::getID() {
    return id;
}

void Deliverer::setVehicle(Vehicle v) {
    this->vehicle=v;
}

Vehicle Deliverer::getVehicle() {
    return vehicle;
}

void Deliverer::setIsFree(bool free) {
    this->isFree = free;
}

bool Deliverer::getIsFree() {
    return isFree;
}






