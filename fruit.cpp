#include "fruit.h"

fruit::fruit() {
    value = 100;
}

int fruit::countEaten = 0; //this is to count the total number of fruits eaten, we will use it to calculate the value

int fruit::getValue() {
    return value*countEaten; //each time you eat a fruit the next fruit has 100 more points!
}

void fruit::increaseCount(){
    countEaten++;
}


//setting the Qpixmap image, dimensions, set the pixmap to the QgraphicsItem.
void fruit::setRandSprite()
{
    //we set the image to be a random fruit image from the four images
    int rand = qrand()%4;
    if(rand == 0){
        sprite.load("cherry.png");
    }else if(rand == 1){
        sprite.load("orange.png");
    }else if(rand == 2){
        sprite.load("apple.png");
    }else {
        sprite.load("strawberry.png");
    }


    sprite = sprite.scaledToWidth(blockDim);
    sprite = sprite.scaledToHeight(blockDim);

    setPixmap(sprite);
}


//this function is called to reset the number of fruit eaten when the player starts a new game
void fruit::resetCount()
{
    countEaten = 0;
}




