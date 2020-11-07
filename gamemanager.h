#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <QMainWindow>
#include<QGraphicsView>
#include <QTimer>
#include "board.h"
#include "smallpellets.h"
#include "powerpellets.h"
#include "fruit.h"
#include"inky.h"
#include "pinky.h"
#include"blinky.h"
#include "lives.h"
#include "score.h"
#include "text.h"
#include "player.h"


class GameManager : public QGraphicsView
{
    Q_OBJECT
private:
    board *boardInstance;
    smallPellets smallPelletsarr[244]; //better be dynamic?
    powerPellets powerPelletsarr[4];
    fruit fruitInsatnce;
    QGraphicsScene * scene;
    Inky *InkyInstant;
    Pinky *PinkyInstant;
    Blinky * BlinkyInstant;
    player* pacman;
    int playerScore =0;
    lives* remlives;
    text* gamestate;
    score* currentscore;
    int blockDim = 20; //the length and width of each row and column in pixels (dimensions of each row and col in pixels)
    int margin = 30; //margin from the board to the view borders, it will be the same from all sides for simplicity
    int sceneDim = 31*blockDim + 2*margin; //this is the dimension of the scene, the length and width of the scene, it will be a square for simplicity
    QTimer *timer;
     QTimer *timerGhostState;
    bool started = false;
private slots:
    void keyPressEvent(QKeyEvent *event); //override()
    void advance();
    void ghostStateTimeout();
    void resetGame();
public:
    GameManager();
    ~GameManager();
};
#endif // GAMEMANAGER_H
