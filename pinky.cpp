#include "pinky.h"

Pinky::Pinky(int ** temp):Ghosts(temp)
{


    sprite.load("pinky.png");
    sprite=sprite.scaledToWidth(blockDim);
    sprite=sprite.scaledToHeight(blockDim);
    setPixmap(sprite);
    SETPOS(InitialRow, InitialColumn);
    scatterPath = ShortestPathBFS(QPair<int, int>(1, 1));
}



void Pinky::ReturnHome()
{
    ReturnOriginalState();
    SETPOS(InitialRow, InitialColumn);
    scatterPath = ShortestPathBFS(QPair<int, int>(1, 1));

}

void Pinky::ReturnOriginalState()
{
    AttackingState=1;
    sprite.load("pinky.png");
    sprite=sprite.scaledToWidth(blockDim);
    sprite=sprite.scaledToHeight(blockDim);
    setPixmap(sprite);

}



void Pinky::UpdateShortestPath(QPair<int, int> PacmanCoordiante, int pacManDir)
{
    shortestPath.clear();
    int ahead=4;//this how many steps pinky should  be ahead of pacman

    //here we determine the coordinate after pacman by 4 (ahead) cells and then call updateShortestPath and GoToCell and moveTo



    if(pacManDir == 0){ //UP

        while( (PacmanCoordiante.first-ahead <= 0) ||  boardData[PacmanCoordiante.first - ahead][PacmanCoordiante.second] < 0 ){
            ahead--;
        }

        shortestPath=ShortestPathBFS(QPair<int,int> (PacmanCoordiante.first-ahead, PacmanCoordiante.second));

    }else if(pacManDir == 1){ //DOWN

        while( (PacmanCoordiante.first+ahead >= TotalRows-1) ||  boardData[PacmanCoordiante.first + ahead][PacmanCoordiante.second] < 0 ){
            ahead--;
        }

        shortestPath=ShortestPathBFS(QPair<int,int> (PacmanCoordiante.first+ahead, PacmanCoordiante.second));

    }else if(pacManDir == 2){ //RIGHT

        //we do the portal thingy here
        if( (PacmanCoordiante.first == 14) && (PacmanCoordiante.second + ahead >= TotalColumns-1 ) ){

            shortestPath=ShortestPathBFS(QPair<int,int> (14, 2 ));



        }else{

            while( (PacmanCoordiante.second + ahead >= TotalColumns-1) ||  boardData[PacmanCoordiante.first][PacmanCoordiante.second+ahead] < 0 ){
                ahead--;
            }

            shortestPath=ShortestPathBFS(QPair<int,int> (PacmanCoordiante.first, PacmanCoordiante.second+ahead));
        }


    }else if(pacManDir == 3){ //LEFT

        //portal thingy here
        if( (PacmanCoordiante.first == 14) && (PacmanCoordiante.second - ahead <= 1 ) ){
            shortestPath=ShortestPathBFS(QPair<int,int> (14, TotalColumns-3 ));
        }else{
            while( (PacmanCoordiante.second-ahead <= 0) ||  boardData[PacmanCoordiante.first][PacmanCoordiante.second-ahead] < 0 ){
                ahead--;
            }

            shortestPath=ShortestPathBFS(QPair<int,int> (PacmanCoordiante.first, PacmanCoordiante.second-ahead));
        }


    }



    moveCounter=0;

}




