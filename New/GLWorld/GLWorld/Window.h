//Window.h

#pragma once
#include "stdafx.h"
#include <functional>

#define MAX_LOADSTRING 100

LRESULT DefWndProc(HWND, UINT, WPARAM, LPARAM);

class Window
{
protected:
	HINSTANCE	m_hInst;
	HWND		m_hWnd;
	TCHAR		m_szTitle[MAX_LOADSTRING];
	WNDCLASSEX	m_wcx;
	RECT		m_Dimensions;
	DWORD		m_Styles;
	bool		m_bRegistered;
	bool		m_bCreated;
	typedef std::tr1::function<LRESULT (HWND, UINT, WPARAM, LPARAM)> WndProcFunction;
	WndProcFunction m_WNdProcFunction;

public:
	Window(HINSTANCE hInstance, const WNDCLASSEX* wcx = NULL, const RECT* Dimensions = NULL, bool bDisplay=false);
	~Window();

	bool					RegisterWindow();
	virtual bool			Create();
	bool					Show(const bool p_bDisplay=true);

	inline static Window*	GetObjectFromWindow(HWND hWnd){ return (Window*)GetWindowLong(hWnd, GWL_USERDATA);}
	inline HWND				GetHandle() { return m_hWnd;}

	void SetWindowTitle(char* lpszTitle);
	void SetWndProcFunction(WndProcFunction ProcFunction);

protected:
	static LRESULT CALLBACK	stWndProc(HWND, UINT, WPARAM, LPARAM);
};