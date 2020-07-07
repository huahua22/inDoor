/*
 * video.c
 *
 *  Created on: 2019年12月9日
 *      Author: xwr
 */

#include "video.h"
int img_fd;
int imgcfd;
static int capturing = 1;
pthread_t sDecodeThread;
static int initFirst = 1;
static struct sockaddr_in img_addr, img_peer;
static socklen_t len = sizeof(struct sockaddr_in);
int nonBlocking_videofd = 0;
int setVideo() {
	capturing = 1;
	int err;
	printf("fly test begin****..\n");
	if (initFirst == 1) {
		init("XXX.H264", 140, 5, 520, 390);
		initFirst = 0;
	}
	play();
	init_server_img();
	err = pthread_create(&sDecodeThread, NULL, WriteThread, NULL);
	if (err != 0) {
		printf("audio decode component create thread fail.");
		return -1;
	}
	return 0;
}

void alarmHandle(int signal) {
	capturing = 0;
	sleep(1);
	pause();
}
void stopVideo() {
	printf("stop video\n");
	close(imgcfd);
	imgcfd = 0;
	capturing = 0;
	pthread_join(sDecodeThread, NULL);
	pause();
	printf("----------------pause video\n");
}
double tick(void)
{
    struct timeval t;
    gettimeofday(&t, 0);
    return t.tv_sec + 1E-6 * t.tv_usec;
}
static void* WriteThread(void *arg) {
	unsigned char *frame_buf = NULL;
	unsigned char *img_buf = NULL;
	int ret;
	frame_buf = malloc(1 * 1024 * 64);
	img_buf = malloc(1024 * 64);
	if (frame_buf == NULL) {
		printf("error frame_buf == NULL\n");
	}
	int frame_len = 0;
	int index = 0;
	memset(frame_buf, 0x0, 1 * 1024 * 64);
	memset(img_buf, 0x0, 1 * 1024 * 64);
	nonBlocking_videofd = 1;
	double time_stamp=0;
	int frame_num =0;
	while (capturing) {
		while (nonBlocking_videofd) {
			imgcfd = accept(img_fd, (struct sockaddr*) &img_peer, &len);
			if (imgcfd > 0) {
				printf("client video connect id=%d\n", imgcfd);
				close(img_fd);
				img_fd =0;
				nonBlocking_videofd =0;
				time_stamp =tick();
				printf("::::::::::::%0.3f\n",time_stamp);
				break;
			}
			imgcfd =0;
		}

		while (imgcfd) {
			if (tick() - time_stamp >= 1) {
				printf("::::::::::::::::frame num:::::::::::%d\n", frame_num);
				frame_num = 0;
				time_stamp = tick();
			}
			memset(img_buf, 0x0, MSG_SIZE);
			ret = read(imgcfd, img_buf, MSG_SIZE);
			if (ret > 0) {
				if (img_buf[0] == 0xff && img_buf[1] == 0x00) {
					int value = 0;
					for (int i = 2; i < 6; i++) {
						int shift = (5 - i) * 8;
						value += (img_buf[i] & 0xFF) << shift;
					}
					frame_len = value;
					memcpy(frame_buf, img_buf + 2, ret - 2);
					index = ret - 2;
//					printf("frame_buf:%d\n", frame_len);
				} else {
					memcpy(frame_buf + index, img_buf, ret);
					index += ret;
				}
				if (index == frame_len + 4) {
					Tplay_write_data(frame_buf, frame_len + 4);
					frame_num++;
					index = 0;
				}
			}
			if (ret <= 0) {
				printf("video clinet disconnected\n");
				close(imgcfd);
				imgcfd = 0;
				sleep(3);
				init_server_img();
				nonBlocking_videofd= 1;
			}
		}
	}
	free(frame_buf);
	free(img_buf);
}

int init_server_img(void) {
	int ret = 0;
	int opt = 1;
	int opt_len = sizeof(opt);
	printf("Createing img socket...\n");
	img_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (img_fd == -1) {
		perr("img socket");
		return -1;
	}
	setsockopt(img_fd, SOL_SOCKET, SO_REUSEADDR, (char*) &opt, opt_len);
	int flag = fcntl(img_fd, F_GETFL, 0);
	if (flag < 0) {
		perror("img fd fcntl F_GETFL fail");
		exit(1);
	}
	fcntl(img_fd, F_SETFL, flag | O_NONBLOCK);
	img_addr.sin_family = AF_INET;
	img_addr.sin_port = htons(img_port);
	img_addr.sin_addr.s_addr = INADDR_ANY;
	ret = bind(img_fd, (struct sockaddr*) &img_addr, sizeof(img_addr));
	if (ret == -1) {
		perr("bind img");
		close(img_fd);
		img_fd = 0;
		init_server_img();
		return -1;
	}
	if (listen(img_fd, 2) == -1) {
		perror("listen");
		pthread_exit((void*) -1);
		printf("...ok\n");
	}
	return ret;
}
void closeVideoSocket() {
	printf("close video socket\n");
	nonBlocking_videofd = 0;
	close(img_fd);
	img_fd = 0;
	capturing = 0;
	pthread_join(sDecodeThread, NULL);
	pause();
	printf("finish video close\n");
}
