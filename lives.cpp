#include "lives.h"

lives::lives(QGraphicsScene* scene)
{
    QPixmap playerImage("pacmanR.png");
    playerImage = playerImage.scaledToWidth(blockDim);
    playerImage = playerImage.scaledToHeight(blockDim);
    icon = playerImage;
    for(int i =0; i < NumOfLives-1; i++)
    {
        shapes.push_back(new QGraphicsPixmapItem);
        shapes.top()->setPixmap(playerImage);
        shapes.top()->setPos(margin+blockDim*i, 31*blockDim+ margin);      //, 20+i*blockdim, sceneDim = 31*blockDim
        scene->addItem(shapes.top());
    }
    savedscene = scene;
}

void lives::loselife(){
    if(CurNumOfLives>1){
      savedscene->removeItem(shapes.top());
      shapes.pop();
      }
    CurNumOfLives--;
}

int lives::getnumlives(){
    return CurNumOfLives;
}


//adds a live on the screen
void lives::addLive(){
    //if the function is called after reset it will not add the image of the first live
    if(CurNumOfLives != 0){
    CurNumOfLives++;
        if(CurNumOfLives-1 >= 0){
            shapes.push_back(new QGraphicsPixmapItem);
            shapes.top()->setPixmap(icon);
            shapes.top()->setPos(margin+blockDim*(CurNumOfLives-2), 31*blockDim+ margin);      //, 20+i*blockdim, sceneDim = 31*blockDim
            savedscene->addItem(shapes.top());
        }
    }
    else
        CurNumOfLives++;
}

void lives::resetLives()
{
    for(int i = 0; i < NumOfLives; i++)
        addLive();
}


bool lives::Died()
{
    return CurNumOfLives==0;

}

