#include "text.h"

text::text()
{
    QFont arcade("Emulogic", 8);
    setFont(arcade);
    display = "READY!";
    setPlainText(display);
    setPos(13*16, 18*16);        //13*blockdim, 18*blockdim
    setDefaultTextColor(QColor(254, 232, 0));
}

void text::lost(){
    display = "GAME OVER";
    setDefaultTextColor(Qt::red);
    setPlainText(display);
    setPos(11*16, 18*16);      //11*blockdim, 18*blockdim
}
