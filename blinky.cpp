#include "blinky.h"

Blinky::Blinky(int ** temp):Ghosts(temp)
{

    sprite.load("blinky.png");
    sprite=sprite.scaledToWidth(blockDim);
    sprite=sprite.scaledToHeight(blockDim);
    setPixmap(sprite);
    SETPOS(InitialRow, InitialColumn);
    scatterPath = ShortestPathBFS(QPair<int, int>(1, TotalColumns-2));
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
    scatterPath = ShortestPathBFS(QPair<int, int>(1, TotalColumns-2));

}

void Blinky::ReturnOriginalState()
{
    AttackingState=1;
    sprite.load("blinky.png");
    sprite=sprite.scaledToWidth(blockDim);
    sprite=sprite.scaledToHeight(blockDim);
    setPixmap(sprite);
}
