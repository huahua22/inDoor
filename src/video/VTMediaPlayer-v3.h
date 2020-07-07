#ifndef __VT_MEDIA_PLAYER_H_
#define __VT_MEDIA_PLAYER_H_
#include <string.h>
#include "Tplay.h"
#include <stdbool.h>


  /**
     * ��������ʼ����file-path or http/https URL��
     *
     * @param url �ļ�·������URL
     *
     *
     */
int init(char *url,int x, int y, int width,int height);
  /**
     * ��ʼ������Ƶ, ֧��MP3����
     *
     *
     */
int  play(void);
  /**
     * ֹͣ���� �ͷ��ڴ���Դ������״̬ΪIDLE
     *
     *
     */
int  stop(void);
int destory(void);
int pause(void);
int h264raw_updata_stream(unsigned char *frame_data, unsigned int len);
#endif
