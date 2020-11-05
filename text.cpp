#include "text.h"

text::text()
{
    QFont arcade("Emulogic", 12);
    setFont(arcade);
    display = "READY!";
    setPlainText(display);
    setPos(13*20, 17*20);        //13*blockdim, 18*blockdim
    setDefaultTextColor(QColor(254, 232, 0));
}

void text::lost(){
    display = "GAME OVER";
    setDefaultTextColor(Qt::red);
    setPlainText(display);
    setPos(11*20, 18*20);      //11*blockdim, 18*blockdim
}
