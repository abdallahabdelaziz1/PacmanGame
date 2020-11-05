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
    text();
    void lost();
};

#endif // TEXT_H
