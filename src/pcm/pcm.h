/*
 * pcm.h
 *
 *  Created on: 2020年1月8日
 *      Author: xwr
 */

#ifndef UDP_PCM_H_
#define UDP_PCM_H_
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>
#include<arpa/inet.h>
#include "tinyalsa/asoundlib.h"
#include "speex/speex_echo.h"
#include "speex/speex_preprocess.h"

#define     PCM_PORT      9002
#define     BUF_SIZE 320
void init_pcm_property();
int init_server_pcm(void);
void* PcmThread();
void setPcmThread();
void stopPcm();
void setPcm();
void closePcmSocket();
#endif /* UDP_PCM_H_ */
