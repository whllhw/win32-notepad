#include "StaticText.h"
//������
StaticText::StaticText(HWND hwnd,HINSTANCE hInst){
	hStatic = CreateWindow(
		L"static", //��̬�ı��������
		L"C����������",  //�ؼ����ı�
		WS_CHILD /*�Ӵ���*/ | WS_VISIBLE /*����ʱ��ʾ*/ | WS_BORDER /*���߿�*/ | SS_CENTER /*ˮƽ����*/ | SS_CENTERIMAGE /*��ֱ����*/,
		20 /*X����*/, 20 /*Y����*/, 200 /*���*/, 100 /*�߶�*/,
		hwnd,  //�����ھ��
		(HMENU)1,  //Ϊ�ؼ�ָ��һ��Ψһ��ʶ��
		hInst,  //��ǰ����ʵ�����
		NULL
	);
}


StaticText::~StaticText()
{
}
