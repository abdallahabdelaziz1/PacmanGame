#ifndef GHOSTS_H
#define GHOSTS_H

#include <QObject>
#include<QGraphicsPixmapItem>
#include<QPixmap>
#include "board.h"

class Ghosts: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Ghosts(int** temp);//constructor takes a pointer to 2D array to fill board data
    virtual void FollowPaceman(); //function that determines the moves of the ghost. Now, random. Will be overrided in the next milestone
    virtual void ReturnHome()=0;  //pure virtual function that is overrided for each ghost to retur him to his original place

    void changestate(); //changes the image of the ghost to the scared ghost
    void escape(); // make him escape from the pacman
    virtual void ReturnOriginalState()=0; //returns its original image without going back to the home
    bool getAttackingState();//get wheter he is attcking or escaping
    void SETPOS(int r, int c);//chang the position of the ghost
    static void SetValue();//returns the value to 200
    static void DoubleValue(); //doubles the value
    static int GetValue();//

protected:
    const int TotalRows=31;
    const int TotalColumns=28;
    int row;
    int column;

    int blockDim = 20;
    int margin = 30;
    QPixmap sprite;
    int** boardData;//carries board data
    float speed = 2; //need to be a divisor of blockDim so that rowPerSpeed is an integer. used to improve smothness of the ghost moving
    float rowsPerSpeed = blockDim / speed;
    int moveCounter = 0;
    int q=0;

    bool AttackingState;  //state=1: he can attack, else he can't

    static int value;//this is the value (score) player will get if he eats a ghost.
    //It will be 200 for first eaten ghose then 400 then 800.
    //it will return to 200, if player eats a new powerpellet or if all ghosts return to attacking state.

};

#endif // GHOSTS_H

