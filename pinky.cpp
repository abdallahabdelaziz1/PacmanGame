#include "pinky.h"

Pinky::Pinky(int ** temp):Ghosts(temp)
{


    sprite.load("pinky.png");
    sprite=sprite.scaledToWidth(blockDim);
    sprite=sprite.scaledToHeight(blockDim);
    setPixmap(sprite);
   SETPOS(InitialRow, InitialColumn);
}


void Pinky::ReturnHome()
{
    ReturnOriginalState();
    SETPOS(InitialRow, InitialColumn);

}

void Pinky::ReturnOriginalState()
{
     AttackingState=1;
    sprite.load("pinky.png");
    sprite=sprite.scaledToWidth(blockDim);
    sprite=sprite.scaledToHeight(blockDim);
    setPixmap(sprite);

}
