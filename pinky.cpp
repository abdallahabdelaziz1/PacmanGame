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




void Pinky::FollowPaceman(QPair<int, int> PacmanCoordiante, int pacManDir) { //make the next move

    Hit_Wall = false;           //resets ghosts hit wall state, when following pacman we reset hitwall
    Begin_Escape = false;       //resets escape as well.
    int ahead = 4;              //this how many steps pinky should  be ahead of pacman


    //we do a while loop, if being ahead of pacman by four steps is not possible we test out three, then two and so on...
    //at some point there must be an empty space either infront of him by a few steps or behind him by a few steps

    //Could the while loop never teriminate?? hopefully not,
    //Could we keep decreasing the number of steps till we are outside of the board? hopefully not, maybe add another coddition that is not over the board from both sides and not one side only.




    if(scatterPath.empty()){

        if(moveCounter==0){

            //here we determine the coordinate after pacman by 4 (ahead) cells and then call updateShortestPath and GoToCell and moveTo

            if(pacManDir == 0){ //UP

                while( (PacmanCoordiante.first-ahead <= 0) ||  boardData[PacmanCoordiante.first - ahead][PacmanCoordiante.second] < 0 ){
                    ahead--;
                }

                UpdateShortestPath(QPair<int,int> (PacmanCoordiante.first-ahead, PacmanCoordiante.second));

            }else if(pacManDir == 1){ //DOWN

                while( (PacmanCoordiante.first+ahead >= TotalRows-1) ||  boardData[PacmanCoordiante.first + ahead][PacmanCoordiante.second] < 0 ){
                    ahead--;
                }

                UpdateShortestPath(QPair<int,int> (PacmanCoordiante.first+ahead, PacmanCoordiante.second));

            }else if(pacManDir == 2){ //RIGHT

                //we do the portal thingy here
                if( (PacmanCoordiante.first == 14) && (PacmanCoordiante.second + ahead >= TotalColumns-1 ) ){

                    UpdateShortestPath(QPair<int,int> (14, 2 ));

                    /*if(boardData[PacmanCoordiante.first][PacmanCoordiante.second+ahead - TotalColumns + 2] < 0){
                            UpdateShortestPath(QPair<int,int> (14, 2 ));
                    }else{
                            UpdateShortestPath(QPair<int,int> (14, PacmanCoordiante.second+ahead - TotalColumns + 2 ));
                    }*/

                }else{

                    while( (PacmanCoordiante.second + ahead >= TotalColumns-1) ||  boardData[PacmanCoordiante.first][PacmanCoordiante.second+ahead] < 0 ){
                        ahead--;
                    }

                    UpdateShortestPath(QPair<int,int> (PacmanCoordiante.first, PacmanCoordiante.second+ahead));
                }


            }else if(pacManDir == 3){ //LEFT

                //portal thingy here
                if( (PacmanCoordiante.first == 14) && (PacmanCoordiante.second - ahead <= 1 ) ){
                    UpdateShortestPath(QPair<int,int> (14, TotalColumns-3 ));
                }else{
                    while( (PacmanCoordiante.second-ahead <= 0) ||  boardData[PacmanCoordiante.first][PacmanCoordiante.second-ahead] < 0 ){
                        ahead--;
                    }

                    UpdateShortestPath(QPair<int,int> (PacmanCoordiante.first, PacmanCoordiante.second-ahead));
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
