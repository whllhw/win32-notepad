#include "window.h"

WPARAM Window::exec() {
	//while (GetMessage(&msg, NULL, 0, 0)) {
	//	TranslateMessage(&msg);  //翻译消息
	//	DispatchMessage(&msg);  //分派消息
	//}
	while (msg.message != WM_QUIT) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)){
			TranslateMessage(&msg);
			DispatchMessage(&msg);}
		else{
			KeyDown(hwnd);}}
	return msg.wParam;
}
void Window::KeyDown(HWND hwnd) {//响应按键事件！！
	static HWND hEdit, hwndStatus;
	if (!hEdit) {
		hEdit = GetDlgItem(hwnd, IDC_EDIT);
		hwndStatus = GetDlgItem(hwnd, IDC_STATUS);
	}
	char tmp[1024];
	// 得到所在行的的长度;  
	//iLength = SendMessage(hWndEdit, EM_LINELENGTH, iLine, 0);
	//EM_GETTHUMB(&HBE=190),0,0 //取得多行文本编辑控件的滚动框的当前位置（注意：是象素值）
	//EM_GETSEL(&HB0=176),0,//变量 获取光标位置（以字节数表示），或:(缓冲区起点,缓冲区终点)取得编辑控件中选定内容的范围，返回值中低16位为起点，高16位为终点
	size_t x = SendMessage(hEdit, EM_LINEFROMCHAR, -1, 0);//得到光标所在行的偏移量
	wsprintfA(tmp, "当前 %d 行，共有 %d 行", x + 1, SendMessage(hEdit, EM_GETLINECOUNT, 0, 0));
	SetWindowTextA(hwndStatus, tmp);
	if (GetAsyncKeyState(VK_UP)) {
		//当UP按下时执行事件
	}
}
void Window::ShowW() {
	ShowWindow(hwnd, iCmdShow);
}
void Window::CreateW() {
	AddMenu();
	hwnd = 
		(
		szClassName,  //窗口类的名字
		TEXT("Welcome"),  //窗口标题（出现在标题栏）
		WS_OVERLAPPEDWINDOW,  //窗口风格
		CW_USEDEFAULT,  //初始化时x轴的位置
		CW_USEDEFAULT,  //初始化时y轴的位置
		500,  //窗口宽度
		320,  //窗口高度
		NULL,  //父窗口句柄
		hRoot,  //窗口菜单句柄
		hInst,  //当前窗口的句柄
		NULL  //不使用该值
	);
}
void Window::UpdateW() {
	UpdateWindow(hwnd);
}
const void Window::RegisterW(TCHAR szClassName[]) {
	this->szClassName = szClassName;
	WNDCLASS &wndclass = *(new WNDCLASS);  //窗口
										   //为窗口类的各个字段赋值
	wndclass.style = CS_HREDRAW | CS_VREDRAW;  //窗口风格
	wndclass.lpfnWndProc = WndProc;  //窗口过程
	wndclass.cbClsExtra = 0;  //暂时不需要理解
	wndclass.cbWndExtra = 0;  //暂时不需要理解
	wndclass.hInstance = hInst;  //当前窗口句柄
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);  //窗口图标
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);  //鼠标样式
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);  //窗口背景画刷
	wndclass.lpszMenuName = NULL;  //窗口菜单
	wndclass.lpszClassName = this->szClassName;  //窗口类名
												 //注册窗口
	RegisterClass(&wndclass);

}
void Window::AddMenu() {
	hRoot = CreateMenu();
	HMENU pop1 = CreatePopupMenu();
	AppendMenu(hRoot,
		MF_POPUP,
		(UINT_PTR)pop1,
		L" 文件(&F)");
	// 使用AppendMenu函数 
	AppendMenu(pop1,
		MF_STRING,
		IDM_OPEN,
		L"打开(&O)");
	AppendMenu(pop1,
		MF_STRING,
		IDM_SAVE,
		L"保存(&S)");
	AppendMenu(pop1,
		MF_STRING,
		IDM_SAVEAS,
		L"另存为(&A)");
	AppendMenu(pop1,
		MF_STRING,
		IDM_EXIT,
		L"退出(&Q)");
	HMENU pop2 = CreatePopupMenu();
	AppendMenu(hRoot,
		MF_POPUP,
		(UINT_PTR)pop2,
		L"编辑(&E)");
	AppendMenu(pop2,
		MF_STRING,
		IDM_FIND,
		L"查找(&F)");
	AppendMenu(pop2,
		MF_STRING,
		IDM_REPLACE,
		L"替换(&R)");
	AppendMenu(pop2,
		MF_STRING,
		IDM_CUT,
		L"剪切(&T)");
	AppendMenu(pop2,
		MF_STRING,
		IDM_COPY,
		L"复制(&C)");
	AppendMenu(pop2,
		MF_STRING,
		IDM_PASTE,
		L"粘贴(&P)");

}