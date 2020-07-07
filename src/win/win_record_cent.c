#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>
#include <minigui/control.h>
#include "resource.h"
#define IDC_ST_RC_COM_INFO 1001
#define IDC_ST_RC_SEC 1002
#define IDC_ST_RC_CALL 1003
#define IDC_ST_RC_TAKE_PHOTO 1004
#define IDC_ST_RC_PHONE 1005
#define IDC_ST_RC_PHOTO_MSG 1006
#define IDC_ST_RCGB 1007
BITMAP goback;
BITMAP comInfo;
BITMAP sec;
BITMAP call;
BITMAP takePhoto;
BITMAP phone;
BITMAP photoMsg;
void LoadRecordCentBmp() {
	LoadBgBmp();
	LoadWallBmp();
	LoadBitmap(HDC_SCREEN, &comInfo, rc_bmp_name[0]);
	LoadBitmap(HDC_SCREEN, &sec, rc_bmp_name[1]);
	LoadBitmap(HDC_SCREEN, &call, rc_bmp_name[2]);
	LoadBitmap(HDC_SCREEN, &takePhoto, rc_bmp_name[3]);
	LoadBitmap(HDC_SCREEN, &phone, rc_bmp_name[4]);
	LoadBitmap(HDC_SCREEN, &photoMsg, rc_bmp_name[5]);
	LoadBitmap(HDC_SCREEN, &goback, op_bmp_name[0]);
}
void UnloadRecordCentBmp() {
	UnloadBgBmp();
	UnloadWallBmp();
	UnloadBitmap(&goback);
	UnloadBitmap(&comInfo);
	UnloadBitmap(&sec);
	UnloadBitmap(&call);
	UnloadBitmap(&takePhoto);
	UnloadBitmap(&phone);
	UnloadBitmap(&photoMsg);
}
static int RecordCentProc(HWND hWnd, int message, WPARAM wParam, LPARAM lParam) {
	HDC hdc;
	switch (message) {
	case MSG_CREATE:
		LoadRecordCentBmp();
		break;
	case MSG_PAINT:
		hdc = BeginPaint(hWnd);
		FillBgBmp(hdc);
		FillWallBmp(hdc, 775, 400, 60, 80);
		EndPaint(hWnd, hdc);
		break;
	case MSG_CLOSE:
		UnloadRecordCentBmp();
		DestroyMainWindow(hWnd);
		PostQuitMessage(hWnd);
		break;
	case MSG_COMMAND:
		break;
	default:
		return DefaultMainWinProc(hWnd, message, wParam, lParam);
	}
	return (0);
}
static void RCSNotif(HWND hwnd, int id, int nc, DWORD add_data) {
	if (nc == STN_CLICKED) {
		switch (id) {
		case IDC_ST_RCGB:
			WinHome(HWND_DESKTOP);
			break;
		}
	}
}
void AddRCControls(HWND main) {
	//小区信息
	HWND scfHwnd = CreateWindowEx(CTRL_STATIC, "",
	WS_CHILD | WS_VISIBLE | SS_BITMAP | SS_REALSIZEIMAGE | SS_NOTIFY,
	WS_EX_TRANSPARENT,
	IDC_ST_RC_COM_INFO, 142, 75, 168, 140, main, (DWORD) &comInfo);
	SetNotificationCallback(scfHwnd, RCSNotif);
	//安防信息
	HWND ssecHwnd = CreateWindowEx(CTRL_STATIC, "",
	WS_CHILD | WS_VISIBLE | SS_BITMAP | SS_REALSIZEIMAGE | SS_NOTIFY,
	WS_EX_TRANSPARENT,
	IDC_ST_RC_SEC, 316, 75, 168, 140, main, (DWORD) &sec);
	SetNotificationCallback(ssecHwnd, RCSNotif);
	//报警记录
	HWND scallHwnd = CreateWindowEx(CTRL_STATIC, "",
	WS_CHILD | WS_VISIBLE | SS_BITMAP | SS_REALSIZEIMAGE | SS_NOTIFY,
	WS_EX_TRANSPARENT,
	IDC_ST_RC_CALL, 490, 75, 168, 140, main, (DWORD) &call);
	SetNotificationCallback(scallHwnd, RCSNotif);

	HWND stpHwnd = CreateWindowEx(CTRL_STATIC, "",
	WS_CHILD | WS_VISIBLE | SS_BITMAP | SS_REALSIZEIMAGE | SS_NOTIFY,
	WS_EX_TRANSPARENT,
	IDC_ST_RC_TAKE_PHOTO, 142, 221, 168, 140, main, (DWORD) &takePhoto);
	SetNotificationCallback(stpHwnd, RCSNotif);

	HWND sphoneHwnd = CreateWindowEx(CTRL_STATIC, "",
	WS_CHILD | WS_VISIBLE | SS_BITMAP | SS_REALSIZEIMAGE | SS_NOTIFY,
	WS_EX_TRANSPARENT,
	IDC_ST_RC_SEC, 316, 221, 168, 140, main, (DWORD) &phone);
	SetNotificationCallback(sphoneHwnd, RCSNotif);

	HWND spmHwnd = CreateWindowEx(CTRL_STATIC, "",
	WS_CHILD | WS_VISIBLE | SS_BITMAP | SS_REALSIZEIMAGE | SS_NOTIFY,
	WS_EX_TRANSPARENT,
	IDC_ST_RC_PHOTO_MSG, 490, 221, 168, 140, main, (DWORD) &photoMsg);
	SetNotificationCallback(spmHwnd, RCSNotif);

	HWND sgbHwnd = CreateWindowEx(CTRL_STATIC, "",
	WS_CHILD | WS_VISIBLE | SS_BITMAP | SS_REALSIZEIMAGE | SS_NOTIFY,
	WS_EX_TRANSPARENT,
	IDC_ST_RCGB, 650, 400, 124, 80, main, (DWORD) &goback);
	SetNotificationCallback(sgbHwnd, RCSNotif);
}
int WinRecordCent(HWND hosting) {
	MSG Msg;
	HWND hMainWnd;
	MAINWINCREATE CreateInfo;
	CreateInfo.dwStyle = WS_NONE;
	CreateInfo.dwExStyle = WS_EX_AUTOSECONDARYDC;
	CreateInfo.spCaption = "";
	CreateInfo.hMenu = 0;
	CreateInfo.hCursor = GetSystemCursor(0);
	CreateInfo.hIcon = 0;
	CreateInfo.MainWindowProc = RecordCentProc;
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

