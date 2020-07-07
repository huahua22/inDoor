#include "Tplay.h"

static DemoPlayerContext demoPlayer;

static int semTimedWait(sem_t *sem, int64_t time_ms) {
	int err;

	if (time_ms == -1) {
		err = sem_wait(sem);
	} else {
		struct timespec ts;
		clock_gettime(CLOCK_REALTIME, &ts);
		ts.tv_nsec += time_ms % 1000 * 1000 * 1000;
		ts.tv_sec += time_ms / 1000 + ts.tv_nsec / (1000 * 1000 * 1000);
		ts.tv_nsec = ts.tv_nsec % (1000 * 1000 * 1000);

		err = sem_timedwait(sem, &ts);
	}
}
int CallbackForTPlayer(void *pUserData, int msg, int param0, void *param1) {
	DemoPlayerContext *pDemoPlayer = (DemoPlayerContext*) pUserData;

	CEDARX_UNUSE(param1);
	switch (msg) {
	case TPLAYER_NOTIFY_PREPARED: {
		printf("TPLAYER_NOTIFY_PREPARED,has prepared.\n");
		sem_post(&pDemoPlayer->mPreparedSem);
		pDemoPlayer->mPreparedFlag = 1;
		break;
	}

	case TPLAYER_NOTIFY_PLAYBACK_COMPLETE: {
		printf("TPLAYER_NOTIFY_PLAYBACK_COMPLETE\n");
		break;
	}

	case TPLAYER_NOTIFY_SEEK_COMPLETE: {
		printf("TPLAYER_NOTIFY_SEEK_COMPLETE>>>>info: seek ok.\n");
		break;
	}

	case TPLAYER_NOTIFY_MEDIA_ERROR: {
		switch (param0) {
		case TPLAYER_MEDIA_ERROR_UNKNOWN: {
			printf("erro type:TPLAYER_MEDIA_ERROR_UNKNOWN\n");
			break;
		}
		case TPLAYER_MEDIA_ERROR_UNSUPPORTED: {
			printf("erro type:TPLAYER_MEDIA_ERROR_UNSUPPORTED\n");
			break;
		}
		case TPLAYER_MEDIA_ERROR_IO: {
			printf("erro type:TPLAYER_MEDIA_ERROR_IO\n");
			break;
		}
		}
		printf("TPLAYER_NOTIFY_MEDIA_ERROR\n");
		pDemoPlayer->mError = 1;

		printf("error: open media source fail.\n");
		break;
	}

	case TPLAYER_NOTIFY_NOT_SEEKABLE: {
		pDemoPlayer->mSeekable = 0;
		printf("info: media source is unseekable.\n");
		break;
	}

	case TPLAYER_NOTIFY_BUFFER_START: {
		printf("have no enough data to play\n");
		break;
	}

	case TPLAYER_NOTIFY_BUFFER_END: {
		printf("have enough data to play again\n");
		break;
	}

	case TPLAYER_NOTIFY_VIDEO_FRAME: {
		//printf("get the decoded video frame\n");
		break;
	}

//	case TPLAYER_NOTIFY_AUDIO_FRAME: {
//		//printf("get the decoded audio frame\n");
//		break;
//	}

	case TPLAYER_NOTIFY_SUBTITLE_FRAME: {
		//printf("get the decoded subtitle frame\n");
		break;
	}
	case TPLAYER_NOTYFY_DECODED_VIDEO_SIZE: {
		int w, h;
		w = ((int*) param1)[0];   //real decoded video width
		h = ((int*) param1)[1];   //real decoded video height
		printf("*****tplayerdemo:video decoded width = %d,height = %d", w, h);
		printf("real set to display rect:w = %d,h = %d\n", w, h);
		//TPlayerSetSrcRect(pDemoPlayer->mTPlayer, 0, 0, w, h);
		break;
	}

	default: {
		printf("warning: unknown callback from Tinaplayer.\n");
		break;
	}

	}

	return 0;
}

void Tplayer_init(char *url, int x, int y, int width, int height) {
	int waitErr;
	if (demoPlayer.mTPlayer == NULL) {
		memset(&demoPlayer, 0, sizeof(DemoPlayerContext));
		demoPlayer.mError = 0;
		demoPlayer.mSeekable = 1;
		demoPlayer.mPreparedFlag = 0;
		demoPlayer.mMediaInfo = NULL;
		demoPlayer.mTPlayer = TPlayerCreate(CEDARX_PLAYER, x, y, width, height);

		//int waitErr;
		if (demoPlayer.mTPlayer == NULL) {
			printf("can not create tplayer, quit.\n");
			exit(-1);
		}
	}
	// reset player
	//TPlayerReset(demoPlayer.mTPlayer);
	if (TPlayerReset(demoPlayer.mTPlayer) != 0) {
		printf("TPlayerReset return fail.\n");
	} else {
		printf("reset the player ok.\n");
		if (demoPlayer.mError == 1) {
			demoPlayer.mError = 0;
		}
		//PowerManagerReleaseWakeLock("tplayerdemo");
	}
	//* set callback to player.
	TPlayerSetNotifyCallback(demoPlayer.mTPlayer, CallbackForTPlayer,
			(void*) &demoPlayer);
	if (((access("/dev/zero", F_OK)) < 0) || ((access("/dev/fb0", F_OK)) < 0)) {
		printf("/dev/zero OR /dev/fb0 is not exit\n");
	} else {

		// system("dd if=/dev/zero of=/dev/fb0 bs=1K count=1200");//clean the framebuffer
	}
	sem_init(&demoPlayer.mPreparedSem, 0, 0);
	//* set url to the tinaplayer.
	strcpy(demoPlayer.mUrl, url);
	if (TPlayerSetDataSource(demoPlayer.mTPlayer, (const char*) demoPlayer.mUrl,
	NULL) != 0) {
		printf("TPlayerSetDataSource() return fail.\n");
	} else {
		printf("TPlayerSetDataSource() end\n");
	}

	demoPlayer.mPreparedFlag = 0;
	if (TPlayerPrepareAsync(demoPlayer.mTPlayer) != 0) {
		printf("TPlayerPrepareAsync() return fail.\n");
	} else {
		printf("preparing...\n");
	}
	waitErr = semTimedWait(&demoPlayer.mPreparedSem, 10 * 1000);
	if (waitErr == -1) {
		printf("prepare fail\n");
	}
	printf("prepare ok\n");
	printf("start play\n");

}
void Tplay_start() {
	if (TPlayerStart(demoPlayer.mTPlayer) != 0) {
		printf("TPlayerStart() return fail.\n");
	} else {
		printf("started.\n");
		//PowerManagerAcquireWakeLock("tplayerdemo");
	}
}

void Tplay_stop() {
	if (TPlayerStop(demoPlayer.mTPlayer) != 0) {
		printf("TPlayerStop() return fail.\n");
	} else {
		printf("TPlayer Stop...\n");
	}
}
void Tplay_pause() {
	if (TPlayerPause(demoPlayer.mTPlayer) != 0) {
		printf("TPlayerPause() return fail.\n");
	} else {
		printf("TPlayer pause...\n");
	}
}
void Tplay_destroy() {
	TPlayerDestroy(demoPlayer.mTPlayer);
	printf("TPlayer destroy...\n");

}
void Tplay_resume() {
	if (TPlayerReset(demoPlayer.mTPlayer) != 0) {
		printf("TPlayerReset() return fail.\n");
	} else {
		printf("reset the player ok.\n");
	}
}

void Tplay_write_data(unsigned char *frame_data, unsigned int len) {
	TPlayerWriteData(demoPlayer.mTPlayer, frame_data, len);
}

int Tplay_Get_FreeSize() {
	return TPlayerGetFreeSize(demoPlayer.mTPlayer);
}
