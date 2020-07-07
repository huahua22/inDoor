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
#define IDC_ST_MCGB 2001
BITMAP goback;
void LoadMonitCentBmp() {
	LoadBgBmp();
	LoadWallBmp();
	LoadBitmap(HDC_SCREEN, &goback, op_bmp_name[0]);
}
void UnloadMonitCentBmp() {
	UnloadBgBmp();
	UnloadWallBmp();
	UnloadBitmap(&goback);
}
static int MonitCentProc(HWND hWnd, int message, WPARAM wParam, LPARAM lParam) {
	HDC hdc;
	switch (message) {
	case MSG_CREATE:
		LoadMonitCentBmp();
		break;
	case MSG_PAINT:
		hdc = BeginPaint(hWnd);
		FillBgBmp(hdc);
		FillWallBmp(hdc,775,400,60,80);
		EndPaint(hWnd, hdc);
		break;
	case MSG_CLOSE:
		UnloadMonitCentBmp();
		DestroyMainWindow(hWnd);
		PostQuitMessage(hWnd);
		break;
	default:
		return DefaultMainWinProc(hWnd, message, wParam, lParam);
	}
	return (0);
}
static void MCSNotif(HWND hwnd, int id, int nc, DWORD add_data) {
	if (nc == STN_CLICKED) {
		switch (id) {
		case IDC_ST_MCGB:
			WinHome(HWND_DESKTOP);
			break;
		}
	}
}
void AddMCControls(HWND main) {
	HWND sgbHwnd = CreateWindowEx(CTRL_STATIC, "",
	WS_CHILD | WS_VISIBLE | SS_BITMAP | SS_REALSIZEIMAGE | SS_NOTIFY,
			WS_EX_TRANSPARENT,
			IDC_ST_MCGB, 650, 400, 124, 80, main, (DWORD) &goback);
	SetNotificationCallback(sgbHwnd, MCSNotif);
}
int WinMonitCent(HWND hosting) {
	MSG Msg;
	HWND hMainWnd;
	MAINWINCREATE CreateInfo;
	CreateInfo.dwStyle = WS_NONE;
	CreateInfo.dwExStyle = WS_EX_AUTOSECONDARYDC;
	CreateInfo.spCaption = "";
	CreateInfo.hMenu = 0;
	CreateInfo.hCursor = GetSystemCursor(0);
	CreateInfo.hIcon = 0;
	CreateInfo.MainWindowProc = MonitCentProc;
	CreateInfo.lx = 0;
	CreateInfo.ty = 0;
	CreateInfo.rx = g_rcScr.right;
	CreateInfo.by = g_rcScr.bottom;
	CreateInfo.iBkColor = PIXEL_lightgray;
	CreateInfo.dwAddData = 0;
	CreateInfo.hHosting = hosting;
	hMainWnd = CreateMainWindow(&CreateInfo);
	AddMCControls(hMainWnd);
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

