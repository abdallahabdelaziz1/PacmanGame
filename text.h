#ifndef TEXT_H
#define TEXT_H

#include <QObject>
#include <QGraphicsTextItem>
#include <QFont>
#include<QTimer>

class text : public QGraphicsTextItem
{
    Q_OBJECT


protected:
 //   QFont font; this should be removed Abdallah? Sah?
    QString display;
    QTimer* gameovertimer;
    QTimer* wintimer;
    QFont *arcade;
private slots:
    void ChangeToContinue();//after 2 seconds of showing "you won", it shows "Continue? Y\N".
    void ChangeToRepeat();//after 2 seconds of showing "Game over", it shows "Again? Y\N".
public:
    text();                           //initiated at teh begining of the game and shows the word "READY!" on screen.
    void lost();                      //make the display "GAME OVER"
    void won();                       //make the display "You won" then after 3 seconds shows "Continue? Y\N".

};

#endif // TEXT_H
