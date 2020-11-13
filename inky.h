#ifndef INKY_H
#define INKY_H
#include "ghosts.h"

class Inky:public Ghosts
{
private:
    const int InitialRow=14;
     const int InitialColumn=13;
public:
    Inky(int** temp);
  //  void FollowPaceman() override; //will be defined later
    void ReturnHome() override; //returns inky to its home
    void ReturnOriginalState() override;//returns its image without returning to its home


};

#endif // INKY_H
