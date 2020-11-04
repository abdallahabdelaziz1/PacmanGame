#ifndef BOARD_H
#define BOARD_H
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QFile>
#include <QTextStream>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>

class board : public QGraphicsView
{
private:
    QGraphicsScene gameScene; //this is the main game scene of our view, we can add multiple scenes if we want later
    int boardData[31][28]; //array to save the board.txt
    int blockDim = 16; //the length and width of each row and column in pixels (dimensions of each row and col in pixels)
    int margin = 20; //margin from the board to the view borders, it will be the same from all sides for simplicity
    int sceneDim = 31*blockDim + 2*margin; //this is the dimension of the scene, the length and width of the scene, it will be a square for simplicity
    QGraphicsPixmapItem **boardImages;

public:
    board();
    int getMargin();
    int getBoardData(int r, int c);
    bool checkBlock(int r, int c);
    ~board();
 //this function returns false if there is an obstacle at row r and col c, I can't see the point now.


};

#endif // BOARD_H
