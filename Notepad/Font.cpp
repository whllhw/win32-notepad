#include "Font.h"

Font::Font() {
	hFont = CreateFont(20/*高度*/, 0/*宽度*/, 0, 0, 400 /*一般这个值设为400*/,
		FALSE/*不带斜体*/, FALSE/*不带下划线*/, FALSE/*不带删除线*/,
		DEFAULT_CHARSET,  //这里我们使用默认字符集，还有其他以 _CHARSET 结尾的常量可用
		OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS,  //这行参数不用管
		DEFAULT_QUALITY,  //默认输出质量
		FF_DONTCARE,  //不指定字体族*/
		L"宋体"  //字体名
	);
}

void Font::setFont(HWND hBtn) {
	SendMessage(hBtn, WM_SETFONT,
		(WPARAM)hFont, NULL);
}
