#include <Windows.h>
#include <atlstr.h>
#include "Font.h"
#include <string>
#include <Richedit.h>
#include "resource.h"
//TODO Messagbox出现乱码！已经解决
using namespace std;

extern HWND g_hEdit, g_hwnd;
extern HINSTANCE hInst;
extern HWND g_hwndStatus;
bool Find(wstring);

void SetWindowCenter(const HWND & hwnd);

INT_PTR CALLBACK DlgFindProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	static HWND hBtn;
	static HWND hEdit1;

	switch (msg)
	{
		/*case WM_CTLCOLORSTATIC:
			return (INT_PTR)GetStockObject(NULL_BRUSH);
			break;*/
			//case WM_CREATE: {
			//	hBtn = CreateWindow(
			//		TEXT("button"),
			//		TEXT("查找"),
			//		WS_CHILD | WS_VISIBLE | SS_CENTER | WS_BORDER,
			//		140, 210, 133, 30,
			//		hwnd,
			//		(HMENU)1,
			//		hInst,
			//		NULL
			//	);

			//	HWND hStatic1 = CreateWindow(

			//		L"static", //静态文本框的类名
			//		L"要查找的文本",  //控件的文本
			//		WS_CHILD /*子窗口*/ | WS_VISIBLE /*创建时显示*/,//| WS_BORDER /*带边框*/ | SS_CENTER /*水平居中*/ | SS_CENTERIMAGE /*垂直居中*/,
			//		100, 30, 191, 51,
			//		hwnd,  //父窗口句柄
			//		(HMENU)2,  //为控件指定一个唯一标识符
			//		hInst,  //当前程序实例句柄
			//		NULL
			//	);

			//	hEdit1 = CreateWindow(
			//		L"edit", //静态文本框的类名
			//		L"",  //控件的文本
			//		WS_CHILD /*子窗口*/ | WS_VISIBLE /*创建时显示*/,//| WS_BORDER /*带边框*/ | SS_CENTER /*水平居中*/ | SS_CENTERIMAGE /*垂直居中*/,
			//		100, 90, 211, 30,
			//		hwnd,  //父窗口句柄
			//		(HMENU)4,  //为控件指定一个唯一标识符
			//		hInst,  //当前程序实例句柄
			//		NULL
			//	);
			//	Font font;
			//	font.setFont(hEdit1);
			//	font.setFont(hStatic1);
			//	font.setFont(hBtn);
			//}
			//				break;
	case WM_COMMAND:
	{
		if (LOWORD(wParam) == IDOK) {
			hEdit1 = GetDlgItem(hwnd, IDC_EDIT1);
			TCHAR str1[1024];
			GetWindowTextW(hEdit1, str1, 1024);
			wstring test(str1);
			//string str(test.begin(), test.end());
			if (!Find(test)) {
				DestroyWindow(hwnd);
			}
		}
		else if (LOWORD(wParam) == IDCANCEL) {
			DestroyWindow(hwnd);
		}
	}	break;
	//case WM_KEYDOWN://无效！！
	//	if (wParam == VK_RETURN) {
	//		MessageBoxA(hwnd, "return", "", MB_OK);
	//	}
	//	/*for (int i = 0; i < (int)LOWORD(lParam); i++)
	//	{
	//		switch (LOWORD(wParam))
	//		{
	//		case '\n':
	//			MessageBoxA(hwnd, "return", "", MB_OK);
	//		}
	//	}*/break;
	case WM_DESTROY:
		SetWindowTextA(g_hwndStatus, "");
		break;
	case WM_SYSCOMMAND:
		if (wParam == SC_CLOSE)
		{
			// 如果执行了关闭  
			// 销毁对话框，将收到WM_DESTROY消息  
			DestroyWindow(hwnd);
		}
		return 0;
	default:
		break;
	}
	//return DefWindowProc(hwnd, msg, wParam, lParam); 不能使用
	return (INT_PTR)FALSE;
}

void CreateFindWindow() {
	HWND hdlg = CreateDialog(hInst, MAKEINTRESOURCE(IDD_DIALOG_FIND), g_hwnd, (DLGPROC)DlgFindProc);
	ShowWindow(hdlg, SW_NORMAL);
	HWND hEdit1 = GetDlgItem(hdlg, IDC_EDIT1);
	SetFocus(hEdit1);
}
bool Find(wstring str) {
	static int index;
	static wstring last;
	if (last != str && index != 0) {
		index = 0;
		last = str;
	}//不同字符时从起始位置开始查找
	else {
		last = str;
	}
	int size = SendMessage(g_hEdit, EM_GETLIMITTEXT, 0, 0);//分配动态的大小
	TCHAR *buf = new TCHAR[size];
	GetWindowText(g_hEdit, buf, size);
	wstring test(buf); 
	size_t found = test.find(str, index);
	if (found == wstring::npos || found == index) {
		wsprintf(buf, L"没有找到 %s", str.c_str());
		MessageBox(g_hwnd, buf, L"找不到内容", MB_OK | MB_ICONERROR);
		SetWindowText(g_hwndStatus, buf);
		index = 0;
		return false;
	}
	else {
		wsprintf(buf, L"在 %d 找到 %s", found, str.c_str());
		//MessageBox(g_hwnd, buf, L"找到内容", MB_OK | MB_ICONINFORMATION);
		SetWindowText(g_hwndStatus, buf);
		index = found + str.length();
		SetFocus(g_hEdit);//获取焦点后再选中
		SendMessage(g_hEdit, EM_SETSEL, found, found + str.length());
		SendMessage(g_hEdit, EM_SCROLLCARET, 0, 0);//把可见范围移至光标处
		//EM_SCROLL(&HB5=181),*,0 //文本垂直滚动。第三个参数*控制滚动方向:SB_LINEDOWN(1)向下滚动一行，SB_LINEUP(0)向上滚动一行，SB_PAGEDOWN(3)向下滚动一页，SB_PAGEUP(2)向上滚动一页。
		return true;
	}
}
