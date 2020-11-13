#ifndef BOARD_H
#define BOARD_H
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QFile>
#include <QTextStream>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>

class board {
private:
    QGraphicsScene *gameScene; //this is the main game scene of our view, we can add multiple scenes if we want later
    int** boardData; //array to save the board.txt
    int blockDim = 20; //the length and width of each row and column in pixels (dimensions of each row and col in pixels)
    int margin = 30; //margin from the board to the view borders, it will be the same from all sides for simplicity
    int sceneDim = 31*blockDim + 2*margin; //this is the dimension of the scene, the length and width of the scene, it will be a square for simplicity
    QGraphicsPixmapItem **boardImages; //this will save the images of the board


public:
    board(QGraphicsScene * g); //constructor
    int getBoardData(int r, int c); //returns boardData at row r and column c
    int **getBoardPointer(); //returns a pointer to boardData
    ~board(); //destructor

};

#endif // BOARD_H
