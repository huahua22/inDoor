/*
 * pcm.c
 *
 *  Created on: 2020年1月8日
 *      Author: xwr
 */

#include "pcm.h"
int pcming = 1;
char buf[BUF_SIZE];
char out_buf[BUF_SIZE];
char recv_buf[BUF_SIZE];
pthread_t pcmThread;
struct pcm *out_pcm, *in_pcm;
static struct sockaddr_in pcm_addr, pcm_peer;
static socklen_t len = sizeof(struct sockaddr_in);
int pcmcfd;
int pcm_fd;
int apt = 1;
void setPcmThread() {
	pthread_create(&pcmThread, NULL, PcmThread, NULL);
}
void setPcm() {
	printf("start pcm\n");
	init_pcm_property();
	init_server_pcm();
	setPcmThread();
}
/*
 * 初始声卡的配置
 */
void init_pcm_property() {
	unsigned int card = 0;
	unsigned int device = 0;
	unsigned int channels = 1;
	unsigned int rate = 8000;
	enum pcm_format format = PCM_FORMAT_S16_LE;
	unsigned int period_size = 1024;
	unsigned int period_count = 4;
	struct pcm_config config;
	memset(&config, 0, sizeof(config));
	config.channels = channels;
	config.rate = rate;
	config.period_size = period_size;
	config.period_count = period_count;
	config.format = format;
	config.start_threshold = 0;
	config.stop_threshold = 0;
	config.silence_threshold = 0;
	//播音
	printf("----------------open pcm out--------------\n");
	out_pcm = pcm_open(card, device, PCM_OUT, &config);
	printf("----------------open--------------\n");
	if (!out_pcm || !pcm_is_ready(out_pcm)) {
		printf("Unable to open PCM OUT device (%s)\n", pcm_get_error(out_pcm));
		exit(-1);
	}
	//录音
	printf("----------------open pcm in--------------\n");
	in_pcm = pcm_open(card, device, PCM_IN, &config);
	if (!in_pcm || !pcm_is_ready(in_pcm)) {
		printf("Unable to open PCM IN device (%s)\n", pcm_get_error(in_pcm));
		exit(-1);
	}
}
int init_server_pcm(void) {
	int ret = 0;
	int opt = 1;
	int opt_len = sizeof(opt);
	printf("Createing pcm socket...\n");
	pcm_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (pcm_fd == -1) {
		perror("pcm socket");
		return -1;
	}
	setsockopt(pcm_fd, SOL_SOCKET, SO_REUSEADDR, (char*) &opt, opt_len);
	int flag = fcntl(pcm_fd, F_GETFL, 0);
	if (flag < 0) {
		perror("fcntl F_GETFL fail");
		return -1;
	}
	fcntl(pcm_fd, F_SETFL, flag | O_NONBLOCK);
	pcm_addr.sin_family = AF_INET;
	pcm_addr.sin_port = htons(PCM_PORT);
	pcm_addr.sin_addr.s_addr = INADDR_ANY;
	ret = bind(pcm_fd, (struct sockaddr*) &pcm_addr, sizeof(pcm_addr));
	if (ret == -1) {
		perror("bind pcm");
		return -1;
	}
	if (listen(pcm_fd, 1) == -1) {
		perror("listen pcm");
		pthread_exit((void*) -1);
	}
	return ret;
}

void* PcmThread() {
	int ret;
	SpeexEchoState *echo_state;
	SpeexPreprocessState *preprocess_state;
	spx_int32_t denoise = 1;
	spx_int32_t noiseSuppress = -15;	//负的32位整数 -25
	spx_int32_t agc = 1;
	spx_int32_t level = 8000;
	int vad = 1;
	int vadProbStart = 80;
	int vadProbContinue = 45;
	spx_int32_t supperess_active = -30;
	spx_int32_t supperess = -10;
	unsigned int rate = 8000;
	unsigned int size;
	unsigned int frames_per_sec = 8000 / 50;  //20ms录音
	int frame_size = 160;  //20ms采样一次
	int filter_length = 2500;  //回声消除滤波器的长度
	size = frames_per_sec * pcm_frames_to_bytes(in_pcm, 1);
	echo_state = speex_echo_state_init(frame_size, filter_length);
	//设置回音消除参数
	speex_echo_ctl(echo_state, SPEEX_ECHO_SET_SAMPLING_RATE, &rate);
	//降噪 增益 静音
	preprocess_state = speex_preprocess_state_init(frame_size, rate);
	speex_preprocess_ctl(preprocess_state, SPEEX_PREPROCESS_SET_DENOISE,
			&denoise);  //降噪
	speex_preprocess_ctl(preprocess_state, SPEEX_PREPROCESS_SET_NOISE_SUPPRESS,
			&noiseSuppress); //设置噪声的dB
	/*speex_preprocess_ctl(preprocess_state, SPEEX_PREPROCESS_SET_AGC, &agc); //增益
	speex_preprocess_ctl(preprocess_state, SPEEX_PREPROCESS_SET_AGC_LEVEL,
			&level); //自动增益控制
	speex_preprocess_ctl(preprocess_state, SPEEX_PREPROCESS_SET_VAD, &vad); //静音检测
	speex_preprocess_ctl(preprocess_state, SPEEX_PREPROCESS_SET_PROB_START,
			&vadProbStart);
	speex_preprocess_ctl(preprocess_state, SPEEX_PREPROCESS_SET_PROB_CONTINUE,
			&vadProbContinue);
	speex_preprocess_ctl(preprocess_state, SPEEX_PREPROCESS_SET_ECHO_STATE,
			echo_state);
	speex_preprocess_ctl(preprocess_state,
	SPEEX_PREPROCESS_SET_ECHO_SUPPRESS_ACTIVE, &supperess_active); //静音检测
	speex_preprocess_ctl(preprocess_state, SPEEX_PREPROCESS_SET_ECHO_SUPPRESS,
			&supperess); //静音检测
   if(preprocess_state ==NULL){
	   printf("speex_preprocess_state_init failed\n");
	   speex_echo_state_destroy(echo_state);
	   pcming = 0;
	   return -1;
   }*/
	memset(buf, 0x0, BUF_SIZE);
	memset(out_buf, 0x0, BUF_SIZE);
	memset(recv_buf, 0x0, BUF_SIZE);
	socklen_t len = sizeof(struct sockaddr_in);
	while (pcming) {
		while (apt && pcming) {
			pcmcfd = accept(pcm_fd, (struct sockaddr*) &pcm_peer, &len);
			if (pcmcfd > 0) {
				apt = 0;
				close(pcm_fd);
				pcm_fd = 0;
				int flag = fcntl(pcmcfd, F_GETFL, 0);
				if (flag < 0) {
					perror("fcntl F_GETFL fail");
					return -1;
				}
				fcntl(pcmcfd, F_SETFL, flag | O_NONBLOCK);
			}
		}
		while (pcmcfd) {
			memset(recv_buf, 0, BUF_SIZE);
			ret = read(pcmcfd, recv_buf, BUF_SIZE);
			if (ret > 0)
				pcm_writei(out_pcm, recv_buf, frames_per_sec);  //play
			pcm_readi(in_pcm, buf, frames_per_sec);
//			speex_echo_cancellation(echo_state, (spx_int16_t*) buf,
//					(spx_int16_t*) recv_buf, (spx_int16_t*) out_buf);
//			speex_preprocess_run(preprocess_state,buf);
			write(pcmcfd, buf, BUF_SIZE);
			memset(buf, 0x0, BUF_SIZE);
			//connect close
			if (ret == 0) {
				printf("pcm clinet disconnected\n");
				close(pcmcfd);
				pcmcfd = 0;
				pcming = 0;
			}
		}
	}
	speex_echo_state_destroy(echo_state);
	speex_preprocess_state_destroy(preprocess_state);
	printf("------------------pcm close\n");
	pcm_close(in_pcm);
	pcm_close(out_pcm);
}

void stopPcm() {
	printf("-----stop pcm\n");
	close(pcmcfd);
	pcmcfd = 0;
	pcming = 0;
	sleep(1);
	pthread_join(pcmThread, NULL);
	printf("-------------------join pcm pthread\n");
}

void closePcmSocket() {
	printf("--------close pcm socket\n");
	apt = 0;
	close(pcm_fd);
	pcm_fd = 0;
	pcmcfd = 0;
	pcming = 0;
	pthread_join(pcmThread, NULL);
	printf("-------------------join pcm pthread\n");
}
