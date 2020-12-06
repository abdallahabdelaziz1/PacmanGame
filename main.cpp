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


    //This is how ghosts work
    //whenever the ghost starts from the home, each ghost moves to one corner of the board, in what we call Scatter Mode
    //Blinky goes to upper right corner, Pinky goes to upper left corner, and Inky goes to down left corner
    //After they reach the corner, they start chasing pacman according to the following
    //Blinky goes directly to pacman position
    //Pinky goes to the position ahead of pacman be four positions, if possible (like we are chasing pacman from ahead)
    //Inky goes to the position before of pacman be four positions, if possible (like we are chasing pacman from behind)
    //Thus, we are following him from three directions, QED


    //For the shortest path, we used BFS algorithm by using a queue
    //we first push the position of the ghost and we search throgh its avaliable neighbours as they are the nearest children to it (distance 1)
    //we then pop the first node in the queue and push its avaolable childern (distance 2)
    //we continue doing so unitl we reach the required position (we are sure we can because the graph is connected)
    //then we construct the path by going backwards from the desitination to the source by using a map that connects every child to their partent
    //we didn't use an adjacency list as every node has at most four childern, so we thought it were more convenient to use 4 if statements (Ms. Mai confirmed that)


    GameManager gameManager;
    gameManager.QGraphicsView::show();


    return a.exec();
}
