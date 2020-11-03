#include "gamemanager.h"
#include "board.h"
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QFile>
#include <QTextStream>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //We need a view and a scene for our game, so I think we have three ways to approach this:
    //1-)create the view in main.cpp and then pass it to board class to initilaize and add a scene to it and then show the view in main
    //2-)let board be a view by letting board inhirit from QgrpahicsView and then changing the board scene in the board class and showing the board object in main.
    //3-) I forgot the third method lol
    //I will use the second method becuase I think the first is useless.
    board boardInstance;
    boardInstance.show();



/*
    //Create our player
    Player p(boardData);
    scene.addItem(&p); //we must add it to the scene to render

    //to handle event you must
    //1- create the apporpriate slot
    //2- associate the input to the suitable item, you can only focus one item to listen at one time.
    p.setFlag(QGraphicsPixmapItem::ItemIsFocusable);
    p.setFocus();
    //if you have multiple things/items that need input instead of the player
    //then I think it is better to use one general item that listens to all input and sends appropriate input to each item
    //or automatically change the focus between items or create a way for the player to change the focus.


    Food food(1,3);
    scene.addItem(&food);*/




    return a.exec();
}
