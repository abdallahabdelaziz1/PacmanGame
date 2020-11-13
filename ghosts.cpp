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



    AttackingState=1;


}
//initializing the value
int Ghosts::value=200;

void Ghosts::FollowPaceman()
{
//the motion here will be random, and will be overrided by algorithmic motion in child classes in the next milestone

    moveCounter++;
    if(moveCounter == 1){
        q=qrand()%4;//at the beginning of the movement to a new block, radonmly select a direction
        //0 : up, 1: won, 2: right, 3: left
    }

    if(q==0 && boardData[row-1][column]>0){

        if(moveCounter > rowsPerSpeed){
            moveCounter = 0;//retrun movecounter to 0 when we finish the whole block
            row--;//up
        }
        setPos( (blockDim*column+margin) , (blockDim*row+margin) - speed*moveCounter );

    }
    else if(q==1 && boardData[row+1][column]>0){

        if(moveCounter > rowsPerSpeed){
            moveCounter = 0;
            row++;//down
        }
        setPos( (blockDim*column+margin) , (blockDim*row+margin) + speed*moveCounter );

    }
    else if(q==2  && (column+1==TotalColumns||boardData[row][column+1]>0)){

        if(moveCounter > rowsPerSpeed){
            moveCounter = 0;
            column++;//right
            if (column == TotalColumns-1)//handling portal
                column = 1;
        }
        setPos( (blockDim*column+margin) + speed*moveCounter, (blockDim*row+margin)  );

    }
    else if(q==3 && (column-1==-1 || boardData[row][column-1]>0)){

        if(moveCounter > rowsPerSpeed){
            moveCounter = 0;
            column--;//left
            if(column==0)//handling portal
                column=TotalColumns-2;
        }
        setPos( (blockDim*column+margin) - speed*moveCounter, (blockDim*row+margin)  );

    }else{
        moveCounter=0;
    }
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
    //however it will have an algorithm in the upcoming milestones
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

void Ghosts::SetValue()
{
    value=200;
}
void Ghosts::DoubleValue(){
    value*=2;
}

int Ghosts::GetValue()
{
    return value;
}
