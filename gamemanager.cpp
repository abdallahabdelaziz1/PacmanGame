
#include "gamemanager.h"

GameManager::GameManager()

{

    scene=new QGraphicsScene;
    (this)->QGraphicsView::setFixedSize(sceneDim, sceneDim);
    this->setBackgroundBrush(QBrush(Qt::black, Qt::SolidPattern));
    this->setScene(scene);
        //1-)Create the view and the scene

     //this->setWindowTitle("Pacman Game");
     //this->setBackgroundBrush(QBrush(Qt::black, Qt::SolidPattern)); //this changes the background color to black
     //this->setScene(&gameScene);

    srand(time(NULL));

    timer=new QTimer(this);
    connect(timer, SIGNAL(timeout()),this, SLOT(advance()));

    timerGhostState=new QTimer(this);
    connect(timerGhostState, SIGNAL(timeout()),this, SLOT(ghostStateTimeout()));

    timerFruit=new QTimer(this);
    connect(timerFruit, SIGNAL(timeout()),this, SLOT(createFruit()));

    //The game manager will initialize the game
    boardInstance=new board(scene);

    //fillpellets on the scene
    fillPellets();


//adding the ghosts to the scene
    InkyInstant=new Inky(boardInstance->getBoardPointer());
    scene->addItem(InkyInstant);



    PinkyInstant=new Pinky(boardInstance->getBoardPointer());
    scene->addItem(PinkyInstant);


    BlinkyInstant=new Blinky(boardInstance->getBoardPointer());
   scene->addItem(BlinkyInstant);




   //adding score, remaining lives, and game state
   pacman = new player(boardInstance->getBoardPointer());
   remlives = new lives(scene);
   gamestate = new text;

   currentscore = new score;
   pacstate = new state;
   scene->addItem(pacstate);
   scene->addItem(pacman);
   scene->addItem(gamestate);
   scene->addItem(currentscore);

}



void GameManager::keyPressEvent(QKeyEvent *event)
{

    if (event->key() == Qt::Key_Space && !started)
    {
       started=true;
       StartAgain();

    }

    if(remlives->Died()){

        if(event->key()==Qt::Key_Y){
           StartAgain();
           playerScore=0;
            tenkcount=1;
            currentscore->updatescore(0);
            remlives->addliveWithPhoto();
            remlives->addliveWithPhoto();
            remlives->addliveWithoutphoto();

        }
        else if(event->key()==Qt::Key_N){
            this->close();
        }
    }
    else if(UneatenPellets==0){
        if(event->key()==Qt::Key_Y){
           StartAgain();
        }
        else if(event->key()==Qt::Key_N){
            this->close();
        }

    }
    else if(started){
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
    //adding a life everytime the player gains 10,000 points
    if(playerScore/10000==tenkcount){
        //qDebug()<<playerScore/10000;
        remlives->addliveWithPhoto();
        tenkcount++;
    }

    QList<QGraphicsItem*> collidedItems = pacman->collidingItems();
    for(int i=0; i < collidedItems.size(); i++){
        if( typeid(*collidedItems[i]) == typeid(smallPellets)){
            scene->removeItem(collidedItems[i]);
            playerScore += smallPelletsarr[0].getValue();
            UneatenPellets--;
        }else if(typeid(*collidedItems[i]) == typeid(powerPellets)){
            scene->removeItem(collidedItems[i]);
            UneatenPellets--;

            Ghosts::SetValue();//sets value to 200
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
                resetGame();
            }
        }else if(typeid(*collidedItems[i]) == typeid(Pinky)){
            if(PinkyInstant->getAttackingState() == 0){
                PinkyInstant->ReturnHome();
                playerScore += Ghosts::GetValue();
                 Ghosts::DoubleValue();
            }else{
                remlives->loselife();
                resetGame();
            }
        }else if(typeid(*collidedItems[i]) == typeid(Blinky)){
            if(BlinkyInstant->getAttackingState() == 0){
                BlinkyInstant->ReturnHome();
                playerScore += Ghosts::GetValue();
                 Ghosts::DoubleValue();
            }else{
                remlives->loselife();
                resetGame();
            }
        }else if(typeid(*collidedItems[i]) == typeid(fruit)){
                scene->removeItem(collidedItems[i]);
                fruit::increaseCount();
                playerScore += fruitInstance.getValue();
                int tempT = (qrand()%5) + 11;
                timerFruit->start(1000*tempT);
        }

    }

    currentscore->updatescore(playerScore);

    if(remlives->Died()){

        gamestate->lost();
        scene->addItem(gamestate);
        timer->stop();
        timerFruit->stop();
        pacman->endanim();
    }
    else if(UneatenPellets==0){
        gamestate->won();
        scene->addItem(gamestate);
        timer->stop();
        timerFruit->stop();
        pacman->endanim();
        resetGame();
    }
    else{
    InkyInstant->FollowPaceman();
    PinkyInstant->FollowPaceman();
    BlinkyInstant->FollowPaceman();
    pacman->move();
    }



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
    Ghosts::SetValue();
    pacstate->normalstate();
    timerGhostState->stop();

}

void GameManager::resetGame(){
    Ghosts::SetValue();
    InkyInstant->ReturnHome();
    PinkyInstant->ReturnHome();
    BlinkyInstant->ReturnHome();
    pacman->reset();
    pacstate->normalstate();

}

void GameManager::fillPellets()
{
    UneatenPellets=248;
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
                smallPelletsarr[tempItr].setPos(blockDim*j + margin, blockDim*i + margin);
                scene->addItem(&smallPelletsarr[tempItr]);
                tempItr++;
            }else if(boardInstance->getBoardData(i,j) > 185 && boardInstance->getBoardData(i,j) < 310 && boardInstance->getBoardData(i,j) != 222 && boardInstance->getBoardData(i,j) != 243){
                smallPelletsarr[tempItr].setPos(blockDim*j + margin, blockDim*i + margin);
                scene->addItem(&smallPelletsarr[tempItr]);
                tempItr++;
            }else{
                for(int k=0; k<20; k++){
                    if(tempArr[k] == boardInstance->getBoardData(i,j)){
                        smallPelletsarr[tempItr].setPos(blockDim*j + margin, blockDim*i + margin);
                       scene->addItem(&smallPelletsarr[tempItr]);
                        tempItr++;
                    }
                }
            }


            if(boardInstance->getBoardData(i,j) == 31 || boardInstance->getBoardData(i,j) == 36 || boardInstance->getBoardData(i,j) == 243 || boardInstance->getBoardData(i,j) == 222 ){
                powerPelletsarr[tempItr2].setPos(blockDim*j + margin, blockDim*i + margin);
                scene->addItem(&powerPelletsarr[tempItr2]);
                tempItr2++;
            }

        }
    }



}

void GameManager::StartAgain()
{
    scene->removeItem(gamestate);
    fillPellets();
    pacman->startanim();
    timer->start(20);
    int temp = (qrand()%5) + 11;
    timerFruit->start(1000*temp);//the fruit will appear after 10 to 15 seconds, we can make this random


}

void GameManager::createFruit()
{
    //set sprite, set pos, add item
    fruitInstance.setRandSprite();

    //set pos
    int tempR = qrand()%31;
    int tempC = qrand()%28;
    while(boardInstance->getBoardData(tempR, tempC) < 0){
        tempR = qrand()%31;
        tempC = qrand()%28;
    }
    fruitInstance.setPos(blockDim*tempC + margin, blockDim*tempR + margin);

    //add it to the scene
    scene->addItem(&fruitInstance);

    //calling the timer again but with a different value
    int tempT = (qrand()%5) + 11;
    timerFruit->start(1000*tempT);
}

GameManager::~GameManager()
{
}
