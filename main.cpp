#include "gamemanager.h"
#include "board.h"
#include "smallpellets.h"
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>

//group members
//900196010	Amer Elsheikh
//900196083	Abdallah Taha
//900192706	Abdelrahman Abdelmonem

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //creating gameManager instance and showing it
    GameManager gameManager;
    gameManager.QGraphicsView::show();


    return a.exec();
}
