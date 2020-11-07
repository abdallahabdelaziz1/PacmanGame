#include "board.h"

board::board(QGraphicsScene * g)
{

    gameScene=g;


    //2) allocating memory to board data
    boardData=new int*[31];
    for(int i=0;i<31;i++){
        boardData[i]=new int[28];
    }

    //3-) We will create our board from a text file

    //Read board data from txt file and assign it to boardData array
    QFile file("board.txt");
    file.open(QIODevice::ReadOnly);
    QString temp;
    QTextStream stream(&file);
    for(int i=0; i<31; i++){
        for(int j=0; j<28; j++){
            stream >> temp;
            boardData[i][j] = temp.toInt();
        }
    }




    //Draw board graphics
    QPixmap edgeImageH("edgeH.png");
    edgeImageH = edgeImageH.scaledToWidth(blockDim);
    edgeImageH = edgeImageH.scaledToHeight(blockDim);
    QPixmap edgeImageV("edgeV.png");
    edgeImageV = edgeImageV.scaledToWidth(blockDim);
    edgeImageV = edgeImageV.scaledToHeight(blockDim);
    QPixmap cornerImageTL("cornerTL.png");
    cornerImageTL = cornerImageTL.scaledToWidth(blockDim);
    cornerImageTL = cornerImageTL.scaledToHeight(blockDim);
    QPixmap cornerImageTR("cornerTR.png");
    cornerImageTR = cornerImageTR.scaledToWidth(blockDim);
    cornerImageTR = cornerImageTR.scaledToHeight(blockDim);
    QPixmap cornerImageBR("cornerBR.png");
    cornerImageBR = cornerImageBR.scaledToWidth(blockDim);
    cornerImageBR = cornerImageBR.scaledToHeight(blockDim);
    QPixmap cornerImageBL("cornerBL.png");
    cornerImageBL = cornerImageBL.scaledToWidth(blockDim);
    cornerImageBL = cornerImageBL.scaledToHeight(blockDim);



    //FOR SOME F***** STUPID REASON THE QGRAPHICSPIXMAPITEM HAVE TO BE IN THE HEAP!!!!!! AND DON"T DELETE THEM, WTF QT???
    //since we will use board images once it is better anyway to save them in heap, however deleting them makes them disappear so I am not entirely sure of this method or why does this happen.
    //so it will be better to create a member array board images and delete it in the destructor
    boardImages = new QGraphicsPixmapItem*[31]; //we need a pixmapitem for each image, we need to decide two things, position and image it holds
    for(int i=0; i<31; i++){
        boardImages[i] = new QGraphicsPixmapItem[28];
    }

    for (int i=0; i<31;i++){
        for(int j=0;j<28;j++){

            if(boardData[i][j] == -1){
                //vertical edge image
                boardImages[i][j].setPixmap(edgeImageV);
            }else if (boardData[i][j] == -2){
                //horizontal edge image
                boardImages[i][j].setPixmap(edgeImageH);
            }else if(boardData[i][j] == -3){
                boardImages[i][j].setPixmap(cornerImageTL);
            }else if(boardData[i][j] == -4){
                boardImages[i][j].setPixmap(cornerImageTR);
            }else if(boardData[i][j] == -5){
                boardImages[i][j].setPixmap(cornerImageBR);
            }else if(boardData[i][j] == -6){
                boardImages[i][j].setPixmap(cornerImageBL);
            }

            //positioning the images using simple relations.
            boardImages[i][j].setPos(blockDim*j + margin, blockDim*i + margin);

            //we must render our items, add the images to the scene
            gameScene->addItem(&boardImages[i][j]);
        }
    }





}


int board::getMargin(){
    return margin;
}

bool board::checkBlock(int r, int c){
    if(boardData[r][c] < 0)
    return false;

    return true;
}

int **board::getBoardPointer()
{
    return boardData;
}

int board::getBoardData(int r, int c){
    return boardData[r][c];
}

board::~board(){
    for(int i=0; i<31 ; i++){
        delete [] boardImages[i];
    }
    delete [] boardImages;
}
