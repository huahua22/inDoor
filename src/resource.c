/*
 * resource.c
 *
 *  Created on: 2020年3月20日
 *      Author: xwr
 */

#include "resource.h"
BITMAP bgbmp;
void LoadBgBmp(){
	LoadBitmap(HDC_SCREEN, &bgbmp, bg_name);
}

void LoadWallBmp(){
	LoadBitmap(HDC_SCREEN, &wall, "./res/image/setting.png");
}
void UnloadWallBmp(){
	UnloadBitmap(&wall);
}
void UnloadBgBmp(){
	UnloadBitmap(&bgbmp);
}
void FillBgBmp(HDC hdc){
	FillBoxWithBitmap(hdc, 0, 0, WINDOW_RX, WINDOW_RY, &bgbmp);
}
void FillWallBmp(HDC hdc,int x,int y,int w,int h){
	FillBoxWithBitmap(hdc, x, y, w, h, &wall);
}

//void fillHomeBmp(HDC hdc) {
//	FillBoxWithBitmap(hdc, 0, 0, WINDOW_RX, WINDOW_RY, &bgbmp);
//	FillBoxWithBitmap(hdc, HOME_COX, 100, HOME_NORMAL_WIDTH,
//	HOME_NORMAL_HEIGHT, &rcbmp);
//	FillBoxWithBitmap(hdc, HOME_COX, 196, HOME_NORMAL_WIDTH,
//	HOME_NORMAL_HEIGHT, &ocbmp);
//	FillBoxWithBitmap(hdc, HOME_COX, 292, HOME_NORMAL_WIDTH,
//	HOME_NORMAL_HEIGHT, &robmp);
//	FillBoxWithBitmap(hdc, 169, 100, 204, 274, &tbbmp);
//	FillBoxWithBitmap(hdc, 383, 100, 116, 133, &shbmp);
//	FillBoxWithBitmap(hdc, 509, 100, 250, 133, &vibmp);
//	FillBoxWithBitmap(hdc, 383, 243, 250, 133, &fcbmp);
//	FillBoxWithBitmap(hdc, 643, 243, 116, 133, &oabmp);
//
//	FillBoxWithBitmap(hdc, 0,0,800,38,&tb);
//	FillBoxWithBitmap(hdc, 10, 0, 33, 38, &tnet);
//	FillBoxWithBitmap(hdc, 53, 0, 33, 38, &tsecur);
//	FillBoxWithBitmap(hdc, 96, 0, 33, 38, &tpic);
//	FillBoxWithBitmap(hdc, 139, 0, 33, 38, &tmsg);
//	FillBoxWithBitmap(hdc, 180, 0, 33, 38, &tcall);
//
//	FillBoxWithBitmap(hdc, 26,416,124,64,&hic);
//	FillBoxWithBitmap(hdc, 151,416,124,64,&hbm);
//	FillBoxWithBitmap(hdc, 276,416,124,64,&hci);
//	FillBoxWithBitmap(hdc, 401,416,124,64,&hcc);
//	FillBoxWithBitmap(hdc, 526,416,124,64,&hus);
//	FillBoxWithBitmap(hdc, 651,416,124,64,&hss);
//}
