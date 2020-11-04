#include "smallpellets.h"

smallPellets::smallPellets() {

    //initializing sprite and value
    sprite.load("smallPellet.png");
    sprite = sprite.scaledToWidth(blockDim);
    sprite = sprite.scaledToHeight(blockDim);
    value = 10;


    // I have to setpixmap, setPos, addItemToScene I will do the the other two in the game manager.
    setPixmap(sprite);
}
