

#ifndef EATEXPRESS_CLIENT_H
#define EATEXPRESS_CLIENT_H


#pragma once

#include <string>
#include <fstream>


using namespace std;

class Client
{
private:
    int id;

public:
    Client();
    ~Client();
    Client(int id);
    int getId();
    void setId(int id);
};


#endif //EATEXPRESS_CLIENT_H
