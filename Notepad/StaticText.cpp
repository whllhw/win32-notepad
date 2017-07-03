#include "StaticText.h"
//已弃用
StaticText::StaticText(HWND hwnd,HINSTANCE hInst){
	hStatic = CreateWindow(
		L"static", //静态文本框的类名
		L"C语言中文网",  //控件的文本
		WS_CHILD /*子窗口*/ | WS_VISIBLE /*创建时显示*/ | WS_BORDER /*带边框*/ | SS_CENTER /*水平居中*/ | SS_CENTERIMAGE /*垂直居中*/,
		20 /*X坐标*/, 20 /*Y坐标*/, 200 /*宽度*/, 100 /*高度*/,
		hwnd,  //父窗口句柄
		(HMENU)1,  //为控件指定一个唯一标识符
		hInst,  //当前程序实例句柄
		NULL
	);
}


StaticText::~StaticText()
{
}
