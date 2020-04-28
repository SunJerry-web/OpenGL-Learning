#include <windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>

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

	HWND hwnd = CreateWindowEx(NULL, L"GLWindow", L"Draw Line", WS_OVERLAPPEDWINDOW, 100, 100, 800, 600, NULL, NULL, hInstance, NULL);

	HDC dc = GetDC(hwnd);
	//定义像素格式说明符
	PIXELFORMATDESCRIPTOR pfd;
	memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
	pfd.nVersion = 1;
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);

	//颜色缓冲区32位
	pfd.cColorBits = 32;
	pfd.cDepthBits = 24;
	pfd.cStencilBits = 8;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.iLayerType = PFD_MAIN_PLANE;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;

	int pixelFormat = ChoosePixelFormat(dc, &pfd);
	SetPixelFormat(dc, pixelFormat, &pfd);

	HGLRC rc = wglCreateContext(dc);
	wglMakeCurrent(dc, rc);

	glMatrixMode(GL_PROJECTION);
	gluPerspective(50.0f, 800.0f / 600.0f, 0.1f, 1000.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClearColor(0.1, 0.4, 0.6, 1.0);


	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);

	MSG msg;
	while (true) {
		if (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE)) {
			if (msg.message == WM_QUIT) {
				break;
			}

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		glClear(GL_COLOR_BUFFER_BIT);
		//设置线的宽度
		glLineWidth(4.0f);
		/*1、必须是两个独立的点，才能连成一条线
		glBegin(GL_LINES);
		glVertex3f(0.0f, 0.0f, -10.0f);
		glVertex3f(-5.0f, 0.0f, -10.0f);
		glVertex3f(0.0, 5.0f, -10.0f);
		glEnd();*/
		/*2、自动首尾相连，成环
		glBegin(GL_LINE_LOOP);
		glVertex3f(0.0f, 0.0f, -10.0f);
		glVertex3f(-5.0f, 0.0f, -10.0f);
		glVertex3f(0.0, 5.0f, -10.0f);
		glEnd();*/
		/*3、不会成环*/
		//可以绘制出颜色渐变的效果
		glBegin(GL_LINE_STRIP);
		glColor4ub(255,0,0,255);
		glVertex3f(0.0f, 0.0f, -10.0f);
		glColor4ub(0,255,0,255);
		glVertex3f(-5.0f, 0.0f, -10.0f);
		glColor4ub(0,0,255,255);
		glVertex3f(0.0, 5.0f, -10.0f);
		glEnd();
		SwapBuffers(dc);
	}

	return 0;
}

