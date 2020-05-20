

#ifndef EATEXPRESS_VEHICLE_H
#define EATEXPRESS_VEHICLE_H

#include <string>

using namespace std;

class Vehicle {
private:
    string marca;
    float vMed;
    float espaco;
    int ano;
public:
    Vehicle();
    Vehicle(string marca,float vMed, float espaco,int ano);
    ~Vehicle();
    void setvMed(float vMed);
    void setEspaco(float espaco);
    void setAno(int ano);
    void setMarca(string marca);
    float getvMed();
    float getEspaco();
    int getAno();
    string getMarca();
};


#endif //EATEXPRESS_VEHICLE_H
