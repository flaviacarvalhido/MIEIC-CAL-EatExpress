

#include "Vehicle.h"


Vehicle::Vehicle(){
    this->marca="";
    this->vMed = 0;
    this->espaco = 0;
    this->ano = 0;
}
Vehicle::Vehicle(string marca,float vMed, float espaco,int ano){
    this->marca = marca;
    this->vMed = vMed;
    this->espaco = espaco;
    this->ano = ano;
}

Vehicle::~Vehicle() {

}

void Vehicle::setMarca(string marca){
    this->marca = marca;
}

void Vehicle::setvMed(float vMed){
    this->vMed = vMed;

}
void Vehicle::setEspaco(float espaco){
    this->espaco = espaco;
}

void Vehicle::setAno(int ano){
    this->ano = ano;
}

string Vehicle::getMarca(){
    return marca;
}

float Vehicle::getvMed(){
    return vMed;
}
float Vehicle::getEspaco(){
    return espaco;
}

int Vehicle::getAno(){
    return ano;
}