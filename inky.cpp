#include "inky.h"


Inky::Inky(int ** temp):Ghosts(temp)
{

    sprite.load("inky.png");
    sprite=sprite.scaledToWidth(blockDim);
    sprite=sprite.scaledToHeight(blockDim);
    setPixmap(sprite);
    SETPOS(InitialRow, InitialColumn);
    scatterPath = ShortestPathBFS(QPair<int, int>(TotalRows - 2, 1));
    //will add to the scene in gamemanager
}


void Inky::ReturnHome()
{
    ReturnOriginalState();
    SETPOS(InitialRow, InitialColumn);
    scatterPath = ShortestPathBFS(QPair<int, int>(TotalRows - 2, 1));

}

void Inky::ReturnOriginalState()
{
    AttackingState=1;
    sprite.load("inky.png");
    sprite=sprite.scaledToWidth(blockDim);
    sprite=sprite.scaledToHeight(blockDim);
    setPixmap(sprite);

}

void Inky::UpdateShortestPath(QPair<int, int> PacmanCoordiante)
{

    shortestPath.clear();
    shortestPath=ShortestPathBFS(PacmanCoordiante);
    moveCounter=0;

}
