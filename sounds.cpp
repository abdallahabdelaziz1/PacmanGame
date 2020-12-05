#include "sounds.h"

Sounds::Sounds()
{

    //creating the playlist and adding the music
    mainPlaylist = new QMediaPlaylist();
    mainPlaylist->addMedia(QUrl::fromLocalFile("pacmanMainSound.mp3"));
    mainPlaylist->addMedia(QUrl::fromLocalFile("pacmanWin.mp3"));  //from zapsplat.com
    mainPlaylist->addMedia(QUrl::fromLocalFile("pacmanGameover.mp3"));

    //creating the media player which plays a specific music in the playlist by setPlaylist
    currentMedia = new QMediaPlayer();
    currentMedia->setPlaylist(mainPlaylist);


}

void Sounds::stopPlayer(){
    currentMedia->stop(); //stops the music played
}

//sets which music to play in the playlist and what mode to play it in and plays it from the media player.
void Sounds::playMain(){
    mainPlaylist->setCurrentIndex(0);
    mainPlaylist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
    currentMedia->setVolume(30);
    currentMedia->play();
}

//sets which music to play in the playlist and what mode to play it in and plays it from the media player.
void Sounds::playWin(){
    mainPlaylist->setCurrentIndex(1);
    mainPlaylist->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);
    currentMedia->play();
}

//sets which music to play in the playlist and what mode to play it in and plays it from the media player.
void Sounds::playLose(){
    mainPlaylist->setCurrentIndex(2);
    mainPlaylist->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);
    currentMedia->play();
}


