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

INT_PTR CALLBACK DlgReplaceProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {//�滻���ڹ��̴���
	static HWND hBtn;
	HWND hEdit1;
	HWND hEdit2;


	switch (msg)
	{

	case WM_COMMAND:
	{
		if (LOWORD(wParam) == IDC_BUTTON1) {//�滻ȫ��
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
		else if (LOWORD(wParam) == IDOK) {//�滻һ��
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
			// ���ִ���˹ر�  
			// ���ٶԻ��򣬽��յ�WM_DESTROY��Ϣ  
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
	int size = SendMessage(g_hEdit, EM_GETLIMITTEXT, 0, 0);//���䶯̬�Ĵ�С	
	TCHAR *buf = new TCHAR[size];
	GetWindowText(g_hEdit, buf, size);
	//wstring test(&buf[0]); 
	//string str(test.begin(), test.end()); 
	CString str(buf);
	str.Replace(src, dest);
	TCHAR *buf2 = str.GetBuffer(str.GetLength());
	//TCHAR *buf2 = (TCHAR*)str.c_str();
	SetWindowText(g_hEdit, buf2);
	MessageBox(g_hwnd, L"������滻��", L"�ɹ�", MB_OK | MB_ICONINFORMATION);
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
//	int size = SendMessage(g_hEdit, EM_GETLIMITTEXT, 0, 0);//���䶯̬�Ĵ�С
//	TCHAR *buf = new TCHAR[size];
//	GetWindowText(g_hEdit, buf, size);
//	wstring test(&buf[0]); //ʵ�ֿ��ַ���string���͵�ת��
//	//string content(test.begin(), test.end());
//	//size_t found = content.find(str);
//	size_t found = content.find_first_of(str, index);
//	if (found == string::npos) {
//		wsprintf(buf, L"û���ҵ� %s", str);
//		MessageBox(g_hwnd, buf, L"�Ҳ�������", MB_OK | MB_ICONERROR);
//		SetWindowText(g_hwndStatus, buf);
//		index = 0;
//		return false;
//	}
//	else {
//		wsprintf(buf, L"�� %d �ҵ� %s", found, str);
//		//MessageBox(g_hwnd, buf, L"�ҵ�����", MB_OK | MB_ICONINFORMATION);
//		SetWindowText(g_hwndStatus, buf);
//		index = found + 1;
//		SetFocus(g_hEdit);//��ȡ�������ѡ��
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
	}//��ͬ�ַ�ʱ����ʼλ�ÿ�ʼ����
	else {
		last = str;
	}
	//TCHAR buf[1024];
	int size = SendMessage(g_hEdit, EM_GETLIMITTEXT, 0, 0);//���䶯̬�Ĵ�С
	TCHAR *buf = new TCHAR[size];
	GetWindowText(g_hEdit, buf, size);
	wstring test(buf); //ʵ�ֿ��ַ���wstring���͵�ת��
					   //string content(test.begin(), test.end());
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
		needsave = false;
		return true;
	}
}
