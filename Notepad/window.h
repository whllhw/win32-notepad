#pragma once
#include <Windows.h>
#define IDM_SAVE     301  
#define IDM_SAVEAS   302  
#define IDM_EXIT     303
#define IDM_FIND     304
#define IDM_REPLACE  305
#define IDM_CUT      306
#define IDM_COPY     307
#define IDM_PASTE    308
#define IDM_OPEN     309

#define IDC_EDIT     201
#define IDC_STATUS   202
class Window {
public:
	friend LRESULT CALLBACK  WndProc(HWND, UINT, WPARAM, LPARAM);
	static HINSTANCE Hinst;
	HINSTANCE hInst;
	HWND     hwnd;
	int iCmdShow;
	MSG msg;
	const TCHAR *szClassName;
	HMENU hRoot;

	void AddMenu();
	const void RegisterW(TCHAR szClassName[]);
	void CreateW();
	void ShowW();
	void UpdateW();
	WPARAM exec();

	void KeyDown(HWND hwnd);

	Window(HINSTANCE hInstance,
		HINSTANCE hPrevInstance,
		PSTR szCmdLine,
		int iCmdShow) :iCmdShow(iCmdShow), hInst(hInstance) {}
};