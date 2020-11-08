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

private:
    static int countEaten;

};



#endif // FRUIT_H
