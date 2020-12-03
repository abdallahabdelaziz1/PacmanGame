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



void Pinky::UpdateShortestPath(QPair<int, int> PacmanCoordiante)
{
    shortestPath.clear();
    shortestPath=ShortestPathBFS(PacmanCoordiante);
    moveCounter=0;

}








/* if(moveCounter == 0){
            if(pacmandir == 0){
                if(PacmanCoordiante.first - 4 <= 0 || boardData[PacmanCoordiante.first - 4][PacmanCoordiante.second] < 0){
                    if(PacmanCoordiante.second + 4 <= TotalColumns || boardData[PacmanCoordiante.first][PacmanCoordiante.second + 4]< 0){
                        UpdateShortestPath(PacmanCoordiante);
                    }else{
                        UpdateShortestPath(QPair<int,int> (PacmanCoordiante.first, PacmanCoordiante.second + 4));
                    }
                }else{
                    UpdateShortestPath(QPair<int,int> (PacmanCoordiante.first - 4, PacmanCoordiante.second));
                }
            }
            if(pacmandir == 1){
                if(PacmanCoordiante.first + 4 >= TotalRows || boardData[PacmanCoordiante.first + 4][PacmanCoordiante.second] < 0){
                    if(PacmanCoordiante.second - 4 <= 0 || boardData[PacmanCoordiante.first][PacmanCoordiante.second - 4] < 0){
                        UpdateShortestPath(PacmanCoordiante);
                    }else{
                        UpdateShortestPath(QPair<int,int> (PacmanCoordiante.first, PacmanCoordiante.second - 4));
                    }
                }else{
                    UpdateShortestPath(QPair<int,int> (PacmanCoordiante.first + 4, PacmanCoordiante.second));
                }
            }
            if(pacmandir == 2){
                if(PacmanCoordiante.first == 14 && PacmanCoordiante.second >= TotalColumns - 7 ){
                    UpdateShortestPath(QPair<int,int> (14, 2));
                }
                else if(PacmanCoordiante.second + 4 >= TotalColumns || boardData[PacmanCoordiante.first][PacmanCoordiante.second + 4] < 0){
                    if(PacmanCoordiante.first + 4 >= TotalRows || boardData[PacmanCoordiante.first + 4][PacmanCoordiante.second]< 0){
                        UpdateShortestPath(PacmanCoordiante);
                    }else{
                        UpdateShortestPath(QPair<int,int> (PacmanCoordiante.first  + 4, PacmanCoordiante.second));
                    }
                }else{
                    UpdateShortestPath(QPair<int,int> (PacmanCoordiante.first, PacmanCoordiante.second + 4));
                }
            }
            if(pacmandir == 3){
                if(PacmanCoordiante.first == 14 && PacmanCoordiante.second < 6){
                    UpdateShortestPath(QPair<int,int> (14, TotalColumns - 3));
                }
                else if(PacmanCoordiante.second - 4 <= 0 || boardData[PacmanCoordiante.first][PacmanCoordiante.second - 4] < 0){
                    if(PacmanCoordiante.first - 4 <= 0 || boardData[PacmanCoordiante.first - 4][PacmanCoordiante.second]< 0){
                        UpdateShortestPath(PacmanCoordiante);
                    }else{
                        UpdateShortestPath(QPair<int,int> (PacmanCoordiante.first - 4, PacmanCoordiante.second));
                    }
                }else{
                    UpdateShortestPath(QPair<int,int> (PacmanCoordiante.first, PacmanCoordiante.second - 4));
                }
            }
                GoToCell=shortestPath.top();
            }
        moveTo(determineDirection(GoToCell));
*/
