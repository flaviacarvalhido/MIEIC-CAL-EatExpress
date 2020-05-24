
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

Client::~Client() {

}

bool Client::operator<(const Client &rhs) const {
    return id < rhs.id;
}

bool Client::operator>(const Client &rhs) const {
    return rhs < *this;
}

bool Client::operator<=(const Client &rhs) const {
    return !(rhs < *this);
}

bool Client::operator>=(const Client &rhs) const {
    return !(*this < rhs);
}
