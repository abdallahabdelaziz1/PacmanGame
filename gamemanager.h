#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <QMainWindow>
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


class GameManager : public QMainWindow
{
    Q_OBJECT
private:
    board boardInstance;
    smallPellets smallPelletsarr[244]; //better be dynamic?
    powerPellets powerPelletsarr[4];
    fruit fruitInsatnce;
    Inky *InkyInstant;
    Pinky *PinkyInstant;
    Blinky * BlinkyInstant;
    player* pacman;
    lives* remlives;
    text* gamestate;
    score* currentscore;


public:
    GameManager(QWidget *parent = nullptr);
    ~GameManager();
};
#endif // GAMEMANAGER_H
