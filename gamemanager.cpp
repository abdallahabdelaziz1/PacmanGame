
#include "gamemanager.h"

GameManager::GameManager()

{

    //creating the scene
    scene=new QGraphicsScene;
    (this)->QGraphicsView::setFixedSize(sceneDim, sceneDim);
    this->setBackgroundBrush(QBrush(Qt::black, Qt::SolidPattern));
    this->setScene(scene);


    srand(time(NULL)); //for random values

    //intializing timers
    timer=new QTimer(this);
    connect(timer, SIGNAL(timeout()),this, SLOT(advance()));

    timerGhostState=new QTimer(this);
    connect(timerGhostState, SIGNAL(timeout()),this, SLOT(ghostStateTimeout()));

    timerFruit=new QTimer(this);
    connect(timerFruit, SIGNAL(timeout()),this, SLOT(createFruit()));

    delay = new QTimer(this);
    connect(delay, SIGNAL(timeout()), this, SLOT(delayStart()));
    delay->setSingleShot(true);


    //The game manager will initialize the game
    boardInstance=new board(scene);


    //put the pellets on the scene
    fillPellets();

    //adding the ghosts to the scene
    InkyInstant=new Inky(boardInstance->getBoardPointer());
    scene->addItem(InkyInstant);

    PinkyInstant=new Pinky(boardInstance->getBoardPointer());
    scene->addItem(PinkyInstant);

    BlinkyInstant=new Blinky(boardInstance->getBoardPointer());
    scene->addItem(BlinkyInstant);

    //adding player, score, remaining lives, and pacman state!
    pacman = new player(boardInstance->getBoardPointer());
    remlives = new lives(scene);
    gamestate = new text;
    currentscore = new score;
    pacstate = new state;

    scene->addItem(pacstate);
    scene->addItem(pacman);
    scene->addItem(gamestate);
    scene->addItem(currentscore);


    //creating sound and music object
    musicManager = new Sounds;

}



//Handling input
void GameManager::keyPressEvent(QKeyEvent *event) {

    //starting the game
    if (event->key() == Qt::Key_Space && !started){
       started=true;
       StartAgain();
    }

    //if the player is dead
    if(remlives->Died()){

        //if Y then we will start again, if N then we will close the view.
        if(event->key()==Qt::Key_Y){
           StartAgain();
           playerScore=0;
           tenkcount=1;
           currentscore->updatescore(0);
           remlives->resetLives();
           fruit::resetCount();
        }else if(event->key()==Qt::Key_N){
            this->close();
        }

    }else if(UneatenPellets==0){ //if the player wins

        //if Y then continue with same score and lives, if N then close view.
        if(event->key()==Qt::Key_Y){
           StartAgain();
        }else if(event->key()==Qt::Key_N){
            this->close();
        }

    }else if(started){ //handling directions input
        if (event->key() == Qt::Key_Up){
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

    //adding a life everytime the player gains 10,000 points
    if(playerScore/10000==tenkcount){
        remlives->addLive();
        tenkcount++;
    }

    //handling collisions
    QList<QGraphicsItem*> collidedItems = pacman->collidingItems();
    for(int i=0; i < collidedItems.size(); i++){

        if( typeid(*collidedItems[i]) == typeid(smallPellets)){

            scene->removeItem(collidedItems[i]);
            playerScore += smallPelletsarr[0].getValue();
            UneatenPellets--;

        }else if(typeid(*collidedItems[i]) == typeid(powerPellets)){

            scene->removeItem(collidedItems[i]);
            UneatenPellets--;
            Ghosts::SetValue();//resets value to 200
            pacstate->invenciblestate();
            playerScore += powerPelletsarr[0].getValue();
            InkyInstant->changestate();
            InkyInstant->escape();
            PinkyInstant->changestate();
            PinkyInstant->escape();
            BlinkyInstant->changestate();
            BlinkyInstant->escape();
            timerGhostState->start(9000);

        }else if(typeid(*collidedItems[i]) == typeid(Inky)){

            if(InkyInstant->getAttackingState() == 0){
                //Ghost is eaten
                InkyInstant->ReturnHome();
                playerScore += Ghosts::GetValue();
                Ghosts::DoubleValue();
            }else{
                //ghost will attack, he will lose a live, game will reset,
                remlives->loselife();
                resetGame(0);

            }


        }else if(typeid(*collidedItems[i]) == typeid(Pinky)){

            if(PinkyInstant->getAttackingState() == 0){
                PinkyInstant->ReturnHome();
                playerScore += Ghosts::GetValue();
                 Ghosts::DoubleValue();
            }else{
                remlives->loselife();
                resetGame(0);

            }


        }else if(typeid(*collidedItems[i]) == typeid(Blinky)){

            if(BlinkyInstant->getAttackingState() == 0){
                BlinkyInstant->ReturnHome();
                playerScore += Ghosts::GetValue();
                 Ghosts::DoubleValue();
            }else{
                remlives->loselife();
                resetGame(0);
            }


        }else if(typeid(*collidedItems[i]) == typeid(fruit)){
                scene->removeItem(collidedItems[i]);
                fruit::increaseCount();
                playerScore += fruitInstance.getValue();
                int tempT = (qrand()%5) + 14;
                timerFruit->start(1000*tempT);
        }
    }


    //update score text
    currentscore->updatescore(playerScore);

    //checks if the player won or lost every time advanced is called, it will display information win/los text only
    if(remlives->Died()){
        musicManager->playLose();
        gamestate->lost();
        scene->addItem(gamestate);
        timer->stop();
        timerFruit->stop();
        pacman->endanim();
        scene->removeItem(&fruitInstance); //if the fruit hasn't been added it doesn't crash thankfullly.
    }else if(UneatenPellets==0){
        musicManager->playWin();
        gamestate->won();
        scene->addItem(gamestate);
        timer->stop();
        timerFruit->stop();
        pacman->endanim();
        resetGame(1);
        scene->removeItem(&fruitInstance);
    }else{
        InkyInstant->FollowPaceman();
        PinkyInstant->FollowPaceman();
        BlinkyInstant->FollowPaceman();
        pacman->move();
    }

}


//this timer runs out, it resest ghost state to original state.
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

    Ghosts::SetValue(); //resets ghost value after timer of power pellet timer runs out
    pacstate->normalstate(); //returns pacman state to original, used for text
    timerGhostState->stop(); //stops powerpellet timer.
}


//this function is called when pacman is eaten! returning the ghosts and pacman to thier original state
void GameManager::resetGame(bool win){
    Ghosts::SetValue();
    InkyInstant->ReturnHome();
    PinkyInstant->ReturnHome();
    BlinkyInstant->ReturnHome();
    pacman->reset();
    pacstate->normalstate();

    if(!win){
        timer->stop();
        pacman->endanim();
        delay->start(500);
    }

}


//adds and sets the position of the pellets to the scene
void GameManager::fillPellets() {

    UneatenPellets=248;
    //power pellets will be in position 31, 36, 243, 222
    //the smallpellets will be added from 01 to 106 except for 31 & 36 then from 186 to 309 except for 243 & 264
    //and these positions : 95, 105, 106, 109, 110, 113, 114, 125, 126, 131, 138, 151, 158, 161, 162, 173, 174, 177, 178, 181, 182, 185

    QSet<int> tempPos ={ 106, 109, 110, 113, 114, 125, 126, 131, 138, 151, 158, 161, 162, 173, 174, 177, 178, 181, 182, 185};

    int tempItr = 0 ;
    int tempItr2= 0;

    for(int i=0; i<31; i++){

        for(int j=0; j<28; j++){

            //adding powerpellets and small pellets
            if(boardInstance->getBoardData(i,j) == 31 || boardInstance->getBoardData(i,j) == 36 || boardInstance->getBoardData(i,j) == 243 || boardInstance->getBoardData(i,j) == 222 ){
                powerPelletsarr[tempItr2].setPos(blockDim*j + margin, blockDim*i + margin);
                scene->addItem(&powerPelletsarr[tempItr2]);
                tempItr2++;
            }else if( boardInstance->getBoardData(i,j) > 0 && boardInstance->getBoardData(i,j) < 106 ){
                smallPelletsarr[tempItr].setPos(blockDim*j + margin, blockDim*i + margin);
                scene->addItem(&smallPelletsarr[tempItr]);
                tempItr++;
            }else if(boardInstance->getBoardData(i,j) > 185 && boardInstance->getBoardData(i,j) < 310 ){
                smallPelletsarr[tempItr].setPos(blockDim*j + margin, blockDim*i + margin);
                scene->addItem(&smallPelletsarr[tempItr]);
                tempItr++;
            }else if( tempPos.contains(boardInstance->getBoardData(i,j)) ){

                smallPelletsarr[tempItr].setPos(blockDim*j + margin, blockDim*i + margin);
                scene->addItem(&smallPelletsarr[tempItr]);
                tempItr++;

            }

        }

    }

}

//this is called if the player decides to continue (Y) or when the game starts for the first time.
void GameManager::StartAgain() {
    scene->removeItem(gamestate);
    musicManager->playMain();
    fillPellets();
    pacman->startanim();
    timer->start(18);
    int temp = (qrand()%5) + 14;
    timerFruit->start(1000*temp);//the fruit will appear after 13 to 15 seconds, we can make this random
}



//this function creates the fruit, the timer calls it randomly between 10 to 15 seconds
void GameManager::createFruit(){

    //set sprite of the fruit
    fruitInstance.setRandSprite();

    //set pos of the fruit
    int tempR = qrand()%31;
    int tempC = qrand()%28;
    while(boardInstance->getBoardData(tempR, tempC) < 0){ //I keep looping till I find a suitable space for the fruit.
        tempR = qrand()%31;
        tempC = qrand()%28;
    }
    fruitInstance.setPos(blockDim*tempC + margin, blockDim*tempR + margin);

    //add it to the scene
    scene->addItem(&fruitInstance);

    //calling the timer again but with a different value
    int tempT = (qrand()%5) + 14;
    timerFruit->start(1000*tempT);
}

void GameManager::delayStart()
{
    timer->start();
    pacman->startanim();
}

GameManager::~GameManager() {

    delete pacman;
    delete remlives;
    delete gamestate;
    delete currentscore;
    delete pacstate;
    delete scene;
    delete timerFruit;
    delete timerGhostState;
    delete timer;
    delete boardInstance;
    delete InkyInstant;
    delete PinkyInstant;
    delete BlinkyInstant;
    delete musicManager;

}
