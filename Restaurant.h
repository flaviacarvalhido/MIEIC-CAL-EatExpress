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

    bool operator<(const Restaurant &rhs) const;

    bool operator>(const Restaurant &rhs) const;

    bool operator<=(const Restaurant &rhs) const;

    bool operator>=(const Restaurant &rhs) const;
};


#endif //EATEXPRESS_RESTAURANT_H
