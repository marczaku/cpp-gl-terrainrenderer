//GLWindow.cpp

#include "stdafx.h"
#include "GLWindow.h"

GLWindow::GLWindow(HINSTANCE hInstance, const WNDCLASSEX* wcx, const RECT* Dimensions, bool bDisplay) : Window(hInstance,wcx,Dimensions,bDisplay)
{

}
//---------------------------------------------------
GLWindow::~GLWindow()
{
	if (m_hRC)
	{
		wglMakeCurrent(NULL,NULL);
		wglDeleteContext(m_hRC);
		m_hRC=NULL;
	}
	if (m_hDC)
		ReleaseDC(m_hWnd,m_hDC);
}
//---------------------------------------------------
bool GLWindow::Create()
{
	if(!Window::Create())
		return false;

	static	PIXELFORMATDESCRIPTOR pfd=				// pfd Tells Windows How We Want Things To Be
	{
		sizeof(PIXELFORMATDESCRIPTOR),				// Size Of This Pixel Format Descriptor
		1,											// Version Number
		PFD_DRAW_TO_WINDOW |						// Format Must Support Window
		PFD_SUPPORT_OPENGL |						// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,							// Must Support Double Buffering
		PFD_TYPE_RGBA,								// Request An RGBA Format
		32,											// Select Our Color Depth
		0, 0, 0, 0, 0, 0,							// Color Bits Ignored
		0,											// No Alpha Buffer
		0,											// Shift Bit Ignored
		0,											// No Accumulation Buffer
		0, 0, 0, 0,									// Accumulation Bits Ignored
		16,											// 16Bit Z-Buffer (Depth Buffer)  
		0,											// No Stencil Buffer
		0,											// No Auxiliary Buffer
		PFD_MAIN_PLANE,								// Main Drawing Layer
		0,											// Reserved
		0, 0, 0										// Layer Masks Ignored
	};
	if(!(m_hDC=GetDC(m_hWnd))){ return false;}
	if(!(m_PixelFormat=ChoosePixelFormat(m_hDC,&pfd))){ return false;}
	if(!(SetPixelFormat(m_hDC,m_PixelFormat,&pfd))){ return false;}
	if(!(m_hRC=wglCreateContext(m_hDC))){ return false;}
	if(!(wglMakeCurrent(m_hDC,m_hRC))){ return false;}
	OnResize(800,600);
	return true;
}
//---------------------------------------------------
void GLWindow::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
//---------------------------------------------------
void GLWindow::Swap()
{
	SwapBuffers(m_hDC);
}
//---------------------------------------------------
void GLWindow::OnResize(int NewWidth, int NewHeight)
{
	glViewport(0,0,NewWidth,NewHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f,(GLfloat)NewWidth/(GLfloat)NewHeight,0.01f,1000.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}