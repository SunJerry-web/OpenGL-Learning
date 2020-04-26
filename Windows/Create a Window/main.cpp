#include <Windows.h>

LRESULT CALLBACK GLWindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	
	//switch用来处理消息
	switch (msg) {
		case WM_CLOSE:
			PostQuitMessage(0);
			break;
		default:
			break;
	}
	
	return DefWindowProc(hwnd,msg,wParam,lParam);
}


//这里是程序入口，WINAPI WinMain
INT WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd) {

	//注册一个窗口
	WNDCLASSEX wndclass;
	//这里不太懂，不明白，待会去查
	//不需要为这个窗口类型申请额外的存储空间
	wndclass.cbClsExtra = 0;
	//结构体的大小
	wndclass.cbSize = sizeof(WNDCLASSEX);
	//不需要为窗口准备额外的存储空间
	wndclass.cbWndExtra = 0;
	//设置背景颜色
	wndclass.hbrBackground = NULL;
	//窗口类的光标
	wndclass.hCursor = NULL;
	//窗口类的图标，即生成的exe文件的图标长什么样
	wndclass.hIcon = NULL;
	//窗口类的任务栏图标，生成的窗口左上角地图标
	wndclass.hIconSm = NULL;
	//窗口类所在模块的实例句柄
	wndclass.hInstance = hInstance;
	//窗口的处理过程，消息响应函数
	wndclass.lpfnWndProc = GLWindowProc;
	//窗口类的名称
	wndclass.lpszClassName = L"GLWindow";
	//窗口类的菜单资源名
	wndclass.lpszMenuName = NULL;
	//类的风格
	wndclass.style = CS_VREDRAW | CS_HREDRAW;
	//真正开始注册，返回一个标记，存到atom中
	ATOM atom = RegisterClassEx(&wndclass);
	//检查注册是否成功
	if (!atom) {
		return -1;
	}
	//Create a window
	//额外的窗口风格，窗口类的名字，窗口的名字，窗口风格，起始位置x，y,宽度，长度，父窗口，菜单，实例，其它参数
	HWND hwnd = CreateWindowEx(NULL, L"GLWindow",L"OpenGL Window",WS_OVERLAPPEDWINDOW,100,100,800,600,NULL,NULL,hInstance,NULL);
	//Show window
	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);

	//确保函数不会直接退出，
	MSG msg;
	while (true)
	{
		//如果我抓到一个消息，就去处理消息
		if (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE)) {
			if (msg.message == WM_QUIT) {
				break;
			}
			//转换我的消息为应用程序消息
			TranslateMessage(&msg);
			//把该消息派发出去，派发到回调函数LRESULT CALLBACK GLWindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
			DispatchMessage(&msg);

		}

		//draw sence

	}
	return  0;
}

