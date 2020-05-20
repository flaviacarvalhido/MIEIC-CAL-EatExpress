
#include "Client.h"


Client::Client() {
    this->id=0;
}

Client::Client(int id) {
    this->id=id;
}

int Client::getId() {
    return id;
}

void Client::setId(int id) {
    this->id=id;
}
