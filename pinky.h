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
    virtual void UpdateShortestPath(QPair <int, int> PacmanCoordiante, int pacManDir=0) override;
    void ReturnHome() override; //returns pinky to its home
    void ReturnOriginalState() override;//returns its image without returning to its home


};

#endif // PINKY_H
