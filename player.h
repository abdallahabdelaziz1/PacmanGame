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
    int blockDim = 16;
    int margin = 20;
public:
    player();
    int getRow();
    int getCol();
    void move();
    void changedir(char dir);
    void changestate();
};
#endif // PLAYER_H
