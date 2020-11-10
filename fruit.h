#ifndef FRUIT_H
#define FRUIT_H
#include "collectables.h"

class fruit : public collectables {
public:
    fruit();
    int getValue();
    static void increaseCount(){
        countEaten++;
    }
    void setRandSprite();
    static void resetCount();

private:
    static int countEaten;

};



#endif // FRUIT_H
