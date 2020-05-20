#ifndef EATEXPRESS_RESTAURANT_H
#define EATEXPRESS_RESTAURANT_H


class Restaurant
{
private:
    int id;
public:
    Restaurant();
    Restaurant(int id);
    ~Restaurant();

    int getId();
    void setId(int i);
};


#endif //EATEXPRESS_RESTAURANT_H
