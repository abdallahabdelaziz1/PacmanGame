#include "inky.h"


Inky::Inky(int ** temp):Ghosts(temp)
{

    sprite.load("inky.png");
    sprite=sprite.scaledToWidth(blockDim);
    sprite=sprite.scaledToHeight(blockDim);
    setPixmap(sprite);
   SETPOS(InitialRow, InitialColumn);
    //will add to the scene in gamemanager
}


void Inky::ReturnHome()
{
    ReturnOriginalState();
    SETPOS(InitialRow, InitialColumn);

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

    // you should determine where to go here and update hte shoortest path using the BFS function accordingly

}
