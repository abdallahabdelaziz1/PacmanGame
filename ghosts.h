#ifndef GHOSTS_H
#define GHOSTS_H

#include <QObject>
#include<QGraphicsPixmapItem>
#include<QPixmap>
#include<QPair>
#include<QMap>
#include<QQueue>
#include<QStack>

#include <QDebug>

#include "board.h"

class Ghosts: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Ghosts(int** temp);//constructor takes a pointer to 2D array to fill board data
    virtual void FollowPaceman(QPair<int, int> PacmanCoordiante, int pacManDir=0); //function that determines the moves of the ghost. Now, random. Will be overrided in the next milestone
    virtual void ReturnHome()=0;  //pure virtual function that is overrided for each ghost to retur him to his original place
    void changestate(); //changes the image of the ghost to the scared ghost
    void escape(); // make him escape from the pacman
    virtual void ReturnOriginalState()=0; //returns its original image without going back to the home
    bool getAttackingState();//get wheter he is attcking or escaping
    static void SetValue();//returns the value to 200
    static void DoubleValue(); //doubles the value
    static int GetValue();//
    void moveRandomly();

protected:
    void SETPOS(int r, int c);//chang the position of the ghost
    QStack<QPair<int, int>>  ShortestPathBFS(QPair<int, int> PacmanCoordiante); //returns a stack of pairs of indices of the path from the ghost position to pacmanposition
    //the top of the stack will be the position of the ghose, and the bottom is the position of pacman.
    void moveTo(int q);
    int determineDirection(QPair<int, int> GO);
    virtual void UpdateShortestPath(QPair <int, int> PacmanCoordiante, int pacManDir=0)=0;

    QPair<int, int> GoToCell;
    QStack<QPair<int, int>>  shortestPath;
    QStack<QPair<int, int>> scatterPath;    //inky and pinky sacatter at the beginning
    const int TotalRows=31;
    const int TotalColumns=28;
    int row;
    int column;
    bool Begin_Escape = false;
    int blockDim = 20;
    int margin = 30;
    QPixmap sprite;
    int** boardData;//carries board data
    float speed = 2; //need to be a divisor of blockDim so that rowPerSpeed is an integer. used to improve smothness of the ghost moving
    float rowsPerSpeed = blockDim / speed;
    int moveCounter = 0;
    int q=0;     //represents direction
    bool AttackingState;  //state=1: he can attack, else he can't
    bool Hit_Wall = false;  //Used to detect if the escape pattern
    static int value;//this is the value (score) player will get if he eats a ghost.
    //It will be 200 for first eaten ghose then 400 then 800.
    //it will return to 200, if player eats a new powerpellet or if all ghosts return to attacking state.

};

#endif // GHOSTS_H

