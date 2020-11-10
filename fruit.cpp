#include "fruit.h"

fruit::fruit() {
    value = 100;
    //each time you eat a fruit the next fruit has 100 more points, or maybe we can make it doulbe
}

int fruit::countEaten = 0;

int fruit::getValue()
{
    return value*countEaten;
}



void fruit::setRandSprite()
{
    int rand = qrand()%2; //increase to 4
    if(rand == 0){
        sprite.load("cherry.png");
    }else if(rand == 1){
        sprite.load("orange.png");
    }else if(rand == 2){
        sprite.load("apple.png"); //apple
    }else {
        sprite.load("strawberry.png"); //strawberry
    }
    sprite = sprite.scaledToWidth(blockDim);
    sprite = sprite.scaledToHeight(blockDim);

    setPixmap(sprite);
}

void fruit::resetCount()
{
    countEaten = 0;
}




