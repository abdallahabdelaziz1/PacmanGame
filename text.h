#ifndef TEXT_H
#define TEXT_H

#include <QObject>
#include <QGraphicsTextItem>
#include <QFont>

class text : public QGraphicsTextItem
{
    Q_OBJECT

protected:
    QFont font;
    QString display;
public:
    text();                           //initiated at teh begining of the game and shows the word "READY!" on screen.
    void lost();                      //switches form "READY!" to "GAME OVER"
};

#endif // TEXT_H
