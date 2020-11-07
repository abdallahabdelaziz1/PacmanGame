
#include "gamemanager.h"

GameManager::GameManager()

{

    /*
    ui->setupUi(this);
    scene= new QGraphicsScene;
    ui->graphicsView->setScene(scene);


*/
    scene=new QGraphicsScene;
    (this)->QGraphicsView::setFixedSize(sceneDim, sceneDim);
    this->setBackgroundBrush(QBrush(Qt::black, Qt::SolidPattern));
    this->setScene(scene);
        //1-)Create the view and the scene
        //
        //this->setWindowTitle("Pacman Game");
       // this->setBackgroundBrush(QBrush(Qt::black, Qt::SolidPattern)); //this changes the background color to black
     //   this->setScene(&gameScene);


    timer=new QTimer(this);
    connect(timer, SIGNAL(timeout()),this, SLOT(advance()));

    timerGhostState=new QTimer(this);
    connect(timerGhostState, SIGNAL(timeout()),this, SLOT(ghostStateTimeout()));


    //The game manager will initialize the game
    boardInstance=new board(scene);

   // boardInstance->show(); //show the board


    //the smallpellets will be from 01 to 94 except for 31 & 36 then from 186 to 309 except for 243 & 264
    //and these positions : 95, 105, 106, 109, 110, 113, 114, 125, 126, 131, 138, 151, 158, 161, 162, 173, 174, 177, 178, 181, 182, 185
    //1-) we can get boarddata from board class and check which i,j is suitable to set pos for small pellets.
    //2-) we can set boardimages to smallpellets and set position of boardimages. we will also have to use boardData.
    //I will use the first method!

    int tempArr[] ={ 106, 109, 110, 113, 114, 125, 126, 131, 138, 151, 158, 161, 162, 173, 174, 177, 178, 181, 182, 185};

    //TO DO: should set blockDim and margin and use them instead of 20 and 20 in here
    int tempItr = 0 ;
    int tempItr2= 0;
    for(int i=0; i<31; i++){
        for(int j=0; j<28; j++){
            if( boardInstance->getBoardData(i,j) > 0 && boardInstance->getBoardData(i,j) < 106 && boardInstance->getBoardData(i,j) != 31 && boardInstance->getBoardData(i,j) != 36){
                smallPelletsarr[tempItr].setPos(20*j + 30, 20*i + 30);
                scene->addItem(&smallPelletsarr[tempItr]);
                tempItr++;
            }else if(boardInstance->getBoardData(i,j) > 185 && boardInstance->getBoardData(i,j) < 310 && boardInstance->getBoardData(i,j) != 222 && boardInstance->getBoardData(i,j) != 243){
                smallPelletsarr[tempItr].setPos(20*j + 30, 20*i + 30);
                scene->addItem(&smallPelletsarr[tempItr]);
                tempItr++;
            }else{
                for(int k=0; k<20; k++){
                    if(tempArr[k] == boardInstance->getBoardData(i,j)){
                        smallPelletsarr[tempItr].setPos(20*j + 30, 20*i + 30);
                       scene->addItem(&smallPelletsarr[tempItr]);
                        tempItr++;
                    }
                }
            }


            if(boardInstance->getBoardData(i,j) == 31 || boardInstance->getBoardData(i,j) == 36 || boardInstance->getBoardData(i,j) == 243 || boardInstance->getBoardData(i,j) == 222 ){
                powerPelletsarr[tempItr2].setPos(20*j + 30, 20*i + 30);
                scene->addItem(&powerPelletsarr[tempItr2]);
                tempItr2++;
            }

        }
    }




//adding the ghosts to the scene
    InkyInstant=new Inky(boardInstance->getBoardPointer());
    scene->addItem(InkyInstant);



    PinkyInstant=new Pinky(boardInstance->getBoardPointer());
    scene->addItem(PinkyInstant);


    BlinkyInstant=new Blinky(boardInstance->getBoardPointer());
   scene->addItem(BlinkyInstant);

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
   pacman = new player(boardInstance->getBoardPointer());
   remlives = new lives(scene);
   gamestate = new text;
   currentscore = new score;
   scene->addItem(pacman);
   scene->addItem(gamestate);
   scene->addItem(currentscore);

}


void GameManager::keyPressEvent(QKeyEvent *event)
{

    if (event->key() == Qt::Key_Space && !started)
    {
       scene->removeItem(gamestate);
       timer->start(150);
       started=true;
    }
    if(started){
    if (event->key() == Qt::Key_Up)
    {
       pacman->changedir('U');
    }
    if (event->key() == Qt::Key_Down){
        pacman->changedir('D');
    }
    if (event->key() == Qt::Key_Right){
        pacman->changedir('R');
    }
    if (event->key() == Qt::Key_Left){
        pacman->changedir('L');
    }
}
}

void GameManager::advance(){





    QList<QGraphicsItem*> collidedItems = pacman->collidingItems();
    for(int i=0; i < collidedItems.size(); i++){
        if( typeid(*collidedItems[i]) == typeid(smallPellets)){
            scene->removeItem(collidedItems[i]);
            playerScore += smallPelletsarr[0].getValue();
        }else if(typeid(*collidedItems[i]) == typeid(powerPellets)){
            scene->removeItem(collidedItems[i]);
            playerScore += powerPelletsarr[0].getValue();
            InkyInstant->changestate();
            InkyInstant->escape();
            PinkyInstant->changestate();
            PinkyInstant->escape();
            BlinkyInstant->changestate();
            BlinkyInstant->escape();
            timerGhostState->start(8000);

        }else if(typeid(*collidedItems[i]) == typeid(Inky)){
            if(InkyInstant->getAttackingState() == 0){
                //Ghost is eaten
                InkyInstant->ReturnHome();
                playerScore += 200;
            }else{
                //ghost will attack, he will lose a live, game will reset,
                remlives->loselife();
                resetGame();
            }
        }else if(typeid(*collidedItems[i]) == typeid(Pinky)){
            if(PinkyInstant->getAttackingState() == 0){
                PinkyInstant->ReturnHome();
                playerScore += 200;
            }else{
                remlives->loselife();
                resetGame();
            }
        }else if(typeid(*collidedItems[i]) == typeid(Blinky)){
            if(BlinkyInstant->getAttackingState() == 0){
                BlinkyInstant->ReturnHome();
                playerScore += 200;
            }else{
                remlives->loselife();
                resetGame();
            }
        }else if(typeid(*collidedItems[i]) == typeid(fruit)){
                scene->removeItem(collidedItems[i]);
        }
    }

    currentscore->updatescore(playerScore);

    InkyInstant->FollowPaceman();
    PinkyInstant->FollowPaceman();
    BlinkyInstant->FollowPaceman();
    pacman->move();




}

void GameManager::ghostStateTimeout(){
    if(InkyInstant->getAttackingState() != 1){
        InkyInstant->ReturnOriginalState();
    }
    if(PinkyInstant->getAttackingState() != 1){
        PinkyInstant->ReturnOriginalState();
    }
    if(BlinkyInstant->getAttackingState() != 1){
        BlinkyInstant->ReturnOriginalState();
    }

    timerGhostState->stop();
}

void GameManager::resetGame(){
    InkyInstant->ReturnHome();
    PinkyInstant->ReturnHome();
    BlinkyInstant->ReturnHome();
    pacman->reset();
}

GameManager::~GameManager()
{
}
