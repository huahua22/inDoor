/*
 * dialog.c
 *
 *  Created on: 2020年6月4日
 *      Author: xwr
 */

#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>
#include <minigui/control.h>
#include "resource.h"
#define IDC_ST_GB 10001
BITMAP go;
HWND dialogMain;
static int DialogProc(HWND hWnd, int message, WPARAM wParam, LPARAM lParam) {
	HDC hdc;
	switch (message) {
	case MSG_CREATE:
		LoadBitmap(HDC_SCREEN, &go, "./res/image/dialog_goback.png");
		break;
	case MSG_PAINT:
		hdc = BeginPaint(hWnd);
		EndPaint(hWnd, hdc);
		break;
	case MSG_CLOSE:
		UnloadBitmap(&go);
		DestroyMainWindow(hWnd);
		PostQuitMessage(hWnd);
		break;
	default:
		return DefaultMainWinProc(hWnd, message, wParam, lParam);
	}
	return (0);
}
static void DialogNotif(HWND hwnd, int id, int nc, DWORD add_data) {
	if (nc == STN_CLICKED) {
		switch (id) {
		case IDC_ST_GB:
			PostMessage(dialogMain, MSG_CLOSE, 0, 0);
			break;
		}
	}
}
void AddDialogControls(HWND main,char *str) {
	HWND sgbHwnd = CreateWindowEx(CTRL_STATIC, "",
	WS_CHILD | WS_VISIBLE | SS_BITMAP | SS_REALSIZEIMAGE | SS_NOTIFY,
			WS_EX_TRANSPARENT,
			IDC_ST_GB, 0, 0, 20, 20, main, (DWORD) &go);
	SetNotificationCallback(sgbHwnd, DialogNotif);
	 HWND txtStatic = CreateWindowEx(CTRL_STATIC, str,
	                          WS_VISIBLE | SS_CENTER | SS_NOTIFY,WS_EX_TRANSPARENT,
              50, 0,150, 220, 20,main, 0);
//	HWND txt = CreateWindow(CTRL_STATIC,"huahua",WS_VISIBLE | SS_CENTER | SS_NOTIFY,50,200,150,200,20,main,0);
}
int WinDialog(HWND hosting,char *str) {
	MSG Msg;
	MAINWINCREATE CreateInfo;
	CreateInfo.dwStyle = WS_NONE;
	CreateInfo.dwExStyle = WS_EX_AUTOSECONDARYDC;
	CreateInfo.spCaption = "";
	CreateInfo.hMenu = 0;
	CreateInfo.hCursor = GetSystemCursor(0);
	CreateInfo.hIcon = 0;
	CreateInfo.MainWindowProc = DialogProc;
	CreateInfo.lx = 250;
	CreateInfo.ty = 90;
	CreateInfo.rx = 550;
	CreateInfo.by = 390;
	CreateInfo.iBkColor = PIXEL_lightwhite;
	CreateInfo.dwAddData = 0;
	CreateInfo.hHosting = hosting;
	dialogMain = CreateMainWindow(&CreateInfo);
	AddDialogControls(dialogMain,str);
	if (dialogMain == HWND_INVALID)
		return -1;
	ShowWindow(dialogMain, SW_SHOWNORMAL);

	while (GetMessage(&Msg, dialogMain)) {
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}

	MainWindowThreadCleanup(dialogMain);
	return 0;
}


