#include "Font.h"

Font::Font() {
	hFont = CreateFont(20/*�߶�*/, 0/*���*/, 0, 0, 400 /*һ�����ֵ��Ϊ400*/,
		FALSE/*����б��*/, FALSE/*�����»���*/, FALSE/*����ɾ����*/,
		DEFAULT_CHARSET,  //��������ʹ��Ĭ���ַ��������������� _CHARSET ��β�ĳ�������
		OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS,  //���в������ù�
		DEFAULT_QUALITY,  //Ĭ���������
		FF_DONTCARE,  //��ָ��������*/
		L"����"  //������
	);
}

void Font::setFont(HWND hBtn) {
	SendMessage(hBtn, WM_SETFONT,
		(WPARAM)hFont, NULL);
}
