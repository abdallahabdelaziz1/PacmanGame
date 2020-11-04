#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <QMainWindow>
#include "board.h"
#include "smallpellets.h"
#include "powerpellets.h"
#include "fruit.h"


class GameManager : public QMainWindow
{
    Q_OBJECT
private:
    board boardInstance;
    smallPellets smallPelletsarr[228];
    powerPellets powerPelletsarr[4];
    fruit fruitInsatnce;

public:
    GameManager(QWidget *parent = nullptr);
    ~GameManager();
};
#endif // GAMEMANAGER_H
