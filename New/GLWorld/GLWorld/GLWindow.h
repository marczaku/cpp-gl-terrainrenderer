//GLWindow.h

#pragma once
#include "stdafx.h"
#include "Window.h"
#include <gl\glew.h>


class GLWindow : public Window
{
private:
	HDC			m_hDC;
	HGLRC		m_hRC;
	GLuint		m_PixelFormat;

public:
	GLWindow(HINSTANCE hInstance, const WNDCLASSEX* wcx = NULL, const RECT* Dimensions = NULL, bool bDisplay=false);
	~GLWindow();
	virtual bool Create();
	void Clear();
	void Swap();
};