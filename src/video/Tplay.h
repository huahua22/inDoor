#ifndef _TPLAY_VOID_
#define _TPLAY_VOID_

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <ctype.h>
#include <errno.h>
#include <sys/select.h>
#include <sys/types.h>
#include <dirent.h>
#include <fcntl.h>

#include <allwinner/tplayer.h>

#define TOTAL_VIDEO_AUDIO_NUM
#define MAX_FILE_NAME_LEN
typedef int (*TP_NotifyCallback)(int msg, void* para);
//TP_NotifyCallback		g_mNotifier;
typedef struct DemoPlayerContext
{
    TPlayer*        mTPlayer;
    int                 mSeekable;
    int                 mError;
    int                 mVideoFrameNum;
    bool              mPreparedFlag;

    char              mUrl[512];
    MediaInfo*    mMediaInfo;
   // char              mVideoAudioList[TOTAL_VIDEO_AUDIO_NUM][MAX_FILE_NAME_LEN];
    int                 mCurPlayIndex;
    int                 mRealFileNum;
    sem_t             mPreparedSem;
   void*				g_mUserData;

   #if 0
   //zera del
   bool              mLoopFlag;
   bool              mSetLoop;
   #endif
}DemoPlayerContext;


void Tplayer_init(char *url,int x, int y, int width,int height);
void Tplay_start();
void Tplay_stop();
void Tplay_pause();
void Tplay_destroy();



//zera del
#if 0
void Tplay_seekto(int time);
void Tplay_pause();
void Tplay_setVolume(float leftVolume, float rightVolume);
void Tplay_setLooping(bool looping);
bool Tplay_isLooping();
void Tplay_resume();
#endif
#endif
