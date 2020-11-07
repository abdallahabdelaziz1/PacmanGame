#include "ghosts.h"

Ghosts::Ghosts(int** temp)
{
    boardData=new int*[TotalRows];
    for(int i=0;i<TotalRows;i++){
        boardData[i]=new int[TotalColumns];
    }

    for(int i=0;i<TotalRows;i++){
        for(int j=0;j<TotalColumns;j++){
         boardData[i][j]=temp[i][j];

        }
    }

    srand(time(NULL));


    value=200;
    AttackingState=1;


}



void Ghosts::FollowPaceman()
{
//the motion here will be random, and will be overrided by algorithmic motion in child classes in the next milestone

int q=qrand()%4;
if(q==0 && boardData[row-1][column]>0){
    row--; //up
}
else if(q==1 && boardData[row+1][column]>0){
    row++;//down
}
else if(q==2  && (column+1==TotalColumns||boardData[row][column+1]>0)){
    column++;//right
    if (column == TotalColumns)//handling portal
        column = 0;
}
else if(q==3 && (column-1==-1 || boardData[row][column-1]>0)){
     column--;//left
     if(column==-1)//handling portal
         column=TotalColumns-1;
}


SETPOS(row, column);

}

void Ghosts::changestate()
{
    AttackingState=0;//he can't attack now
    sprite.load("ScaredGhost.png");
    sprite=sprite.scaledToWidth(blockDim);
    sprite=sprite.scaledToHeight(blockDim);
    setPixmap(sprite);
}

void Ghosts::escape()
{
    //now it will just move randomly, so we simply coall follow pacman
    FollowPaceman();
    //however it will have an algorithmim in the upcoming milestones
}


bool Ghosts::getAttackingState()
{
    return AttackingState;
}

void Ghosts::SETPOS(int r, int c)
{
    row=r;
    column=c;
    setPos(margin+ column*blockDim, margin+row*blockDim);
}
