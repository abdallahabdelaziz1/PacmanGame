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


//determines the new ToGOcell and updates the path
void Inky::UpdateShortestPath(QPair<int, int> PacmanCoordiante, int pacManDir)
{

    shortestPath.clear();
    int ahead=4;//this is how many steps the ghost should be behind pacman.

    //here we determine the coordinate before pacman 4 cells(like as we chasing pacman from behind) and then call updateShortestPath and GoToCell and moveTo

    if(pacManDir == 0){//up

        while( (PacmanCoordiante.first+ahead >= TotalRows-1) ||  boardData[PacmanCoordiante.first + ahead][PacmanCoordiante.second] < 0 ){
            ahead--;
        }

        shortestPath=ShortestPathBFS(QPair<int,int> (PacmanCoordiante.first+ahead, PacmanCoordiante.second));


    }else if(pacManDir == 1){//down

        while( (PacmanCoordiante.first-ahead <= 0) ||  boardData[PacmanCoordiante.first - ahead][PacmanCoordiante.second] < 0 ){
            ahead--;
        }

        shortestPath=ShortestPathBFS(QPair<int,int> (PacmanCoordiante.first-ahead, PacmanCoordiante.second));

    }else if(pacManDir == 2){//right

        //we do the portal thingy here
        if( (PacmanCoordiante.first == 14) && (PacmanCoordiante.second - ahead <= 1 ) ){

            shortestPath=ShortestPathBFS(QPair<int,int> (14, TotalColumns-3 ));


        }else{
            while( (PacmanCoordiante.second-ahead <= 0) ||  boardData[PacmanCoordiante.first][PacmanCoordiante.second-ahead] < 0 ){
                ahead--;
            }

          shortestPath=ShortestPathBFS(QPair<int,int> (PacmanCoordiante.first, PacmanCoordiante.second-ahead));
        }

    }else if(pacManDir == 3){//left

       if( (PacmanCoordiante.first == 14) && (PacmanCoordiante.second + ahead >= TotalColumns-2 ) ){
            shortestPath=ShortestPathBFS(QPair<int,int> (14, 2 ));
       }else{
            while( (PacmanCoordiante.second+ahead >= TotalColumns-1) ||  boardData[PacmanCoordiante.first][PacmanCoordiante.second+ahead] < 0 ){
                ahead--;
            }

            shortestPath=ShortestPathBFS(QPair<int,int> (PacmanCoordiante.first, PacmanCoordiante.second+ahead));
        }

    }

    moveCounter=0;

}




