#include <Windows.h>
#include "Font.h"
#include <atlstr.h>
#include "resource.h"
#include <string>
extern HWND g_hEdit, g_hwnd;
extern HINSTANCE hInst;
extern HWND g_hwndStatus;
extern bool needsave;
using namespace std;
void Replace(const LPCTSTR, const LPCTSTR);
void ReplaceOnce(const LPCTSTR, const LPCTSTR);
void SetWindowCenter(const HWND & hwnd);
bool FindOnce(wstring);

INT_PTR CALLBACK DlgReplaceProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {//替换窗口过程处理
	static HWND hBtn;
	HWND hEdit1;
	HWND hEdit2;


	switch (msg)
	{

	case WM_COMMAND:
	{
		if (LOWORD(wParam) == IDC_BUTTON1) {//替换全部
			TCHAR str1[1024];
			hEdit2 = GetDlgItem(hwnd, IDC_EDIT2);
			hEdit1 = GetDlgItem(hwnd, IDC_EDIT1);
			GetWindowText(hEdit1, str1, 1024);
			TCHAR str2[1024];
			GetWindowText(hEdit2, str2, 1024);
			Replace(str1, str2);
			needsave = true;
			DestroyWindow(hwnd);
		}
		else if (LOWORD(wParam) == IDCANCEL) {
			DestroyWindow(hwnd);
		}
		else if (LOWORD(wParam) == IDOK) {//替换一个
			//TODO:
			TCHAR str1[1024];
			hEdit2 = GetDlgItem(hwnd, IDC_EDIT2);
			hEdit1 = GetDlgItem(hwnd, IDC_EDIT1);
			GetWindowText(hEdit1, str1, 1024);
			TCHAR str2[1024];
			GetWindowText(hEdit2, str2, 1024);
			ReplaceOnce(str1, str2);
		}
	}
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
	return (INT_PTR)FALSE;
}

void CreateReplaceWindow() {
	HWND hdlg = CreateDialog(hInst, MAKEINTRESOURCE(IDD_DIALOG_REPLACE), g_hwnd, (DLGPROC)DlgReplaceProc);
	ShowWindow(hdlg, SW_NORMAL);
	HWND hEdit1 = GetDlgItem(hdlg, IDC_EDIT1);
	SetFocus(hEdit1);
}
void Replace(const LPCTSTR src, const LPCTSTR dest) {
	//TCHAR buf[1024];
	int size = SendMessage(g_hEdit, EM_GETLIMITTEXT, 0, 0);//分配动态的大小	
	TCHAR *buf = new TCHAR[size];
	GetWindowText(g_hEdit, buf, size);
	//wstring test(&buf[0]); 
	//string str(test.begin(), test.end()); 
	CString str(buf);
	str.Replace(src, dest);
	TCHAR *buf2 = str.GetBuffer(str.GetLength());
	//TCHAR *buf2 = (TCHAR*)str.c_str();
	SetWindowText(g_hEdit, buf2);
	MessageBox(g_hwnd, L"已完成替换！", L"成功", MB_OK | MB_ICONINFORMATION);
}

void ReplaceOnce(const LPCTSTR src, const LPCTSTR dest) {
	wstring test(src);
	if (FindOnce(test)) {
		SendMessage(g_hEdit, EM_REPLACESEL, true, (LPARAM)dest);
	}
}
//bool FindOnce(string str) {
//	static int index;
//	//TCHAR buf[1024];
//	int size = SendMessage(g_hEdit, EM_GETLIMITTEXT, 0, 0);//分配动态的大小
//	TCHAR *buf = new TCHAR[size];
//	GetWindowText(g_hEdit, buf, size);
//	wstring test(&buf[0]); //实现宽字符到string类型的转化
//	//string content(test.begin(), test.end());
//	//size_t found = content.find(str);
//	size_t found = content.find_first_of(str, index);
//	if (found == string::npos) {
//		wsprintf(buf, L"没有找到 %s", str);
//		MessageBox(g_hwnd, buf, L"找不到内容", MB_OK | MB_ICONERROR);
//		SetWindowText(g_hwndStatus, buf);
//		index = 0;
//		return false;
//	}
//	else {
//		wsprintf(buf, L"在 %d 找到 %s", found, str);
//		//MessageBox(g_hwnd, buf, L"找到内容", MB_OK | MB_ICONINFORMATION);
//		SetWindowText(g_hwndStatus, buf);
//		index = found + 1;
//		SetFocus(g_hEdit);//获取焦点后再选中
//		SendMessage(g_hEdit, EM_SETSEL, found, found + str.length());
//		return true;
//	}
//}
bool FindOnce(wstring str) {
	static int index;
	static wstring last;
	if (last != str && index != 0) {
		index = 0;
		last = str;
	}//不同字符时从起始位置开始查找
	else {
		last = str;
	}
	//TCHAR buf[1024];
	int size = SendMessage(g_hEdit, EM_GETLIMITTEXT, 0, 0);//分配动态的大小
	TCHAR *buf = new TCHAR[size];
	GetWindowText(g_hEdit, buf, size);
	wstring test(buf); //实现宽字符到wstring类型的转化
					   //string content(test.begin(), test.end());
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
		needsave = false;
		return true;
	}
}
