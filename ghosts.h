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
    Ghosts(int** temp);
    virtual void FollowPaceman();
    virtual void ReturnHome()=0;
    void changestate(); //changes the image of the ghost to the scared ghost
    void escape(); // make him escape from the pacman
    virtual void ReturnOriginalState()=0; //returns its original image
    bool getAttackingState();
    void SETPOS(int r, int c);//chang the position of the ghose
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
    int** boardData;
    float speed = 2; //need to be a divisor of blockDim so that rowPerSpeed is an integer.
    float rowsPerSpeed = blockDim / speed;
    int moveCounter = 0;
    int q=0;

    bool AttackingState;  //state=1: he can attack, else he can't

    static int value;//this is the value (score) player will get if he eats a ghost.
    //It will be 200 for first eaten ghose then 400 then 800.
    //it will return to 200, if player eats a new powerpellet or if all ghosts return to attacking state.

};

#endif // GHOSTS_H


/*
  //ghosts

    QPixmap rtemp("blinky.png");
      rtemp=rtemp.scaledToWidth(2*16);
      rtemp=rtemp.scaledToHeight(2*16);

      tt.setPixmap(rtemp);
      //column 11 row 13
      tt.setPos(20+16*11, 20+16*13);
      gameScene.addItem(&tt);

      QPixmap ftemp("inky.png");
      ftemp=ftemp.scaledToWidth(2*16);
      ftemp=ftemp.scaledToHeight(2*16);
      tt2.setPixmap(ftemp);
      tt2.setPos(20+16*13, 20+16*13);
      gameScene.addItem(&tt2);


      QPixmap qtemp("pinky.png");
      qtemp=qtemp.scaledToWidth(2*16);
      qtemp=qtemp.scaledToHeight(2*16);
      tt3.setPixmap(qtemp);
      tt3.setPos(20+16*15, 20+16*13);
      gameScene.addItem(&tt3);



  QGraphicsPixmapItem tt;
       QGraphicsPixmapItem tt2;
       QGraphicsPixmapItem tt3;


*/
