#include "window.h"
#include "Button.h"
#include "Font.h"
#include "StaticText.h"
#include <fstream>
#include <string>
#include <atlstr.h>
#include <streambuf>
#include <commctrl.h>  
//#pragma  comment(lib,"comctl32.lib")  

using namespace std;
HINSTANCE hInst;//当前程序句柄
HWND g_hEdit, g_hwnd, g_hwndStatus;//保存全局 edit句柄，窗口句柄
TCHAR strTitle[] = L"NotePad 1.0 [Untitled.txt]";//标题名字
TCHAR curfile[MAX_PATH] = L"Untitled.txt";//保存文件路径
bool isopened = false;
bool needsave = false;

void LoadFileToEdit();

void SaveTextFileFromEdit();

void checksave();

void Replace(const LPCTSTR, const LPCTSTR);

void Find(string);

bool CreateFileWindow();

void SetWindowCenter(const HWND & hwnd);

void CreateReplaceWindow();

void CreateFindWindow();

//INT_PTR CALLBACK DlgProc(HWND hdlg, UINT msg, WPARAM wParam, LPARAM lParam)//对话框保存消息过程
//{
//	HWND hwnd = hdlg;
//	static HWND hBtn,hEdit;
//	//static HBRUSH hBrush;
//	switch (msg)
//	{
//	case WM_CTLCOLORSTATIC:
//		return (INT_PTR)GetStockObject(NULL_BRUSH);
//		break;
//	case WM_COMMAND:
//		if (LOWORD(wParam) == 1) {
//			TCHAR buf[MAX_PATH];
//			TCHAR s[MAX_PATH];
//			GetWindowText(hEdit, buf, MAX_PATH);
//			wsprintf(s, L"NotePad 1.0 [%s]", buf);//设置窗口标题
//			SetWindowText(g_hwnd, s);
//			wsprintf(curfile,buf);
//			ifstream in(curfile);
//			if (in) {
//				TCHAR tmp[MAX_PATH];
//				wsprintf(tmp, L"%s 文件已经存在，覆盖？",curfile);
//				int res = MessageBox(hwnd, tmp, L"警告", MB_ICONINFORMATION | MB_OKCANCEL);
//				in.close();
//				if (res != IDOK) {
//					break;
//				}
//			}
//			DestroyWindow(hdlg);
//		}
//		break;
//	case WM_CREATE://TODO: 打开，试图建立一个通用的窗口，完善程序逻辑
//	{
//		//hBrush = CreateSolidBrush(RGB(0x41, 0x96, 0x4F));
//		hBtn = CreateWindow(
//			TEXT("button"),
//			TEXT("确定"),
//			WS_CHILD | WS_VISIBLE | SS_CENTER | WS_BORDER,
//			70, 90, 133, 23,
//			hwnd,
//			(HMENU)1,
//			hInst,
//			NULL
//		);
//
//		HWND hStatic = CreateWindow(
//			L"static", //静态文本框的类名
//			L"要保存的文件名：",  //控件的文本
//			WS_CHILD /*子窗口*/ | WS_VISIBLE /*创建时显示*/ |  SS_CENTER /*水平居中*/ | SS_CENTERIMAGE /*垂直居中*/,
//			70 /*X坐标*/, 20/*Y坐标*/, 120/*宽度*/, 16 /*高度*/,
//			hwnd,  //父窗口句柄
//			(HMENU)2,  //为控件指定一个唯一标识符
//			hInst,  //当前程序实例句柄
//			NULL
//		);
//
//		hEdit = CreateWindow(
//			L"edit", //静态文本框的类名
//			L"untitled.txt",  //控件的文本
//			WS_CHILD /*子窗口*/ | WS_VISIBLE /*创建时显示*/ | WS_BORDER /*带边框*/ | SS_CENTER /*水平居中*/ | SS_CENTERIMAGE /*垂直居中*/,
//			71 /*X坐标*/, 68 /*Y坐标*/, 133 /*宽度*/, 20 /*高度*/,
//			hwnd,  //父窗口句柄
//			(HMENU)3,  //为控件指定一个唯一标识符
//			hInst,  //当前程序实例句柄
//			NULL
//		);
//		Font font;
//		font.setFont(hBtn);
//		font.setFont(hStatic);
//		font.setFont(hEdit);
//	}break;
//	case WM_PAINT:
//		break;
//	case WM_CLOSE:
//		break;
//	case WM_SIZE:
//		break;
//	default:
//
//		break;
//	}
//	
//	return DefWindowProc(hwnd, msg, wParam, lParam);
//
//}

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	PSTR szCmdLine,
	int iCmdShow
) {
	hInst = hInstance;//保存句柄，以便后面的调用
	Window window(hInstance, hPrevInstance, szCmdLine, iCmdShow);
	window.RegisterW(TEXT("Hello"));
	window.CreateW();
	//StaticText st(window.hwnd, window.hInst);
	/*
	Button bt(window.hwnd,window.hInst);
	Font ft;
	ft.setFont(bt.hBtn);
	ft.setFont(st.hStatic);
*/
	g_hwnd = window.hwnd;
	SetWindowCenter(g_hwnd);
	SetWindowText(g_hwnd, strTitle);

	window.UpdateW();
	window.ShowW();
	window.exec();
	return 0;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
	//HDC         hdc;  //设备环境句柄
	//PAINTSTRUCT ps;
	//RECT        rect; //绘图使用的数据
	int wmId, wmEvent;
	static HWND hEdit;
	static HWND hwndStatus;
	static TCHAR szTextBuf[20];
	switch (message) {
	case WM_CTLCOLORSTATIC://背景色绘制
		return (INT_PTR)GetStockObject(NULL_BRUSH);
		break;
	case WM_CREATE: {
		//hEdit= CreateWindow(TEXT("edit"), TEXT(""),
		//	WS_CHILD | WS_VISIBLE | WS_BORDER /*边框*/ | ES_AUTOVSCROLL /*水平滚动*/| ES_MULTILINE,
		//	20, 20, 450, 250,
		//	hwnd, (HMENU)3, hInst, NULL
		//);

		hEdit = CreateWindowEx(
			WS_EX_CLIENTEDGE,
			L"edit",
			L"",
			WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_MULTILINE | ES_AUTOVSCROLL | ES_NOHIDESEL,
			1, 1, 100, 100,
			hwnd,
			(HMENU)IDC_EDIT,
			GetModuleHandle(NULL),
			NULL
		);
		hwndStatus = CreateWindow(STATUSCLASSNAME, L"", WS_CHILD | WS_VISIBLE, 0, 0, 10, 10, hwnd, (HMENU)IDC_STATUS, hInst, NULL);
		// RichEdit，加载dll  
		//HINSTANCE hRichED = LoadLibrary(_T("riched20.dll"));
		//if (hRichED == NULL)
		//{
		//	MessageBoxA(0, "false", "", MB_OK);
		//}
		////创建3个子窗体，富编辑框控件，lable控件，下拉列表控件  
		//hEdit = CreateWindow(RICHEDIT_CLASS, NULL,
		//	WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_MULTILINE | ES_AUTOVSCROLL,
		//	0, 0, 0, 0,
		//	hwnd, (HMENU)IDC_EDIT, hInst, NULL);

		//int mask = SendMessage(hEdit, EM_SETEVENTMASK, 0, 0);
		//SendMessage(hwnd, EM_SETEVENTMASK, 0, ENM_KEYEVENTS | mask);//发送按键消息消息，在父窗体的消息处理函数中捕获按键消息  
		g_hwndStatus = hwndStatus;
		g_hEdit = hEdit;
		//hFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
		//SendMessage(hEdit, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(FALSE, 0));
		Font font;
		font.setFont(g_hEdit);
		//以下代码为设置框居中
		//RECT rcClient;
		//GetClientRect(hwnd, &rcClient);
		//SetWindowPos(hEdit, NULL, 0, 0, rcClient.right, rcClient.bottom, SWP_NOZORDER);
		//SendMessage(hEdit,EM_SETEVENTMASK, 0,ENM_CHANGE);
		SetFocus(hEdit);//设置焦点
	}
					break;
	case WM_SIZE://动态调整文本框的大小
	{
		RECT rcClient, rcStatus;
		GetClientRect(hwnd, &rcClient);
		SendMessage(hwndStatus, WM_SIZE, 0, 0);
		GetWindowRect(hwndStatus, &rcStatus);
		SetWindowPos(hEdit, NULL, 0, 0, rcClient.right, rcClient.bottom - rcStatus.bottom + rcStatus.top, SWP_NOZORDER);
	}
	break;
	case WM_MOUSEMOVE://鼠标移动事件
		wsprintf(szTextBuf, TEXT("鼠标位置：%d,%d"), LOWORD(lParam), HIWORD(lParam));
		SetWindowText(g_hwndStatus, szTextBuf);
		break;
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		switch (wmId) {
		case IDM_EXIT:
			PostMessage(hwnd, WM_CLOSE, 0, 0);
			break;
		case IDM_CUT:
			SendMessage(g_hEdit, WM_CUT, 0, 0);
			break;
		case IDM_COPY:
			SendMessage(g_hEdit, WM_COPY, 0, 0);
			break;
		case IDM_PASTE:
			SendMessage(g_hEdit, WM_PASTE, 0, 0);
			break;
		case IDM_FIND:
			CreateFindWindow();
			break;
		case IDM_REPLACE:
			CreateReplaceWindow();
			break;
		case IDM_SAVEAS:
			CreateFileWindow();
			SaveTextFileFromEdit();
			break;
		case IDM_OPEN:
			checksave();
			LoadFileToEdit();
			//Rrichedit 选中内容 已弃用
			//CHARRANGE cr;
			//cr.cpMin = 0;
			//cr.cpMax = 5;
			//SendMessage(g_hEdit, EM_EXSETSEL, 0, (LPARAM)&cr);
			//cr.cpMin = 10;
			//cr.cpMax = 15;
			//SendMessage(g_hEdit, EM_EXSETSEL, 0, (LPARAM)&cr);

			break;
		case IDM_SAVE:
			if (needsave) {
				if (isopened) {
					SaveTextFileFromEdit();
				}
				else if (CreateFileWindow()) {
					//调用保存窗口
					SaveTextFileFromEdit();
				}
			}
			break;
		case IDC_EDIT: //文本框事件，IDC_EDIT为用户指定的标识符
			switch (HIWORD(wParam)) {
			case EN_CHANGE:
			{
				if (!needsave) {
					needsave = true;
					if (!isopened) {
						TCHAR ch[MAX_PATH];
						wsprintf(ch, L"%s *", strTitle);
						SetWindowText(g_hwnd, ch);
					}
				}
			}
			break;
			default:
			{}
			return DefWindowProc(hwnd, message, wParam, lParam);
			}
			break;
		case WM_SETFOCUS:
			break;
		default:
			return DefWindowProc(hwnd, message, wParam, lParam);
		}
		break;
		//窗口绘制消息
	case WM_PAINT:
		break;
		//窗口销毁消息
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_CLOSE:
		if (needsave)
		{
			int res;
			res = MessageBox(g_hwnd, L"文件未保存，你是否想保存？", L"保存文件", MB_YESNOCANCEL | MB_ICONINFORMATION);
			if (res == IDCANCEL)
				return 0;
			if (res == IDYES)
			{
				if (CreateFileWindow())
					SaveTextFileFromEdit();
			}
		}
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}

void LoadFileToEdit()
{
	curfile[0] = '\0';
	OPENFILENAME ofn;
	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = g_hwnd;
	ofn.lpstrFilter = L"Text Files(*.txt)\0*.txt\0All File(*.*)\0*.*\0";
	ofn.lpstrFile = curfile;
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
	ofn.lpstrDefExt = L"txt";
	if (!GetOpenFileName(&ofn))
	{
		isopened = false;
		return;
	}
	//返回值： curfile ： 文件路径
	ifstream in(curfile);
	//int nLen = MultiByteToWideChar(CP_ACP, 0, pszText,
	//	strlen(pszText), NULL, 0);
	///*分配buff的空间*/
	//WCHAR *pwszText = (WCHAR*)malloc((nLen + 1) * sizeof(WCHAR));
	///*注意：MultiByteToWideChar系函数并不会处理C形式字符串的终止符！*/
	///*进行转换*/
	//pwszText[nLen] = 0;
	//MultiByteToWideChar(CP_ACP, 0, pszText, strlen(pszText),
	//	pwszText, nLen);
	//MessageBoxW(NULL, pwszText, L"Wide", MB_OK);
	//free(pwszText);
	std::string str((std::istreambuf_iterator<char>(in)),
		std::istreambuf_iterator<char>());
	SetWindowTextA(g_hEdit, str.c_str());
	isopened = true;
	//MessageBoxA(0, str.c_str(), "", MB_OK);
	TCHAR tmp[MAX_PATH], tmp2[MAX_PATH];
	wsprintf(tmp, curfile);
	PathStripPath(tmp);
	wsprintf(tmp2, L"NotePad 1.0 [%s]", tmp);
	SetWindowText(g_hwnd, tmp2);
}

void SaveTextFileFromEdit()
{
	//TCHAR buf[1024];
	int size = SendMessage(g_hEdit, EM_GETLIMITTEXT, 0, 0);//分配动态的大小
	TCHAR *buf = new TCHAR[size];
	GetWindowText(g_hEdit, buf, size);
	int nNum = WideCharToMultiByte(CP_ACP, 0, buf, -1, 0, 0, NULL, NULL);
	char* pBuffer = new char[nNum + 1];
	WideCharToMultiByte(CP_ACP, 0, buf, -1, pBuffer, nNum, NULL, NULL);//实现unicode宽字符到多字节
	ofstream out2(curfile);
	out2 << pBuffer;
	out2.close();
	needsave = false;
}

void checksave()
{
	if (needsave)
	{
		int res;
		res = MessageBox(g_hwnd, L"文件未保存，是否保存", L"保存以继续", MB_YESNOCANCEL | MB_ICONINFORMATION);
		if (res == IDCANCEL)
			return;
		if (res == IDNO)
		{
			needsave = false;
			return;
		}
		if (CreateFileWindow())
			SaveTextFileFromEdit();
	}
}

bool CreateFileWindow() {//文件保存窗口
	OPENFILENAME ofn;
	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = g_hwnd;
	ofn.lpstrFilter = L"Text Files(*.txt)\0*.txt\0All File(*.*)\0*.*\0";
	ofn.lpstrFile = curfile;
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;
	ofn.lpstrDefExt = L"txt";
	if (!GetSaveFileName(&ofn))
		return false;
	// 返回值 curfile 文件的地址
	TCHAR tmp[MAX_PATH], tmp2[MAX_PATH];
	wsprintf(tmp, curfile);
	PathStripPath(tmp);
	wsprintf(tmp2, L"NotePad 1.0 [%s]", tmp);
	SetWindowText(g_hwnd, tmp2);
	return true;
}
void SetWindowCenter(const HWND &hwnd) {//设置窗口居中
	int scrWidth = GetSystemMetrics(SM_CXSCREEN);
	int scrHeight = GetSystemMetrics(SM_CYSCREEN);
	RECT rect;
	//获取窗体尺寸  
	GetWindowRect(hwnd, &rect);
	rect.left = (scrWidth - rect.right) / 2;
	rect.top = (scrHeight - rect.bottom) / 2;
	//设置窗体位置  
	//SetWindowPos(hwnd, HWND_TOP, rect.left, rect.top, rect.right, rect.bottom, SWP_SHOWWINDOW);
	MoveWindow(hwnd, rect.left, rect.top, rect.right, rect.bottom, 1);
}
