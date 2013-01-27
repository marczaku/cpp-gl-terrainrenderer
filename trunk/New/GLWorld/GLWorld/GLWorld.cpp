// GLWorld.cpp : Defines the entry point for the application.

#include "stdafx.h"
#include "GLWorld.h"
#include "GLWindow.h"
#include "Application.h"
#include <gl\glew.h>			// Header File For The OpenGL32 Library
//#include <gl\glu.h>			// Header File For The GLu32 Library

//globals
double deltaTime;
bool	g_bQuit;

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
	Application App(hInstance);

	App.Init();

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
			App.Update(deltaTime);
			App.Draw();
		}
	}

	return (int) msg.wParam;
}