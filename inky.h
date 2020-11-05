#ifndef INKY_H
#define INKY_H
#include "ghosts.h"

class Inky:public Ghosts
{
private:
    const int InitialRow=13;
     const int InitialColumn=11;
public:
    Inky(int** temp);
  //  void FollowPaceman() override; //will be defined later
    void ReturnHome() override;
    void ReturnOriginalState() override;

};

#endif // INKY_H
