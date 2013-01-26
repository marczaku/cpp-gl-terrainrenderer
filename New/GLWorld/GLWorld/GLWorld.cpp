// GLWorld.cpp : Defines the entry point for the application.

#include "stdafx.h"
#include "GLWorld.h"
#include "GLWindow.h"
#include <gl\glew.h>			// Header File For The OpenGL32 Library
//#include <gl\glu.h>			// Header File For The GLu32 Library

//globals
double deltaTime;
bool	g_bQuit;
GLWindow* g_Window;

//functions
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

void Init()
{
	//Initialize OpenGL
	glewInit();
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	gluPerspective( 70, GLdouble( 800 ) / 600, 0.01, 10000.0 );
	g_bQuit=false;
}
void Update(double DeltaTime)
{
}
void Draw()
{
	g_Window->Clear();
}


int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	MSG			msg;
	HACCEL		hAccelTable;
	long long	previousTime;
	long long	currentTime;
	double		secondsPerCount;

	g_Window = new GLWindow(hInstance);
	g_Window->SetWndProcFunction(WndProc);
	g_Window->Show();
	Init();
	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_GLWORLD));
	{
		long long CountsPerSecond=0;
		QueryPerformanceCounter((LARGE_INTEGER*)&previousTime);
		QueryPerformanceFrequency((LARGE_INTEGER*)&CountsPerSecond); 
		secondsPerCount = 1.0 / (double)CountsPerSecond;
	}

	while(!g_bQuit)
	{
		QueryPerformanceCounter((LARGE_INTEGER*)&currentTime);
		deltaTime=(double)(currentTime-previousTime)*secondsPerCount;

		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))
		{
			if (msg.message==WM_QUIT)
			{
				g_bQuit=true;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			Update(deltaTime);
			Draw();
		}
	}

	delete g_Window;
	return (int) msg.wParam;
}



LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_ACTIVATE:
			//active = (!HIWORD(wParam))
			return 0;
	case WM_SYSCOMMAND:// Intercept System Commands
			switch (wParam)
			{
			case SC_SCREENSAVE:
			case SC_MONITORPOWER:
				return 0;
			}
			break;
	case WM_CLOSE:
			PostQuitMessage(0);
			return 0;
	case WM_KEYDOWN:
			//keys[wParam] = TRUE;
			return 0;
	case WM_LBUTTONUP:
			//bCaptureModeOn=false;
			return 0;
	case WM_MOUSEMOVE:
			if(wParam==MK_LBUTTON)
			{
				//if(!bCaptureModeOn)
				//{
					//bCaptureModeOn=true;
					//xOldPos = LOWORD(lParam); 
					//yOldPos = HIWORD(lParam);
				//}
				//else
				//{
					//xPos = LOWORD(lParam); 
					//yPos = HIWORD(lParam);
					//xDelta=xPos-xOldPos;
					//yDelta=yPos-yOldPos;
					//xOldPos=xPos;
					//yOldPos=yPos;
				//}
			}
			return 0;
	case WM_KEYUP:
			//keys[wParam] = FALSE;
			return 0;
	case WM_SIZE:
			//ReSizeGLScene(LOWORD(lParam),HIWORD(lParam));  // LoWord=Width, HiWord=Height
			return 0;
	}

	// Pass All Unhandled Messages To DefWindowProc
	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}