#include "window.h"

WPARAM Window::exec() {
	//while (GetMessage(&msg, NULL, 0, 0)) {
	//	TranslateMessage(&msg);  //������Ϣ
	//	DispatchMessage(&msg);  //������Ϣ
	//}
	while (msg.message != WM_QUIT) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)){
			TranslateMessage(&msg);
			DispatchMessage(&msg);}
		else{
			KeyDown(hwnd);}}
	return msg.wParam;
}
void Window::KeyDown(HWND hwnd) {//��Ӧ�����¼�����
	static HWND hEdit, hwndStatus;
	if (!hEdit) {
		hEdit = GetDlgItem(hwnd, IDC_EDIT);
		hwndStatus = GetDlgItem(hwnd, IDC_STATUS);
	}
	char tmp[1024];
	// �õ������еĵĳ���;  
	//iLength = SendMessage(hWndEdit, EM_LINELENGTH, iLine, 0);
	//EM_GETTHUMB(&HBE=190),0,0 //ȡ�ö����ı��༭�ؼ��Ĺ�����ĵ�ǰλ�ã�ע�⣺������ֵ��
	//EM_GETSEL(&HB0=176),0,//���� ��ȡ���λ�ã����ֽ�����ʾ������:(���������,�������յ�)ȡ�ñ༭�ؼ���ѡ�����ݵķ�Χ������ֵ�е�16λΪ��㣬��16λΪ�յ�
	size_t x = SendMessage(hEdit, EM_LINEFROMCHAR, -1, 0);//�õ���������е�ƫ����
	wsprintfA(tmp, "��ǰ %d �У����� %d ��", x + 1, SendMessage(hEdit, EM_GETLINECOUNT, 0, 0));
	SetWindowTextA(hwndStatus, tmp);
	if (GetAsyncKeyState(VK_UP)) {
		//��UP����ʱִ���¼�
	}
}
void Window::ShowW() {
	ShowWindow(hwnd, iCmdShow);
}
void Window::CreateW() {
	AddMenu();
	hwnd = 
		(
		szClassName,  //�����������
		TEXT("Welcome"),  //���ڱ��⣨�����ڱ�������
		WS_OVERLAPPEDWINDOW,  //���ڷ��
		CW_USEDEFAULT,  //��ʼ��ʱx���λ��
		CW_USEDEFAULT,  //��ʼ��ʱy���λ��
		500,  //���ڿ��
		320,  //���ڸ߶�
		NULL,  //�����ھ��
		hRoot,  //���ڲ˵����
		hInst,  //��ǰ���ڵľ��
		NULL  //��ʹ�ø�ֵ
	);
}
void Window::UpdateW() {
	UpdateWindow(hwnd);
}
const void Window::RegisterW(TCHAR szClassName[]) {
	this->szClassName = szClassName;
	WNDCLASS &wndclass = *(new WNDCLASS);  //����
										   //Ϊ������ĸ����ֶθ�ֵ
	wndclass.style = CS_HREDRAW | CS_VREDRAW;  //���ڷ��
	wndclass.lpfnWndProc = WndProc;  //���ڹ���
	wndclass.cbClsExtra = 0;  //��ʱ����Ҫ���
	wndclass.cbWndExtra = 0;  //��ʱ����Ҫ���
	wndclass.hInstance = hInst;  //��ǰ���ھ��
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);  //����ͼ��
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);  //�����ʽ
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);  //���ڱ�����ˢ
	wndclass.lpszMenuName = NULL;  //���ڲ˵�
	wndclass.lpszClassName = this->szClassName;  //��������
												 //ע�ᴰ��
	RegisterClass(&wndclass);

}
void Window::AddMenu() {
	hRoot = CreateMenu();
	HMENU pop1 = CreatePopupMenu();
	AppendMenu(hRoot,
		MF_POPUP,
		(UINT_PTR)pop1,
		L" �ļ�(&F)");
	// ʹ��AppendMenu���� 
	AppendMenu(pop1,
		MF_STRING,
		IDM_OPEN,
		L"��(&O)");
	AppendMenu(pop1,
		MF_STRING,
		IDM_SAVE,
		L"����(&S)");
	AppendMenu(pop1,
		MF_STRING,
		IDM_SAVEAS,
		L"���Ϊ(&A)");
	AppendMenu(pop1,
		MF_STRING,
		IDM_EXIT,
		L"�˳�(&Q)");
	HMENU pop2 = CreatePopupMenu();
	AppendMenu(hRoot,
		MF_POPUP,
		(UINT_PTR)pop2,
		L"�༭(&E)");
	AppendMenu(pop2,
		MF_STRING,
		IDM_FIND,
		L"����(&F)");
	AppendMenu(pop2,
		MF_STRING,
		IDM_REPLACE,
		L"�滻(&R)");
	AppendMenu(pop2,
		MF_STRING,
		IDM_CUT,
		L"����(&T)");
	AppendMenu(pop2,
		MF_STRING,
		IDM_COPY,
		L"����(&C)");
	AppendMenu(pop2,
		MF_STRING,
		IDM_PASTE,
		L"ճ��(&P)");

}