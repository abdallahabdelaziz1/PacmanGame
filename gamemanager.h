#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <QMainWindow>

class GameManager : public QMainWindow
{
    Q_OBJECT

public:
    GameManager(QWidget *parent = nullptr);
    ~GameManager();
};
#endif // GAMEMANAGER_H
