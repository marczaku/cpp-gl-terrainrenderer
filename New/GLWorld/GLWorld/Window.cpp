//Window.cpp

#include "stdafx.h"
#include "Window.h"

#include "Resource.h"

Window::Window(HINSTANCE hInstance, const WNDCLASSEX* wcx, const RECT* Dimensions, bool bDisplay)
{
	m_hWnd = NULL;
	m_bRegistered=false;
	m_bCreated=false;

	m_hInst=hInstance;

	// Initialize global strings
	LoadString(m_hInst, IDS_APP_TITLE, m_szTitle, MAX_LOADSTRING);

	if(wcx == 0)
	{
		m_wcx.cbSize = sizeof(WNDCLASSEX);
		m_wcx.style = CS_HREDRAW | CS_VREDRAW;
		m_wcx.lpfnWndProc = Window::stWndProc;
		m_wcx.cbClsExtra = 0;
		m_wcx.cbWndExtra = 0;
		m_wcx.hInstance = m_hInst;
		m_wcx.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		m_wcx.hCursor = LoadCursor(NULL, IDC_ARROW);
		m_wcx.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
		m_wcx.lpszMenuName = NULL;
		m_wcx.lpszClassName = "NewWindow";
		m_wcx.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	}
	else
	{
		memcpy(&m_wcx,wcx,sizeof(WNDCLASSEX));
	}
	
	if(Dimensions == 0)
	{
		m_Dimensions.top = 0;
		m_Dimensions.left = 0;
		m_Dimensions.right = 800;
		m_Dimensions.bottom = 600;
	}
	else
	{
		memcpy(&m_Dimensions,Dimensions,sizeof(RECT));
	}

	m_Styles = WS_OVERLAPPEDWINDOW | WS_VISIBLE;

	m_WNdProcFunction = DefWndProc;
}
//---------------------------------------------------
Window::~Window()
{
	if (m_bCreated)
	{
		DestroyWindow(m_hWnd);
		m_hWnd=0;
		m_bCreated=false;
	}
	if(m_bRegistered)
	{
		UnregisterClass(m_wcx.lpszClassName,m_hInst);
		m_bRegistered=false;
	}
}
//---------------------------------------------------
bool Window::RegisterWindow()
{
	m_bRegistered=(!(RegisterClassEx(&m_wcx) == 0));
	return m_bRegistered;
}
//---------------------------------------------------
bool Window::Create()
{
	m_hWnd = NULL;

	// send the this pointer as the window creation parameter
	m_hWnd = CreateWindow(m_wcx.lpszClassName, m_szTitle, m_Styles, m_Dimensions.left, m_Dimensions.top, 
		m_Dimensions.right - m_Dimensions.left, m_Dimensions.bottom - m_Dimensions.top, NULL, NULL, m_hInst, 
		(void *)this);

	m_bCreated = (m_hWnd != NULL);

	return m_bCreated;
}
//---------------------------------------------------
bool Window::Show(const bool p_bDisplay)
{
	if(!m_bRegistered && !RegisterWindow())
		return false;
	if(!m_bCreated && !Create())
		return false;

	ShowWindow(m_hWnd, p_bDisplay);
	UpdateWindow(m_hWnd);

	return true;
}
//---------------------------------------------------
void Window::SetWindowTitle(char* lpszTitle) 
{
	ZeroMemory(m_szTitle, sizeof(char)*MAX_LOADSTRING);
	strcpy_s(m_szTitle, lpszTitle);
}
//---------------------------------------------------
void Window::SetWndProcFunction(WndProcFunction ProcFunction)
{
	m_WNdProcFunction = ProcFunction;
}
//---------------------------------------------------
LRESULT CALLBACK Window::stWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	Window* pWnd;

	if (uMsg == WM_NCCREATE)
		SetWindowLong(hWnd, GWL_USERDATA, (long)((LPCREATESTRUCT(lParam))->lpCreateParams));

	pWnd = GetObjectFromWindow(hWnd);

	if (pWnd)
		return pWnd->m_WNdProcFunction(hWnd, uMsg, wParam, lParam);
	else
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
//---------------------------------------------------
LRESULT DefWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			//DialogBox(m_hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}