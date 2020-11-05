#ifndef SCORE_H
#define SCORE_H

#include "text.h"
class score: public text
{
private:
    void lost();
public:
    score();
    void updatescore(int newscore);
};

#endif // SCORE_H
