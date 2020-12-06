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

void Ghosts::FollowPaceman(QPair<int, int> PacmanCoordiante, int pacManDir) //make the next move
{

    Hit_Wall = false;           //resets ghosts hit wall state, when following pacman we reset hitwall
    Begin_Escape = false;       //resets escape as well.

    if(scatterPath.empty()){
        if(moveCounter==0){
            UpdateShortestPath(PacmanCoordiante, pacManDir);
            GoToCell=shortestPath.top();
        }
        moveTo(determineDirection(GoToCell));
    }else{
        if(moveCounter==0){
            GoToCell=scatterPath.top();
            scatterPath.pop();
        }
        moveTo(determineDirection(GoToCell));
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

    if(moveCounter != 0 && !Begin_Escape){
        moveTo(q);
        if(moveCounter == 0)
            Begin_Escape = true;
    }
    else{

    //Not smooth
       if(Hit_Wall){
             moveRandomly();
       }else{
           if((boardData[row-1][column] < 0 && q==1) || (boardData[row][column-1] < 0 && q==2) || (boardData[row][column+1] < 0 && q==3) || (boardData[row+1][column] < 0 && q==0)){
               //if pacman hit a wall move randomly
               Hit_Wall = true;
               moveRandomly();
           }else{
               //if it didn't hit a wall yet move opposite to the direction of the shortest path
               if(q == 0)
                   moveTo(1);
               else if(q == 1)
                   moveTo(0);
               else if(q == 2)
                   moveTo(3);
               else if(q == 3)
                   moveTo(2);
           }
       }
    }
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

QStack<QPair<int, int>> Ghosts::ShortestPathBFS(QPair<int, int> PacmanCoordiante)// returns the shortest path as stack
{

    QStack<QPair<int, int>> path;// path to be returned

    QQueue<QPair<int, int>> q;// queue to use in BFS
    q.push_back(qMakePair(row, column));


    if(PacmanCoordiante.first==row && PacmanCoordiante.second==column ){
        path.push(PacmanCoordiante);
        return path;
    }


    bool visited[TotalRows][TotalColumns];
    memset(visited, 0, sizeof(visited));//initialize visited by false

    QMap<QPair<int, int>, QPair<int, int> > prev;// map maps the child (key) to its parent (value) (we will construct the path using it)

    QPair<int, int> parent, child, inital;
    inital.first=row, inital.second=column;//intial is the source positions

    visited[row][column]=1;// making the source visited


    while(!q.empty()){
        parent= q.front();//first in the queue
        q.pop_front();
        int x=parent.first, y=parent.second;

        if(boardData[x-1][y]>0 && !visited[x-1][y]){//child above it
            visited[x-1][y]=1;
            child.first=x-1; child.second=y;
            prev[child]=parent;
            q.push_back(child);
        }
        if(boardData[x+1][y]>0 && !visited[x+1][y]){//child below it
            visited[x+1][y]=1;
            child.first=x+1; child.second=y;
            prev[child]=parent;
            q.push_back(child);
        }
        if(boardData[x][y+1]>0){//right
           if(y+1==TotalColumns-1){// y== totalCOlumn-2;  //handling portal to the righ
               y=0;
           }

           if(!visited[x][y+1]){
               visited[x][y+1]=1;
               child.first=x; child.second=y+1;
               prev[child]=parent;
               q.push_back(child);
           }
            y=parent.second;
        }
        if(boardData[x][y-1]>0){//left
            if(y==1){ //handling portal to the left
                y=TotalColumns-1;
            }
            if(!visited[x][y-1]){
                visited[x][y-1]=1;
                child.first=x; child.second=y-1;
                prev[child]=parent;
                q.push_back(child);
            }
            y=parent.second;
        }

        if(visited[PacmanCoordiante.first][PacmanCoordiante.second])//we reached the destination
            break;
    }

    //constucting the path
    QPair<int, int> current=PacmanCoordiante;
    while(current!=inital){
        path.push(current);
        current=prev[current];
    }
    return path;

    //Now the top cell in the stack is the cell that the ghost will visit in the next move (ghost first step)
    //and the bottom cell is the destiantion

}

void Ghosts::moveTo(int q) { //implemented it to move to certain direction using Abdo method in order for ghost to move smoothly
    moveCounter++;

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

int Ghosts::determineDirection(QPair<int, int> GO) //implemented it to give me the direction we should go from my current position to the cell GO
{
    if(GO.first-row == -1)
        return q = 0;//up
    if(GO.first-row==1)
        return q = 1;//down
    if(GO.second==1 && column==TotalColumns-2)
        return q = 2;//right through portal
    if(GO.second==TotalColumns-2 && column==1)
        return q = 3;//left through portal
    if(GO.second-column==1)
        return q = 2;//right
    if(GO.second-column==-1)
        return q = 3;//left

  //  return 0;

}

void Ghosts::moveRandomly()
{
    bool Valid_Direction = true;
    if((boardData[row+1][column] < 0 && q==1) || (boardData[row][column+1] < 0 && q==2) || (boardData[row][column-1] < 0 && q==3) || (boardData[row-1][column] < 0 && q==0))
        Valid_Direction = false;

    while(!Valid_Direction){
        q = qrand() % 4;
        if(q == 0){
            if(boardData[row-1][column] > 0)
                Valid_Direction = true;
        }else if(q == 1){
            if(boardData[row+1][column] > 0)
                Valid_Direction = true;
        }else if(q == 2){
            if(boardData[row][column+1] > 0)
                Valid_Direction = true;
        }else if(q == 3){
            if(boardData[row][column-1] > 0)
                Valid_Direction = true;
        }
    }
    moveTo(q);
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
