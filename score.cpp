#include "score.h"

score::score():text()
{
    display= "0";
    setPlainText(display);
    setDefaultTextColor(Qt::white);
    setPos(16, 0);
}
void score::updatescore(int newscore){
    display = QString::number(newscore);
    setPlainText(display);
}


