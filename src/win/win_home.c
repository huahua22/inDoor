/*
 ============================================================================
 Name        : 0.c
 Author      : xwr
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */
#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>
#include <minigui/control.h>
#include "resource.h"
//extern int receive_video;
HWND hMainWnd;
#define IDC_ST_HRC 1001
#define IDC_ST_HOC 1002
#define IDC_ST_HRO 1003
#define IDC_ST_HSH 1004
#define IDC_ST_HVI 1005
#define IDC_ST_HFC 1006
#define IDC_ST_HOA 1007
#define IDC_ST_HTNET 1008
#define IDC_ST_HTSECUR 1009
#define IDC_ST_HTPIC 1010
#define IDC_ST_HTMSG 1011
#define IDC_ST_HTCALL 1012
#define IDC_ST_HIC 1013
#define IDC_ST_HCC 1014
#define IDC_ST_HUS 1015
#define IDC_ST_HSS 1016
#define IDC_ST_HBM 1017
#define IDC_ST_HCI 1018

BITMAP rcbmp;
BITMAP robmp;
BITMAP ocbmp;
BITMAP tbbmp;
BITMAP fcbmp;
BITMAP vibmp;
BITMAP shbmp;
BITMAP oabmp;
BITMAP tb;
BITMAP tnet;
BITMAP tsecur;
BITMAP tpic;
BITMAP tmsg;
BITMAP tcall;
BITMAP hic;
BITMAP hbm;
BITMAP hci;
BITMAP hcc;
BITMAP hus;
BITMAP hss;
BITMAP h_rec_cent;
void LoadHomeBmp() {
	LoadBgBmp();
	LoadWallBmp();
	LoadBitmap(HDC_SCREEN, &h_rec_cent, h_bmp_name_clicked[0]);
	LoadBitmap(HDC_SCREEN, &rcbmp, h_bmp_name[0]);
	LoadBitmap(HDC_SCREEN, &ocbmp, h_bmp_name[1]);
	LoadBitmap(HDC_SCREEN, &robmp, h_bmp_name[2]);
	LoadBitmap(HDC_SCREEN, &tbbmp, h_bmp_name[3]);
	LoadBitmap(HDC_SCREEN, &shbmp, h_bmp_name[4]);
	LoadBitmap(HDC_SCREEN, &vibmp, h_bmp_name[5]);
	LoadBitmap(HDC_SCREEN, &fcbmp, h_bmp_name[6]);
	LoadBitmap(HDC_SCREEN, &oabmp, h_bmp_name[7]);
	LoadBitmap(HDC_SCREEN, &tb, h_tbmp_name[0]);
	LoadBitmap(HDC_SCREEN, &tnet, h_tbmp_name[1]);
	LoadBitmap(HDC_SCREEN, &tsecur, h_tbmp_name[2]);
	LoadBitmap(HDC_SCREEN, &tpic, h_tbmp_name[3]);
	LoadBitmap(HDC_SCREEN, &tmsg, h_tbmp_name[4]);
	LoadBitmap(HDC_SCREEN, &tcall, h_tbmp_name[5]);
	LoadBitmap(HDC_SCREEN, &hic, h_bbmp_name[0]);
	LoadBitmap(HDC_SCREEN, &hbm, h_bbmp_name[1]);
	LoadBitmap(HDC_SCREEN, &hci, h_bbmp_name[2]);
	LoadBitmap(HDC_SCREEN, &hcc, h_bbmp_name[3]);
	LoadBitmap(HDC_SCREEN, &hus, h_bbmp_name[4]);
	LoadBitmap(HDC_SCREEN, &hss, h_bbmp_name[5]);
}
void UnloadHomeBmp() {
	UnloadBgBmp();
	UnloadWallBmp();
	UnloadBitmap(&h_rec_cent);
	UnloadBitmap(&rcbmp);
	UnloadBitmap(&ocbmp);
	UnloadBitmap(&robmp);
	UnloadBitmap(&tbbmp);
	UnloadBitmap(&shbmp);
	UnloadBitmap(&vibmp);
	UnloadBitmap(&fcbmp);
	UnloadBitmap(&oabmp);

	UnloadBitmap(&tb);
	UnloadBitmap(&tnet);
	UnloadBitmap(&tsecur);
	UnloadBitmap(&tpic);
	UnloadBitmap(&tmsg);
	UnloadBitmap(&tcall);

	UnloadBitmap(&hic);
	UnloadBitmap(&hbm);
	UnloadBitmap(&hci);
	UnloadBitmap(&hcc);
	UnloadBitmap(&hus);
	UnloadBitmap(&hss);
}
static int WinProc(HWND hWnd, int message, WPARAM wParam, LPARAM lParam) {
	HDC hdc;
	RECT rc;
	GetClientRect(hWnd, &rc);
	switch (message) {
	case MSG_CREATE:
		LoadHomeBmp();
		break;
	case MSG_PAINT:
		hdc = BeginPaint(hWnd);
		FillBgBmp(hdc);
		FillBoxWithBitmap(hdc, 169, 100, 204, 274, &tbbmp);
		FillBoxWithBitmap(hdc, 0, 0, 800, 38, &tb);
		FillWallBmp(hdc, 0, 416, 25, 64);
		FillWallBmp(hdc, 776, 416, 28, 64);
		EndPaint(hWnd, hdc);
		break;
	case MSG_CLOSE:
		UnloadHomeBmp();
		DestroyMainWindow(hWnd);
		PostQuitMessage(hWnd);
		break;
	default:
		return DefaultMainWinProc(hWnd, message, wParam, lParam);
	}
	return (0);
}
int InitMainWindow(HWND hosting) {
	MAINWINCREATE window_info;
	window_info.dwStyle = WS_VISIBLE;
	window_info.dwExStyle = WS_EX_NONE;
	window_info.spCaption = "";
	window_info.hMenu = 0;
	window_info.hCursor = GetSystemCursor(0);
	window_info.hIcon = 0;
	window_info.MainWindowProc = WinProc;
	window_info.lx = WINDOW_LX;
	window_info.ty = WINDOW_TY;
	window_info.rx = WINDOW_RX;
	window_info.by = WINDOW_RY;
	window_info.iBkColor = COLOR_darkgreen;
	window_info.dwAddData = 0;
	window_info.hHosting = hosting;
	hMainWnd = CreateMainWindow(&window_info);
	CreateHomeStatic();
	if (hMainWnd == HWND_INVALID)
		return 0;
	else
		return 1;
}
static void HNotif(HWND hwnd, int id, int nc, DWORD add_data) {
	if (nc == STN_CLICKED) {
		switch (id) {
		case IDC_ST_HVI:
			WinVideoInter(HWND_DESKTOP);
			break;
		case IDC_ST_HRC:
			SetWindowAdditionalData2(hwnd,(DWORD)&h_rec_cent);
			UpdateWindow(hwnd,TRUE );
//			printf("recond center\n");
//			WinRecordCent(HWND_DESKTOP);
			WinDialog(HWND_DESKTOP,"huahua");
			break;
		case IDC_ST_HSH:
			WinSmartHome(HWND_DESKTOP);
			break;
		case IDC_ST_HIC:
			WinMonitCent(HWND_DESKTOP);
			break;
		case IDC_ST_HFC:
			WinFamilySec(HWND_DESKTOP);
			break;
		case IDC_ST_HSS:
			WinSysSet(HWND_DESKTOP);
			break;
		case IDC_ST_HUS:
			WinUserSet(HWND_DESKTOP);
			break;
		}

//		PostMessage(hMainWnd, MSG_CLOSE, 0, 0);
	}
}
void CreateHomeStatic() {
	HWND sviHwnd = CreateWindowEx(CTRL_STATIC, "",
	WS_CHILD | WS_VISIBLE | SS_BITMAP | SS_REALSIZEIMAGE | SS_NOTIFY,
	WS_EX_TRANSPARENT,
	IDC_ST_HVI, 509, 100, 250, 133, hMainWnd, (DWORD) &vibmp);
	SetNotificationCallback(sviHwnd, HNotif);
	HWND srcHwnd = CreateWindowEx(CTRL_STATIC, "",
	WS_CHILD | WS_VISIBLE | SS_BITMAP | SS_REALSIZEIMAGE | SS_NOTIFY,
	WS_EX_TRANSPARENT,
	IDC_ST_HRC, 43, 100, 116, 86, hMainWnd, (DWORD) &rcbmp);
	SetNotificationCallback(srcHwnd, HNotif);


	HWND socHwnd = CreateWindowEx(CTRL_STATIC, "",
	WS_CHILD | WS_VISIBLE | SS_BITMAP | SS_REALSIZEIMAGE | SS_NOTIFY,
	WS_EX_TRANSPARENT,
	IDC_ST_HOC, 43, 196, 116, 86, hMainWnd, (DWORD) &ocbmp);
	SetNotificationCallback(socHwnd, HNotif);
	HWND sroHwnd = CreateWindowEx(CTRL_STATIC, "",
	WS_CHILD | WS_VISIBLE | SS_BITMAP | SS_REALSIZEIMAGE | SS_NOTIFY,
	WS_EX_TRANSPARENT,
	IDC_ST_HRO, 43, 292, 116, 86, hMainWnd, (DWORD) &robmp);
	SetNotificationCallback(sroHwnd, HNotif);

	HWND sshHwnd = CreateWindowEx(CTRL_STATIC, "",
	WS_CHILD | WS_VISIBLE | SS_BITMAP | SS_REALSIZEIMAGE | SS_NOTIFY,
	WS_EX_TRANSPARENT,
	IDC_ST_HSH, 383, 100, 116, 133, hMainWnd, (DWORD) &shbmp);
	SetNotificationCallback(sshHwnd, HNotif);
	HWND sfcHwnd = CreateWindowEx(CTRL_STATIC, "",
	WS_CHILD | WS_VISIBLE | SS_BITMAP | SS_REALSIZEIMAGE | SS_NOTIFY,
	WS_EX_TRANSPARENT,
	IDC_ST_HFC, 383, 243, 250, 133, hMainWnd, (DWORD) &fcbmp);
	SetNotificationCallback(sfcHwnd, HNotif);
	HWND soaHwnd = CreateWindowEx(CTRL_STATIC, "",
	WS_CHILD | WS_VISIBLE | SS_BITMAP | SS_REALSIZEIMAGE | SS_NOTIFY,
	WS_EX_TRANSPARENT,
	IDC_ST_HOA, 643, 243, 116, 133, hMainWnd, (DWORD) &oabmp);
	SetNotificationCallback(soaHwnd, HNotif);

	HWND stnetHwnd = CreateWindowEx(CTRL_STATIC, "",
	WS_CHILD | WS_VISIBLE | SS_BITMAP | SS_REALSIZEIMAGE | SS_NOTIFY,
	WS_EX_TRANSPARENT,
	IDC_ST_HTNET, 10, 0, 33, 38, hMainWnd, (DWORD) &tnet);
	SetNotificationCallback(stnetHwnd, HNotif);
	HWND stsecurHwnd = CreateWindowEx(CTRL_STATIC, "",
	WS_CHILD | WS_VISIBLE | SS_BITMAP | SS_REALSIZEIMAGE | SS_NOTIFY,
	WS_EX_TRANSPARENT,
	IDC_ST_HTSECUR, 53, 0, 33, 38, hMainWnd, (DWORD) &tsecur);
	SetNotificationCallback(stsecurHwnd, HNotif);
	HWND stpicHwnd = CreateWindowEx(CTRL_STATIC, "",
	WS_CHILD | WS_VISIBLE | SS_BITMAP | SS_REALSIZEIMAGE | SS_NOTIFY,
	WS_EX_TRANSPARENT,
	IDC_ST_HTPIC, 96, 0, 33, 38, hMainWnd, (DWORD) &tpic);
	SetNotificationCallback(stpicHwnd, HNotif);
	HWND stmsgHwnd = CreateWindowEx(CTRL_STATIC, "",
	WS_CHILD | WS_VISIBLE | SS_BITMAP | SS_REALSIZEIMAGE | SS_NOTIFY,
	WS_EX_TRANSPARENT,
	IDC_ST_HTMSG, 139, 0, 33, 38, hMainWnd, (DWORD) &tmsg);
	SetNotificationCallback(stmsgHwnd, HNotif);
	HWND stcallHwnd = CreateWindowEx(CTRL_STATIC, "",
	WS_CHILD | WS_VISIBLE | SS_BITMAP | SS_REALSIZEIMAGE | SS_NOTIFY,
	WS_EX_TRANSPARENT,
	IDC_ST_HTCALL, 180, 0, 33, 38, hMainWnd, (DWORD) &tcall);
	SetNotificationCallback(stcallHwnd, HNotif);
	HWND shicHwnd = CreateWindowEx(CTRL_STATIC, "",
	WS_CHILD | WS_VISIBLE | SS_BITMAP | SS_REALSIZEIMAGE | SS_NOTIFY,
	WS_EX_TRANSPARENT,
	IDC_ST_HIC, 26, 416, 124, 64, hMainWnd, (DWORD) &hic);
	SetNotificationCallback(shicHwnd, HNotif);
	HWND shbmHwnd = CreateWindowEx(CTRL_STATIC, "",
	WS_CHILD | WS_VISIBLE | SS_BITMAP | SS_REALSIZEIMAGE | SS_NOTIFY,
	WS_EX_TRANSPARENT,
	IDC_ST_HBM, 151, 416, 124, 64, hMainWnd, (DWORD) &hbm);
	SetNotificationCallback(shbmHwnd, HNotif);
	HWND shcimHwnd = CreateWindowEx(CTRL_STATIC, "",
	WS_CHILD | WS_VISIBLE | SS_BITMAP | SS_REALSIZEIMAGE | SS_NOTIFY,
	WS_EX_TRANSPARENT,
	IDC_ST_HCI, 276, 416, 124, 64, hMainWnd, (DWORD) &hci);
	SetNotificationCallback(shcimHwnd, HNotif);
	HWND shccmHwnd = CreateWindowEx(CTRL_STATIC, "",
	WS_CHILD | WS_VISIBLE | SS_BITMAP | SS_REALSIZEIMAGE | SS_NOTIFY,
	WS_EX_TRANSPARENT,
	IDC_ST_HCI, 401, 416, 124, 64, hMainWnd, (DWORD) &hcc);
	SetNotificationCallback(shccmHwnd, HNotif);
	HWND shusmHwnd = CreateWindowEx(CTRL_STATIC, "",
	WS_CHILD | WS_VISIBLE | SS_BITMAP | SS_REALSIZEIMAGE | SS_NOTIFY,
	WS_EX_TRANSPARENT,
	IDC_ST_HUS, 526, 416, 124, 64, hMainWnd, (DWORD) &hus);
	SetNotificationCallback(shusmHwnd, HNotif);
	HWND sHmHwnd = CreateWindowEx(CTRL_STATIC, "",
	WS_CHILD | WS_VISIBLE | SS_BITMAP | SS_REALSIZEIMAGE | SS_NOTIFY,
	WS_EX_TRANSPARENT,
	IDC_ST_HSS, 651, 416, 124, 64, hMainWnd, (DWORD) &hus);
	SetNotificationCallback(shusmHwnd, HNotif);

}

int WinHome(HWND hosting) {
	MSG Msg;
	InitMainWindow(hosting);
	ShowWindow(hMainWnd, SW_SHOWNORMAL);
	while (GetMessage(&Msg, hMainWnd)) {
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
//		if (receive_video == 1) {
//			PostMessage(hMainWnd, MSG_CLOSE, 0, 0);
//			WinVideoInter(HWND_DESKTOP);
//			receive_video = 0;
//		}
	}
	MainWindowThreadCleanup(hMainWnd);
	return (0);
}
