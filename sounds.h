#ifndef SOUNDS_H
#define SOUNDS_H
#include <QMediaPlayer>
#include<QMediaPlaylist>

class Sounds
{

private:
      QMediaPlaylist * Playlist;
//sugessoion: make only one QMediaPlayer called Player
//you wuill use to play whatever in PlayList
//you can make one stop funciton
      QMediaPlayer* backgroundmusic;
      QMediaPlayer* winmusic;
      QMediaPlayer* losemusic;
public:
    Sounds();
    void PlayGeneral();
    void StopGeneral();

    void PlayWin();
    void StopWin();

    void PlayLose();
    void StopLose();
};

#endif // SOUNDS_H
