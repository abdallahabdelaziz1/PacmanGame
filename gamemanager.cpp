
#include "gamemanager.h"

GameManager::GameManager(QWidget *parent)
    : QMainWindow(parent)
{
    //The game manager will initialize the game

    boardInstance.show(); //show the board


    //the smallpellets will be from 01 to 100 except for 31 & 36 then from 197 to 330 except for 243 & 264
    //I will ignore these positions for now: 101, 104, 105, 108, 109, 120, 121, 126, 127, 136, 143, 156, 163, 172, 173, 176, 177, 188, 189, 192, 193, 196
    //1-) we can get boarddata from board class and check which i,j is suitable to set pos for small pellets.
    //2-) we can set boardimages to smallpellets and set position of boardimages. we will also have to use boardData.
    //I will use the first method!

    //TO DO: should set blockDim and margin and use them instead of 16 and 20 in here
    int tempItr = 0 ;
    int tempItr2= 0;
    for(int i=0; i<31; i++){
        for(int j=0; j<28; j++){
            if( boardInstance.getBoardData(i,j) > 0 && boardInstance.getBoardData(i,j) < 101 && boardInstance.getBoardData(i,j) != 31 && boardInstance.getBoardData(i,j) != 36){
                smallPelletsarr[tempItr].setPos(16*j + 20, 16*i + 20);
                boardInstance.scene()->addItem(&smallPelletsarr[tempItr]);
                tempItr++;
            }else if(boardInstance.getBoardData(i,j) > 196 && boardInstance.getBoardData(i,j) < 331 && boardInstance.getBoardData(i,j) != 243 && boardInstance.getBoardData(i,j) != 264){
                smallPelletsarr[tempItr].setPos(16*j + 20, 16*i + 20);
                boardInstance.scene()->addItem(&smallPelletsarr[tempItr]);
                tempItr++;
            }

            if(boardInstance.getBoardData(i,j) == 31 || boardInstance.getBoardData(i,j) == 36 || boardInstance.getBoardData(i,j) == 243 || boardInstance.getBoardData(i,j) == 264 ){
                powerPelletsarr[tempItr2].setPos(16*j + 20, 16*i + 20);
                boardInstance.scene()->addItem(&powerPelletsarr[tempItr2]);
                tempItr2++;
            }

        }
    }



//adding the ghosts to the scene
    InkyInstant=new Inky(boardInstance.getBoardPointer());
    boardInstance.scene()->addItem(InkyInstant);



    PinkyInstant=new Pinky(boardInstance.getBoardPointer());
    boardInstance.scene()->addItem(PinkyInstant);


    BlinkyInstant=new Blinky(boardInstance.getBoardPointer());
    boardInstance.scene()->addItem(BlinkyInstant);

    //testing blinky
   for(int i=0;i<200;i++){ //instead of the loop, use timer
        BlinkyInstant->FollowPaceman();
    }
   BlinkyInstant->changestate(); //if pacman eats power pellet
   for(int i=0;i<200;i++){
        BlinkyInstant->escape();//make him escape
    }
   //after certain time
   BlinkyInstant->ReturnOriginalState();//return his image
   //or if eatern go to home
   BlinkyInstant->ReturnHome();//note return home calls return original state and retrun it to home as well

}

GameManager::~GameManager()
{
}
