/*
 * common.h
 *
 *  Created on: 2019年12月6日
 *      Author: xwr
 */
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
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
#include <stdbool.h>
#include <allwinner/tplayer.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include<sys/time.h>
#include <sys/types.h>
#include <fcntl.h>
#ifndef VIDEO_COMMON_H_
#define VIDEO_COMMON_H_
#define     MSG_SIZE    1 * 1024 * 64
#define img_port 9001
#define perr(x) {fflush(stdout);perror(x);return -1;}
typedef struct sock_cb {
	int fd;
	struct sockaddr_in addr;
	int addrlen;
} sock_cb;
int setVideo();
static void* WriteThread(void *arg);
void stopVideo();
void alarmHandle(int signal);
int init_server_img(void);
void closeVideoSocket();
#endif /* VIDEO_COMMON_H_ */

