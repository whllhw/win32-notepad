//ÒÑÆúÓÃ
#include "Button.h"

Button::Button(HWND hwnd, HINSTANCE hInst) {
	hBtn = CreateWindow(
		TEXT("button"),
		TEXT("µã»÷"),
		WS_CHILD | WS_VISIBLE | SS_CENTER | WS_BORDER,
		100, 100, 100, 100,
		hwnd,
		(HMENU)2,
		hInst,
		NULL
	);
}