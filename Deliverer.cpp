//
// Created by shit on 20/05/2020.
//

#include "Deliverer.h"

Deliverer::Deliverer() {
    this->id=0;
    this->isFree=true;
    this->vMed=0;
    this->espaco=0;
}

Deliverer::Deliverer(int id) {
    this->id = id;

}

void Deliverer::setID(int id) {
    this->id=id;
}

int Deliverer::getID() {
    return id;
}


void Deliverer::setIsFree(bool free) {
    this->isFree = free;
}

bool Deliverer::getIsFree() {
    return isFree;
}
int Deliverer::getEspaco(){
    return espaco;
}
void Deliverer::setEspaco(int espaco){
    this->espaco=espaco;
}
float Deliverer::getvMed(){
    return vMed;
}
void Deliverer::setvMed(float vMed){
    this->vMed=vMed;
}

Deliverer::~Deliverer() {

}






