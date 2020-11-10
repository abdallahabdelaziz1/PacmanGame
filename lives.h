#ifndef LIVES_H
#define LIVES_H

#include <QObject>
#include<QVector>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QGraphicsScene>

class lives : public QObject
{
    Q_OBJECT
private:
    int num;
    QVector<QGraphicsPixmapItem*>  shapes;
    QPixmap icon;
    QGraphicsScene* savedscene;
    int blockDim = 20;
    int margin = 30;

public:
   lives(QGraphicsScene* scene, int n = 3);          //takes the scene as an argument and an optional number of lives (default 3)
   int getnumlives();                                //returns remaining lives
   void loselife();
   void addliveWithPhoto();//should be called when score reaches 10 000
   bool Died();
   void addliveWithoutphoto();
};

#endif // LIVES_H
