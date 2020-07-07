/*
 * resource.h
 *
 *  Created on: 2020年3月19日
 *      Author: xwr
 */

#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>
#include <minigui/control.h>
#include <stdio.h>
#include <stdlib.h>
#define WINDOW_LX 0
#define WINDOW_TY 0
#define WINDOW_RX 800
#define WINDOW_RY 480
#define HOME_NORMAL_WIDTH 116
#define HOME_NORMAL_HEIGHT 86
#define HOME_COX 43
BITMAP wall;
static const char *bg_name="./res/image/home_bg.png";
static const char *h_bmp_name[] = { "./res/image/record_cent.png",
		"./res/image/one_call.png", "./res/image/ring_off.png",
		"./res/image/home_time_bg.png", "./res/image/h_smart_home.png",
		"./res/image/h_video_inter.png", "./res/image/h_family_sec.png",
		"./res/image/h_one_arm.png" };
static const char *h_bmp_name_clicked[] ={
		"./res/image/record_cent_clicked.png"
};
static const char *h_tbmp_name[] = { "./res/image/h_top_line.png",
		"./res/image/h_net.png", "./res/image/h_secur.png",
		"./res/image/h_pic.png", "./res/image/h_msg.png",
		"./res/image/h_call.png"};
static const char *h_bbmp_name[] = { "./res/image/h_monit_cent.png",
		"./res/image/h_build_monit.png", "./res/image/h_com_infor.png",
		"./res/image/h_call_cent.png", "./res/image/h_user_set.png",
		"./res/image/h_sys_set.png"};
static const char *op_bmp_name[] = { "./res/image/go_back.png",
		"./res/image/video.png"};
static const char *rc_bmp_name[] = { "./res/image/rc/rc_com_info.png",
		"./res/image/rc/rc_sec.png", "./res/image/rc/rc_call.png",
		"./res/image/rc/rc_take_photo.png", "./res/image/rc/rc_phone.png",
		"./res/image/rc/rc_photo_msg.png" };
void LoadBgBmp();
void UnloadBgBmp();
void FillBgBmp(HDC hdc);
void LoadWallBmp();
void UnloadWallBmp();
void FillWallBmp(HDC hdc,int x,int y,int w,int h);
