// GLWorld.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "GLWorld.h"
#include "Window.h"


int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	MSG msg;
	HACCEL hAccelTable;

	// Create a window using the resource files
	Window Win(hInstance);
	Win.Show();

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_GLWORLD));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}