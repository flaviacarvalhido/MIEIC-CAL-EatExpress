//
// Created by ricar on 20/05/2020.
//

#ifndef EATEXPRESS_POINT_H
#define EATEXPRESS_POINT_H

#include <ostream>

using namespace std;

class Point {
private:
    int id;
    float x, y;
public:
    Point();
    ~Point();
    Point(int id);
    Point(int id, float x, float y);
    void setID(int id);
    void setX(float x);
    void setY(float y);
    int getID();
    float getX();
    float getY();

    bool operator==(const Point &rhs) const;

    bool operator!=(const Point &rhs) const;

    friend std::ostream &operator<<(std::ostream &os, const Point &point);
};


#endif //EATEXPRESS_POINT_H
