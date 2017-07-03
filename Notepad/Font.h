#pragma once
#include <Windows.h>
class Font
{
public:
	Font();
	HFONT hFont;
	void setFont(HWND);
};

