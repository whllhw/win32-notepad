#include <Windows.h>
#include <atlstr.h>
#include "Font.h"
#include <string>
#include <Richedit.h>
#include "resource.h"
//TODO Messagbox�������룡�Ѿ����
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
			//		TEXT("����"),
			//		WS_CHILD | WS_VISIBLE | SS_CENTER | WS_BORDER,
			//		140, 210, 133, 30,
			//		hwnd,
			//		(HMENU)1,
			//		hInst,
			//		NULL
			//	);

			//	HWND hStatic1 = CreateWindow(

			//		L"static", //��̬�ı��������
			//		L"Ҫ���ҵ��ı�",  //�ؼ����ı�
			//		WS_CHILD /*�Ӵ���*/ | WS_VISIBLE /*����ʱ��ʾ*/,//| WS_BORDER /*���߿�*/ | SS_CENTER /*ˮƽ����*/ | SS_CENTERIMAGE /*��ֱ����*/,
			//		100, 30, 191, 51,
			//		hwnd,  //�����ھ��
			//		(HMENU)2,  //Ϊ�ؼ�ָ��һ��Ψһ��ʶ��
			//		hInst,  //��ǰ����ʵ�����
			//		NULL
			//	);

			//	hEdit1 = CreateWindow(
			//		L"edit", //��̬�ı��������
			//		L"",  //�ؼ����ı�
			//		WS_CHILD /*�Ӵ���*/ | WS_VISIBLE /*����ʱ��ʾ*/,//| WS_BORDER /*���߿�*/ | SS_CENTER /*ˮƽ����*/ | SS_CENTERIMAGE /*��ֱ����*/,
			//		100, 90, 211, 30,
			//		hwnd,  //�����ھ��
			//		(HMENU)4,  //Ϊ�ؼ�ָ��һ��Ψһ��ʶ��
			//		hInst,  //��ǰ����ʵ�����
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
	//case WM_KEYDOWN://��Ч����
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
			// ���ִ���˹ر�  
			// ���ٶԻ��򣬽��յ�WM_DESTROY��Ϣ  
			DestroyWindow(hwnd);
		}
		return 0;
	default:
		break;
	}
	//return DefWindowProc(hwnd, msg, wParam, lParam); ����ʹ��
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
	}//��ͬ�ַ�ʱ����ʼλ�ÿ�ʼ����
	else {
		last = str;
	}
	int size = SendMessage(g_hEdit, EM_GETLIMITTEXT, 0, 0);//���䶯̬�Ĵ�С
	TCHAR *buf = new TCHAR[size];
	GetWindowText(g_hEdit, buf, size);
	wstring test(buf); 
	size_t found = test.find(str, index);
	if (found == wstring::npos || found == index) {
		wsprintf(buf, L"û���ҵ� %s", str.c_str());
		MessageBox(g_hwnd, buf, L"�Ҳ�������", MB_OK | MB_ICONERROR);
		SetWindowText(g_hwndStatus, buf);
		index = 0;
		return false;
	}
	else {
		wsprintf(buf, L"�� %d �ҵ� %s", found, str.c_str());
		//MessageBox(g_hwnd, buf, L"�ҵ�����", MB_OK | MB_ICONINFORMATION);
		SetWindowText(g_hwndStatus, buf);
		index = found + str.length();
		SetFocus(g_hEdit);//��ȡ�������ѡ��
		SendMessage(g_hEdit, EM_SETSEL, found, found + str.length());
		SendMessage(g_hEdit, EM_SCROLLCARET, 0, 0);//�ѿɼ���Χ������괦
		//EM_SCROLL(&HB5=181),*,0 //�ı���ֱ����������������*���ƹ�������:SB_LINEDOWN(1)���¹���һ�У�SB_LINEUP(0)���Ϲ���һ�У�SB_PAGEDOWN(3)���¹���һҳ��SB_PAGEUP(2)���Ϲ���һҳ��
		return true;
	}
}
