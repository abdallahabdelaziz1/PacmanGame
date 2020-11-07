#include "state.h"

state::state()
{
    QFont arcade("Emulogic", 12);
    setFont(arcade);
    display = "Normal";
    setPlainText(display);
    setPos(450, 0);
    setDefaultTextColor(Qt::white);
}

void state::invenciblestate()
{
    display="Invencible";
    setPos(380, 0);
    setDefaultTextColor(Qt::red);
    setPlainText(display);
}

void state::normalstate()
{
    setPos(450, 0);
    display="Normal";
    setDefaultTextColor(Qt::white);
    setPlainText(display);
}
