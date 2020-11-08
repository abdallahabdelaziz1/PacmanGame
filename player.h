#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QString>
#include <QTimer>
#include <QList>
#include <QDebug>

class player : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
private:
    const int TotalRows=31;
    const int TotalColumns=28;
    const int spawnrow = 23;
    const int spawncol = 13;
    int row=23;
    int col=13;
    char direct = 'R';
    char tempDirect = 'R';
    bool invencible=false;
    int blockDim = 20;
    int margin = 30;
    int speed = 2; //need to be a divisor of blockDim so that rowPerSpeed is an integer.
    int Xpos = blockDim*col+margin;
    int Ypos = blockDim*row+margin;
    int tempRow;
    int tempCol;
    QPixmap pacman;
    int** boardData;
    QTimer* mouthanim;
    int frame = 0;
public:
    player(int** temp);             //takes the game board as an argument
    int getRow();                   //gets pacman position
    int getCol();
    void move();                    //updates pacman position accdording to the value of direct
    void changedir(char dir);       //changes direction and image. Takes 'U', 'D', 'R' or 'L' as an argument;
    void changestate();             //changes between invencible and normal states
    bool isinvecible();             //returns true if invencible //interchangable with ghoast state (may not be needed)
    void reset();                   //returns pacman to spawn
    void startanim();
    void endanim();
 private slots:
    void movemouth();
};
#endif // PLAYER_H
