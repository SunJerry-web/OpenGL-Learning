#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>

//下面的语句用来链接相应的库。
#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib")

LRESULT CALLBACK GLWindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {

	//switch用来处理消息
	switch (msg) {
	case WM_CLOSE:
		PostQuitMessage(0);
		break;
	default:
		break;
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}



INT WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd) {

	WNDCLASSEX wndclass;
	wndclass.cbClsExtra = 0;
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.cbWndExtra = 0;
	wndclass.hbrBackground = NULL;
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hIcon = NULL;
	wndclass.hIconSm = NULL;
	wndclass.hInstance = hInstance;
	wndclass.lpfnWndProc = GLWindowProc;
	wndclass.lpszClassName = L"GLWindow";
	wndclass.lpszMenuName = NULL;
	wndclass.style = CS_VREDRAW | CS_HREDRAW;

	ATOM atom = RegisterClassEx(&wndclass);
	if (!atom) {
		return -1;
	}

	//Create a window
	HWND hwnd = CreateWindowEx(NULL, L"GLWindow", L"OpenGL Window", WS_OVERLAPPEDWINDOW, 100, 100, 800, 600, NULL, NULL, hInstance, NULL);

	//create opengl render context
	HDC dc = GetDC(hwnd);
	PIXELFORMATDESCRIPTOR pfd;
	memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
	pfd.nVersion = 1;
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.cColorBits = 32;
	pfd.cDepthBits = 24;
	pfd.cStencilBits = 8;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.iLayerType = PFD_MAIN_PLANE;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;


	int pixelFormat = ChoosePixelFormat(dc, &pfd);
	SetPixelFormat(dc, pixelFormat, &pfd);

	HGLRC rc = wglCreateContext(dc);
	wglMakeCurrent(dc, rc);	//setup opengl context complete

	//opengl init
	/*下面这里是在上节代码上新增的内容*/
	glMatrixMode(GL_PROJECTION);	//tell the gpu processer that I would select the projection matrix;
	// 50.0f为摄像机的视角，800.0f / 600.0f ，窗口宽高比，0.1f为最近能看到哪，1000.0f最远能看到哪
	gluPerspective(50.0f, 800.0f / 600.0f, 0.1f, 1000.0f);	//set some values to projextion matrix
	glMatrixMode(GL_MODELVIEW); //tell the gpu processor that I select the model view matrix，设置模型视口矩阵
	 // 加载一个单位矩阵，即不对模型视口矩阵进行操作
	glLoadIdentity();
	/**************************/
	//set "clearcolor" for background，用这种颜色去擦除颜色缓冲区
	glClearColor(0.1, 0.4, 0.6, 1.0);

	//Show window
	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);

	MSG msg;
	while (true)
	{
		if (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE)) {
			if (msg.message == WM_QUIT) {
				break;
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);

		}

		//draw sence
		glClear(GL_COLOR_BUFFER_BIT);
		/*这里是新增的代码*/
		//设置点的颜色,这里位白色
		glColor4ub(255, 255, 255, 255);	//每个Color的分量占8个字节
		glPointSize(10.0f);
		//画出来的像素点位方格子
		glBegin(GL_POINTS);	//start to draw points
		glVertex3f(0.0f, 0.0f, -0.5f);
		glEnd();	//end
		/*********************************************/
		//present sence
		//把场景渲染到屏幕上去，交换前后缓冲区的内容
		SwapBuffers(dc);
	}
	return  0;
}


