#ifndef INKY_H
#define INKY_H
#include "ghosts.h"

class Inky:public Ghosts
{
private:
    const int InitialRow=14;
     const int InitialColumn=12;
public:
    Inky(int** temp);
  //  void FollowPaceman() override; //will be defined later
    void ReturnHome() override;
    void ReturnOriginalState() override;

};

#endif // INKY_H
