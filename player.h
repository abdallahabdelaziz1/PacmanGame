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
    int row;
    int col;
    char direct;
    QString state;
    int blockDim = 20;
    int margin = 30;
public:
    player();
    int getRow();
    int getCol();
    void move();
    void changedir(char dir);
    void changestate();
};
#endif // PLAYER_H
