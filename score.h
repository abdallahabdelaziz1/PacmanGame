#ifndef SCORE_H
#define SCORE_H

#include "text.h"
class score: public text
{
private:
    void lost();
public:
    score();
    void updatescore(int newscore);        //takes an integer as argument to show on screen
};

#endif // SCORE_H
