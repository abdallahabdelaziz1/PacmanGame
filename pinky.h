#ifndef PINKY_H
#define PINKY_H
#include "ghosts.h"

class Pinky: public Ghosts
{
private:
    const int InitialRow=13;
     const int InitialColumn=12;
public:
    Pinky(int** temp);
  //  void FollowPaceman() override; //will be defined later
    void ReturnHome() override;
    void ReturnOriginalState() override;
};

#endif // PINKY_H
