#include "text.h"


text::text()
{
    arcade=new QFont("Emulogic", 12);
    setFont(*arcade);
    display = "READY!";
    setPlainText(display);
    setPos(13*20, 17*20);        //13*blockdim, 18*blockdim
    setDefaultTextColor(QColor(254, 232, 0));
    gameovertimer=new QTimer(this);
    connect(gameovertimer, SIGNAL(timeout()),this, SLOT(ChangeToRepeat()));
    wintimer=new QTimer(this);
    connect(wintimer, SIGNAL(timeout()), this, SLOT(ChangeToContinue()));



}


void text::lost(){
    display = "GAME OVER";
    setDefaultTextColor(Qt::red);
    setPlainText(display);
    setPos(11*20, 17*20);      //11*blockdim, 18*blockdim
    gameovertimer->start(2000);
}
void text::ChangeToRepeat()
{
    display = "Again? Y\\N";
    setDefaultTextColor(QColor(254, 232, 0));
    setPlainText(display);
    setPos(10*20, 17*20);
    gameovertimer->stop();
}

void text::won()
{
    display = "You Won!";
    setDefaultTextColor(Qt::red);
    setPlainText(display);
    setPos(11*20, 17*20);      //11*blockdim, 18*blockdim
    wintimer->start(2000);

}


void text::ChangeToContinue()
{
    display = "Continue? Y\\N";
    arcade->setPointSize(9);
    setFont(*arcade);
    setDefaultTextColor(QColor(254, 232, 0));

    setPlainText(display);
    setPos(10*20+2, 17*20);
    wintimer->stop();

}

