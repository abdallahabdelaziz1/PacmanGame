#include "powerpellets.h"

powerPellets::powerPellets() {

    //initializing sprite and value
    sprite.load("powerPellet.png");
    sprite = sprite.scaledToWidth(blockDim);
    sprite = sprite.scaledToHeight(blockDim);
    value = 100;


    // I have to setpixmap, setPos, addItemToScene will do the other two in game manager.
    setPixmap(sprite);
}
