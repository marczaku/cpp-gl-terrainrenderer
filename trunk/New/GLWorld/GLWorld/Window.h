//Window.h

#pragma once
#include "stdafx.h"

#define MAX_LOADSTRING 100

class Window
{
private:
	HINSTANCE	m_hInst;
	HWND		m_hWnd;
	TCHAR		m_szTitle[MAX_LOADSTRING];
	WNDCLASSEX	m_wcx;
	RECT		m_Dimensions;
	DWORD		m_Styles;
	bool		m_bRegistered;
	bool		m_bCreated;

public:
	static LRESULT CALLBACK	stWndProc(HWND, UINT, WPARAM, LPARAM);
	LRESULT CALLBACK		WndProc(HWND, UINT, WPARAM, LPARAM);
	static INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

	Window(HINSTANCE hInstance, const WNDCLASSEX* wcx = NULL, const RECT* Dimensions = NULL, bool bDisplay=false);
	bool RegisterWindow();
	bool Create();

	inline static Window* GetObjectFromWindow(HWND hWnd)
	{
		return (Window*)GetWindowLong(hWnd, GWL_USERDATA);
	}

	void SetWindowTitle(char* lpszTitle) 
	{
		ZeroMemory(m_szTitle, sizeof(char)*MAX_LOADSTRING);
		strcpy_s(m_szTitle, lpszTitle);
	}

	bool Window::Show(const bool p_bDisplay=true);
};