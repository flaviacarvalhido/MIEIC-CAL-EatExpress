
#include "Restaurant.h"

Restaurant::Restaurant() {
    this->id=0;
}

Restaurant::Restaurant(int id) {
    this-> id = id;
}

int Restaurant::getId() {
    return id;
}

void Restaurant::setId(int i) {
    this->id = i;
}

Restaurant::~Restaurant() {

}

bool Restaurant::operator<(const Restaurant &rhs) const {
    return id < rhs.id;
}

bool Restaurant::operator>(const Restaurant &rhs) const {
    return rhs < *this;
}

bool Restaurant::operator<=(const Restaurant &rhs) const {
    return !(rhs < *this);
}

bool Restaurant::operator>=(const Restaurant &rhs) const {
    return !(*this < rhs);
}
