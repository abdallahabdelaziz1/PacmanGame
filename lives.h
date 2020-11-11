#ifndef LIVES_H
#define LIVES_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QGraphicsScene>
#include <QStack>

class lives : public QObject
{
    Q_OBJECT
private:
    const int NumOfLives = 3;
    int CurNumOfLives = NumOfLives;
    QStack<QGraphicsPixmapItem*> shapes;
    QPixmap icon;
    QGraphicsScene* savedscene;
    int blockDim = 20;
    int margin = 30;

public:
   lives(QGraphicsScene* scene);          //takes the scene as an argument and an optional number of lives (default 3)
   int getnumlives();                                //returns remaining lives
   void loselife();
   bool Died();
   void addLive();
   void resetLives();
};

#endif // LIVES_H


