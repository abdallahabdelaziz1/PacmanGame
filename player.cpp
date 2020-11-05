#include "player.h"

player::player() {
    QPixmap playerImage("pacman.png");
    playerImage = playerImage.scaledToWidth(blockDim);
    playerImage = playerImage.scaledToHeight(blockDim);
    setPixmap(playerImage);
    setPos(0.5*blockDim*27+margin, blockDim*23+margin);      //0.5blockdim*27+20, blockdim*23+20
    state = "normal";
}
int player::getRow() {
    return row;
}
int player::getCol() {
    return col;
}

void player::move()
{
    if(direct == 'U')
        row--;
    else if (direct == 'D')
        row++;
    else if (direct == 'L')
        col++;
    else
        col--;
    setPos(0.5*blockDim*col+margin, 0.5*blockDim*row+margin);
}

void player::changedir(char dir){
    direct = dir;
}
void player::changestate(){
    if (state == "normal")
        state = "invencible";
    else
        state = "normal";
}
