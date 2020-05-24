//
// Created by shit on 20/05/2020.
//

#ifndef EATEXPRESS_DELIVERER_H
#define EATEXPRESS_DELIVERER_H




class Deliverer {
private:
    int id;
    bool isFree;
    int espaco;
    float vMed;

public:
    Deliverer();
    Deliverer(int id);
    ~Deliverer();

    void setID(int id);
    int getID();
    int getEspaco();
    void setEspaco(int espaco);
    float getvMed();
    void setvMed(float vMed);


    void setIsFree(bool free);
    bool getIsFree();

};


#endif //EATEXPRESS_DELIVERER_H
