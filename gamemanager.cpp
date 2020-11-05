
#include "gamemanager.h"

GameManager::GameManager(QWidget *parent)
    : QMainWindow(parent)
{
    //The game manager will initialize the game

    boardInstance.show(); //show the board


    //the smallpellets will be from 01 to 94 except for 31 & 36 then from 186 to 309 except for 243 & 264
    //and these positions : 95, 105, 106, 109, 110, 113, 114, 125, 126, 131, 138, 151, 158, 161, 162, 173, 174, 177, 178, 181, 182, 185
    //1-) we can get boarddata from board class and check which i,j is suitable to set pos for small pellets.
    //2-) we can set boardimages to smallpellets and set position of boardimages. we will also have to use boardData.
    //I will use the first method!

    int tempArr[] ={95, 105, 106, 109, 110, 113, 114, 125, 126, 131, 138, 151, 158, 161, 162, 173, 174, 177, 178, 181, 182, 185};

    //TO DO: should set blockDim and margin and use them instead of 20 and 20 in here
    int tempItr = 0 ;
    int tempItr2= 0;
    for(int i=0; i<31; i++){
        for(int j=0; j<28; j++){
            if( boardInstance.getBoardData(i,j) > 0 && boardInstance.getBoardData(i,j) < 95 && boardInstance.getBoardData(i,j) != 31 && boardInstance.getBoardData(i,j) != 36){
                smallPelletsarr[tempItr].setPos(20*j + 30, 20*i + 30);
                boardInstance.scene()->addItem(&smallPelletsarr[tempItr]);
                tempItr++;
            }else if(boardInstance.getBoardData(i,j) > 185 && boardInstance.getBoardData(i,j) < 310 && boardInstance.getBoardData(i,j) != 222 && boardInstance.getBoardData(i,j) != 243){
                smallPelletsarr[tempItr].setPos(20*j + 30, 20*i + 30);
                boardInstance.scene()->addItem(&smallPelletsarr[tempItr]);
                tempItr++;
            }else{
                for(int k=0; k<22; k++){
                    if(tempArr[k] == boardInstance.getBoardData(i,j)){
                        smallPelletsarr[tempItr].setPos(20*j + 30, 20*i + 30);
                        boardInstance.scene()->addItem(&smallPelletsarr[tempItr]);
                        tempItr++;
                    }
                }
            }


            if(boardInstance.getBoardData(i,j) == 31 || boardInstance.getBoardData(i,j) == 36 || boardInstance.getBoardData(i,j) == 243 || boardInstance.getBoardData(i,j) == 222 ){
                powerPelletsarr[tempItr2].setPos(20*j + 30, 20*i + 30);
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



   //adding score, remaining lives, and game state
   pacman = new player;
   remlives = new lives(boardInstance.scene());
   gamestate = new text;
   currentscore = new score;
   boardInstance.scene()->addItem(pacman);
   boardInstance.scene()->addItem(gamestate);
   boardInstance.scene()->addItem(currentscore);

}

GameManager::~GameManager()
{
}
