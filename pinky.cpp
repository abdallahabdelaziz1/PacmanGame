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

void Pinky::UpdateShortestPath(QPair<int, int> PacmanCoordiante)
{

     // you should determine where to go here and update hte shoortest path using the BFS function accordingly
}
