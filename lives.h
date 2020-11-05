#ifndef LIVES_H
#define LIVES_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QGraphicsScene>

class lives : public QObject
{
    Q_OBJECT
private:
    int num;
    QGraphicsPixmapItem* shapes;
    QPixmap icon;
    QGraphicsScene* savedscene;
    int blockDim = 16;
    int margin = 20;
public:
   lives(QGraphicsScene* scene, int n = 3);
   void loselife();
   int getnumlives();
   void addlive();
};

#endif // LIVES_H
