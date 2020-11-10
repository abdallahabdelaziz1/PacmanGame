#include "sounds.h"

Sounds::Sounds()
{

    Playlist = new QMediaPlaylist();
    Playlist->setPlaybackMode(QMediaPlaylist::Loop);

    backgroundmusic= new QMediaPlayer();
    winmusic=new QMediaPlayer();
    losemusic=new QMediaPlayer();


    backgroundmusic->setMedia(QUrl::fromLocalFile("Y:/projects/HangmanGame/HangManGame/backgroundmusic.mp3"));
    backgroundmusic->play();

}


void Sounds::PlayGeneral(){


}
void StopGeneral();
void PlayWin();
void StopWin();
void PlayLose();
void StopLose();


/*

playlist->addMedia(QUrl("qrc:/sounds/backgroundmusic.mp3"));
playlist->setPlaybackMode(QMediaPlaylist::Loop);

QMediaPlayer *music = new QMediaPlayer();
music->setPlaylist(playlist);
music->play();

 backgroundmusic->setMedia(QUrl::fromLocalFile("Y:/projects/HangmanGame/HangManGame/backgroundmusic.mp3"));

*/
