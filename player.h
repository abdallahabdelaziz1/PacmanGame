#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QString>
#include <QKeyEvent>
#include <QList>

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
    bool invencible=false;
    int blockDim = 20;
    int margin = 30;
    QPixmap pacman;
    int** boardData;
public:
    player(int** temp);             //takes the game board as an argument
    int getRow();                   //gets pacman position
    int getCol();
    void move();                    //updates pacman position accdording to the value of direct
    void changedir(char dir);       //changes direction and image. Takes 'U', 'D', 'R' or 'L' as an argument;
    void changestate();             //changes between invencible and normal states
    bool isinvecible();             //returns true if invencible //interchangable with ghoast state (may not be needed)
    void reset();                   //returns pacman to spawn
};
#endif // PLAYER_H
