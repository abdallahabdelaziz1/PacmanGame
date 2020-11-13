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
    void ReturnHome() override; //returns blinky to its home
    void ReturnOriginalState() override;//returns its image without returning to its home

};
#endif // BLINKY_H
