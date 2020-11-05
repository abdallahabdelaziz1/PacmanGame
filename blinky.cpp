#include "blinky.h"

Blinky::Blinky(int ** temp):Ghosts(temp)
{

    sprite.load("blinky.png");
    sprite=sprite.scaledToWidth(blockDim);
    sprite=sprite.scaledToHeight(blockDim);
    setPixmap(sprite);
   SETPOS(InitialRow, InitialColumn);
    //will add to the scene in gamemanager

}



void Blinky::ReturnHome()
{
    ReturnOriginalState();
    SETPOS(InitialRow, InitialColumn);

}

void Blinky::ReturnOriginalState()
{
     AttackingState=1;
    sprite.load("blinky.png");
    sprite=sprite.scaledToWidth(blockDim);
    sprite=sprite.scaledToHeight(blockDim);
    setPixmap(sprite);
}
