#ifndef SOUNDS_H
#define SOUNDS_H
#include <QMediaPlayer>
#include<QMediaPlaylist>

class Sounds
{

private:
      QMediaPlaylist * mainPlaylist;
      QMediaPlayer* currentMedia;

public:
    Sounds();

    void playMain();
    void playWin();
    void playLose();
    void stopPlayer();

};

#endif // SOUNDS_H
