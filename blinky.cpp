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

void Blinky::UpdateShortestPath(QPair<int, int> PacmanCoordiante)
{
    shortestPath.clear();
    shortestPath=ShortestPathBFS(PacmanCoordiante);
    moveCounter=0;

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
