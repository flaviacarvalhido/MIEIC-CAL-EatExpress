
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
