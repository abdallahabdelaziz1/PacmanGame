#ifndef PINKY_H
#define PINKY_H
#include "ghosts.h"

class Pinky: public Ghosts
{
private:
    const int InitialRow=14;
     const int InitialColumn=16;
public:
    Pinky(int** temp);
  //  void FollowPaceman() override; //will be defined later
    void ReturnHome() override; //returns pinky to its home
    void ReturnOriginalState() override;//returns its image without returning to its home
    virtual void UpdateShortestPath(QPair <int, int> PacmanCoordiante) override;


};

#endif // PINKY_H
