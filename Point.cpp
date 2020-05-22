//
// Created by ricar on 20/05/2020.
//

#include "Point.h"

Point::Point() {
    this->id = 0;
    this->x = 0.0; this->y = 0.0;
}

Point::~Point() {

}

Point::Point(int id) {
    this->id = id;
    this->x = 0.0; this->y = 0.0;
}

void Point::setID(int id) {
    this->id = id;
}

void Point::setX(float x) {
    this->x = x;
}

void Point::setY(float y) {
    this->y = y;
}

int Point::getID() {
    return id;
}

float Point::getX() {
    return x;
}

float Point::getY() {
    return y;
}

Point::Point(int id, float x, float y) {
    this->id = id;
    this->x = x;
    this->y = y;
}

bool Point::operator==(const Point &rhs) const {
    return id == rhs.id;
}

bool Point::operator!=(const Point &rhs) const {
    return !(rhs == *this);
}

std::ostream &operator<<(std::ostream &os, const Point &point) {
    os << "id: " << point.id << " x: " << point.x << " y: " << point.y;
    return os;
}
