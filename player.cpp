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

    for(int i=0;i<TotalRows;i++){
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
    if(direct == 'U' && boardData[row-1][col]>0){
        row--;
    }
    else if (direct == 'D'&& boardData[row+1][col]>0){
        row++;
    }
    else if (direct == 'L' && (col-1==-1 || boardData[row][col-1]>0))
    {col--;
        if (col == -1)//shouldn't it be -1?? not 0
            col = TotalColumns-1;
    }
    else if (direct=='R' && (col+1==TotalColumns||boardData[row][col+1]>0))//you must add the condition R
    {
        col++;
        if (col == TotalColumns)//should be totoal columns not, total -1
            col = 0;
    }
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

void player::reset(){
    row = spawnrow;
    col = spawncol;
    setPos(blockDim*col+margin, blockDim*row+margin);
}
