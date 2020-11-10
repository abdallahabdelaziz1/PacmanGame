#include "lives.h"

lives::lives(QGraphicsScene* scene, int n)
{
    shapes = new QGraphicsPixmapItem[10];
    QPixmap playerImage("pacmanR.png");
    playerImage = playerImage.scaledToWidth(blockDim);
    playerImage = playerImage.scaledToHeight(blockDim);
    icon = playerImage;
    for(int i =0; i < n-1; i++)
    {
        shapes[i].setPixmap(playerImage);
        shapes[i].setPos(margin+blockDim*i, 31*blockDim+ margin);      //, 20+i*blockdim, sceneDim = 31*blockDim
        scene->addItem(&shapes[i]);
    }
    num = n;
    savedscene = scene;
}
void lives::loselife(){
    if(num-2>=0)
        shapes[0].scene()->removeItem(&shapes[num-2]); //he tried to remove shape[0] and it doesn't exist
    num--;
}

int lives::getnumlives(){
    return num;
}

void lives::addliveWithPhoto(){

    num++;

    if(num-2 >= 0){
        shapes[num-2].setPixmap(icon);
        shapes[num-2].setPos(margin+blockDim*(num-2), 31*blockDim+ margin);
        savedscene->addItem(&shapes[num-2]);
    }

}

bool lives::Died()
{
    return num==0;

}

void lives::addliveWithoutphoto()
{
    num++;
}
