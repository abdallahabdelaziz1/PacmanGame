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


void Inky::FollowPaceman(QPair<int, int> PacmanCoordiante, int pacManDir) { //make the next move

    Hit_Wall = false;           //resets ghosts hit wall state, when following pacman we reset hitwall
    Begin_Escape = false;       //resets escape as well.
    int ahead = 4;              //this is how many steps the ghost should be behind pacman.


    //we do a while loop, if being ahead of pacman by four steps is not possible we test out three, then two and so on...
    //at some point there must be an empty space either infront of him by a few steps or behind him by a few steps

    //Could the while loop never teriminate?? hopefully not,
    //Could we keep decreasing the number of steps till we are outside of the board? hopefully not, maybe add another coddition that is not over the board


    if(scatterPath.empty()){

        if(moveCounter==0){

            //here we determine the coordinate after pacman 4 cells and then call updateShortestPath and GoToCell and moveTo

            if(pacManDir == 0){

                while( (PacmanCoordiante.first+ahead >= TotalRows-1) ||  boardData[PacmanCoordiante.first + ahead][PacmanCoordiante.second] < 0 ){
                    ahead--;
                }

                UpdateShortestPath(QPair<int,int> (PacmanCoordiante.first+ahead, PacmanCoordiante.second));


            }else if(pacManDir == 1){

                while( (PacmanCoordiante.first-ahead <= 0) ||  boardData[PacmanCoordiante.first - ahead][PacmanCoordiante.second] < 0 ){
                    ahead--;
                }

                UpdateShortestPath(QPair<int,int> (PacmanCoordiante.first-ahead, PacmanCoordiante.second));

            }else if(pacManDir == 2){

                //we do the portal thingy here
                if( (PacmanCoordiante.first == 14) && (PacmanCoordiante.second - ahead <= 1 ) ){


                    UpdateShortestPath(QPair<int,int> (14, TotalColumns-3 ));
                    /*if(boardData[PacmanCoordiante.first][PacmanCoordiante.second+ahead - TotalColumns + 2] < 0){
                            UpdateShortestPath(QPair<int,int> (14, 2 ));
                    }else{
                            UpdateShortestPath(QPair<int,int> (14, PacmanCoordiante.second+ahead - TotalColumns + 2 ));
                    }*/ //or maybe check manual coordinates if 14, 137 we move ghost to 14,2

                    //(PacmanCoordiante.second + ahead >= TotalColumns-1)


                }else{
                    while( (PacmanCoordiante.second-ahead <= 0) ||  boardData[PacmanCoordiante.first][PacmanCoordiante.second-ahead] < 0 ){
                        ahead--;
                    }

                  UpdateShortestPath(QPair<int,int> (PacmanCoordiante.first, PacmanCoordiante.second-ahead));
                }

            }else if(pacManDir == 3){

               if( (PacmanCoordiante.first == 14) && (PacmanCoordiante.second + ahead >= TotalColumns-2 ) ){
                    UpdateShortestPath(QPair<int,int> (14, 2 ));
               }else{
                    while( (PacmanCoordiante.second+ahead >= TotalColumns-1) ||  boardData[PacmanCoordiante.first][PacmanCoordiante.second+ahead] < 0 ){
                        ahead--;
                    }

                    UpdateShortestPath(QPair<int,int> (PacmanCoordiante.first, PacmanCoordiante.second+ahead));
                }

            }


            GoToCell=shortestPath.top();
        }

        moveTo(determineDirection(GoToCell));

    }else{

        //keep following the scatter path
        if(moveCounter==0){
            GoToCell=scatterPath.top();
            scatterPath.pop();
        }
        moveTo(determineDirection(GoToCell));

    }


}


