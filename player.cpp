#include "player.h"

player::player(int** temp) {
    QPixmap playerImage("pacmanR.png");
    playerImage = playerImage.scaledToWidth(blockDim);
    playerImage = playerImage.scaledToHeight(blockDim);
    pacman = playerImage;
    setPixmap(pacman);
    setPos(blockDim*col+margin, blockDim*row+margin);      //0.5blockdim*27+20, blockdim*23+20
    boardData=new int*[TotalRows];
    for(int i=0;i<TotalRows;i++){
        boardData[i]=new int[TotalColumns];
    }

    for(int i=0;i<TotalColumns;i++){
        for(int j=0;j<TotalColumns;j++){
         boardData[i][j]=temp[i][j];

        }
    }

}
int player::getRow() {
    return row;
}
int player::getCol() {
    return col;
}

void player::move()
{
    if(direct == 'U'&& boardData[row-1][col]>0)
        row--;
    else if (direct == 'D'&&boardData[row+1][col]>0)
        row++;
    else if (direct == 'L'&& boardData[row][col-1]>0)
        col--;
    else if (boardData[row][col+1]>0)
        col++;
    setPos(blockDim*col+margin, blockDim*row+margin);
}

void player::changedir(char dir){
    direct = dir;
    if (dir == 'U')
        pacman.load("pacmanU.png");
    else if (direct == 'D')
        pacman.load("pacmanD.png");
    else if (direct == 'L')
        pacman.load("pacmanL.png");
    else
        pacman.load("pacmanR.png");
    pacman = pacman.scaledToWidth(blockDim);
    pacman = pacman.scaledToHeight(blockDim);
    setPixmap(pacman);
}
void player::changestate(){
    if (invencible == true)
        invencible=false;
    else
        invencible = true;
}

bool player::isinvecible(){
    return invencible;
}
