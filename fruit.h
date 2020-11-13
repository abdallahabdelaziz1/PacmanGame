#ifndef FRUIT_H
#define FRUIT_H
#include "collectables.h"

class fruit : public collectables {
public:
    fruit();
    int getValue(); //we will override the getValue function because we want to increment the value for each fruit eaten
    static void increaseCount(); //increases the count of eaten fruits
    void setRandSprite(); //sets a random sprite (image) for the fruit
    static void resetCount(); //resets the number of eaten fruit

private:
    static int countEaten; //a static number to keep count of eaten fruit

};



#endif // FRUIT_H
