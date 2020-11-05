#ifndef BLINKY_H
#define BLINKY_H


#include "ghosts.h"

class Blinky:public Ghosts
{
private:
    const int InitialRow=14;
     const int InitialColumn=11;
public:
    Blinky(int** temp);
  //  void FollowPaceman() override; //will be defined later
    void ReturnHome() override;
    void ReturnOriginalState() override;

};
#endif // BLINKY_H
