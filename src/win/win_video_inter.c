/*
 * video_inter.c
 *
 *  Created on: 2020年3月26日
 *      Author: xwr
 */
#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>
#include <minigui/control.h>
#include "resource.h"
#include "video/video.h"
#define IDC_ST_VIGB 2001
#define IDC_ST_VIHU 2002
#define IDC_BTN_GB  3001
BITMAP goback;
BITMAP hangup;
void LoadVideoInterBmp() {
	LoadBgBmp();
	LoadWallBmp();
	LoadBitmap(HDC_SCREEN, &goback, op_bmp_name[0]);
	LoadBitmap(HDC_SCREEN, &hangup, op_bmp_name[1]);
}
void UnloadVideoInterBmp() {
	UnloadBgBmp();
	UnloadWallBmp();
	UnloadBitmap(&goback);
	UnloadBitmap(&hangup);
}
static int VideoInterProc(HWND hWnd, int message, WPARAM wParam, LPARAM lParam) {
	HDC hdc;
	switch (message) {
	case MSG_CREATE:
		LoadVideoInterBmp();
		break;
	case MSG_PAINT:
		hdc = BeginPaint(hWnd);
		FillBgBmp(hdc);
		FillWallBmp(hdc,775,400,60,80);
		EndPaint(hWnd, hdc);
		DrawVideoDisplayRect();
		break;
	case MSG_CLOSE:
		UnloadVideoInterBmp();
		DestroyMainWindow(hWnd);
		PostQuitMessage(hWnd);
		break;
	case MSG_COMMAND:
		switch(LOWORD(wParam)){
		case IDC_BTN_GB:
			WinHome(HWND_DESKTOP);
			break;
		}
		break;
	default:
		return DefaultMainWinProc(hWnd, message, wParam, lParam);
	}
	return (0);
}
static void VISNotif(HWND hwnd, int id, int nc, DWORD add_data) {
	if (nc == STN_CLICKED) {
		switch (id) {
		case IDC_ST_VIGB:
			stopPcm();
			stopVideo();
			WinHome(HWND_DESKTOP);
			break;
		case IDC_ST_VIHU:
			setPcm();
			setVideo();
			break;
		}
	}
}
void AddVIControls(HWND main) {
	HWND sgbHwnd = CreateWindowEx(CTRL_STATIC, "",
	WS_CHILD | WS_VISIBLE | SS_BITMAP | SS_REALSIZEIMAGE | SS_NOTIFY,
			WS_EX_TRANSPARENT,
			IDC_ST_VIGB, 650, 400, 124, 80, main, (DWORD) &goback);
	SetNotificationCallback(sgbHwnd, VISNotif);
	HWND shuHwnd = CreateWindowEx(CTRL_STATIC, "",
	WS_CHILD | WS_VISIBLE | SS_BITMAP | SS_REALSIZEIMAGE | SS_NOTIFY,
			WS_EX_TRANSPARENT,
			IDC_ST_VIHU, 525, 400, 124, 80, main, (DWORD) &hangup);
	SetNotificationCallback(shuHwnd, VISNotif);
//	CreateWindowEx(CTRL_BUTTON,"",WS_CHILD|WS_VISIBLE|BS_BITMAP|BS_PUSHBUTTON|BS_NOBORDER,WS_EX_TRANSPARENT,IDC_BTN_GB,397,400,124,80,main,(DWORD)&goback);
}
int WinVideoInter(HWND hosting) {
	MSG Msg;
	HWND hMainWnd;
	MAINWINCREATE CreateInfo;
	CreateInfo.dwStyle = WS_NONE;
	CreateInfo.dwExStyle = WS_EX_AUTOSECONDARYDC;
	CreateInfo.spCaption = "";
	CreateInfo.hMenu = 0;
	CreateInfo.hCursor = GetSystemCursor(0);
	CreateInfo.hIcon = 0;
	CreateInfo.MainWindowProc = VideoInterProc;
	CreateInfo.lx = 0;
	CreateInfo.ty = 0;
	CreateInfo.rx = g_rcScr.right;
	CreateInfo.by = g_rcScr.bottom;
	CreateInfo.iBkColor = PIXEL_lightgray;
	CreateInfo.dwAddData = 0;
	CreateInfo.hHosting = hosting;
	hMainWnd = CreateMainWindow(&CreateInfo);
	AddVIControls(hMainWnd);
	if (hMainWnd == HWND_INVALID)
		return -1;
	ShowWindow(hMainWnd, SW_SHOWNORMAL);

	while (GetMessage(&Msg, hMainWnd)) {
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}

	MainWindowThreadCleanup(hMainWnd);
	return 0;
}

