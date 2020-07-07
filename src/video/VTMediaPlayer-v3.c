#include <string.h>
#include "VTMediaPlayer-v3.h"

/**
 * ��������ʼ����file-path or http/https URL��
 *
 * @param url �ļ�·������URL
 *
 *
 */
int init(char *url, int x, int y, int width, int height) {
	Tplayer_init(url, x, y, width, height);
	return 0;
}
/**
 * ��ʼ������Ƶ, ֧��MP3����
 *
 *
 */
int play(void) {
	Tplay_start();
	return 0;
}
/**
 * ֹͣ���� �ͷ��ڴ���Դ������״̬ΪIDLE
 *
 *
 */
int stop(void) {
	Tplay_stop();
	return 0;
}

int pause(void) {
	Tplay_pause();
	return 0;
}
int destory(void) {
	Tplay_destroy();
	return 0;
}

int h264raw_updata_stream(unsigned char *frame_data, unsigned int len) {
	Tplay_write_data(frame_data, len);
	return 0;
}
