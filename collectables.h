#ifndef COLLECTABLES_H
#define COLLECTABLES_H
#include <QGraphicsPixmapItem>
#include <QPixmap>


class collectables : public QGraphicsPixmapItem{
protected:
    QPixmap sprite; //this will store the image "sprite" for the collectable
    int value; //value added to the score once the collectable has been collected by the player
    int blockDim = 16; //this defines the dimensions of the collectables
public:
    collectables();
    //virtual void OnCollision();
    //virtual void deleteItem();
};

#endif // COLLECTABLES_H
