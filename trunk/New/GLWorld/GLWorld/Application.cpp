//Application.cpp
#include "stdafx.h"
#include "Application.h"

Application::Application(HINSTANCE hInstance)
{
	ZeroMemory(m_Keys,sizeof(bool)*256);
	m_Position = Vector(0.0f,0.0f,-30.0f);
	m_Velocity = Vector(0.0f,0.0f,0.0f);
	m_pWindow = new GLWindow(hInstance);
	m_pWindow->SetWndProcFunction(StWndProc, (void*)this);
	m_pWindow->Show();
}
//---------------------------------------------------
Application::~Application()
{
	delete m_pWindow;
}
//---------------------------------------------------
GLvoid ReSizeGLScene(GLsizei width, GLsizei height)		// Resize And Initialize The GL Window
{
	glViewport(0,0,width,height);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	// Calculate The Aspect Ratio Of The Window
	gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.01f,1000.0f);

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
}
//---------------------------------------------------
void Application::Init()
{
	glewInit();
	ReSizeGLScene(800,600);
	/*
	glViewport(0,0,800,600);
	glMatrixMode( GL_MODELVIEW );
	glClearColor(0.5f,0.5f,0.5f,1.0f);
	glLoadIdentity();
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	gluPerspective( 70, GLdouble( 800 ) / 600, 0.01, 10000.0 );*/
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}
//---------------------------------------------------
void Application::Update(double DeltaTime)
{
	m_Velocity=Vector(0.0f,0.0f,0.0f);
	m_RotVelocity=Vector(0.0f,0.0f,0.0f);
	if(m_Keys['W']) m_Velocity.z+= 0.01f;
	if(m_Keys['S']) m_Velocity.z-= 0.01f;
	if(m_Keys['A']) m_Velocity.x+= 0.01f;
	if(m_Keys['D']) m_Velocity.x-= 0.01f;
	if(m_Keys['J']) m_RotVelocity.x+= 0.01f;
	if(m_Keys['U']) m_RotVelocity.x-= 0.01f;
	if(m_Keys['H']) m_RotVelocity.z+= 0.01f;
	if(m_Keys['K']) m_RotVelocity.z-= 0.01f;
	m_Rotation+=m_RotVelocity*DeltaTime;
	m_Position+=m_Velocity*DeltaTime;
}
//---------------------------------------------------
void DrawGrid()
{
	glLineWidth(1);
	glBegin(GL_LINES);
	for(int i=-10;i<=10;i++)
	{
		if(i==0)
		{
			glEnd();
			glLineWidth(2);
			glBegin(GL_LINES);
		}
		glVertex3f(1.0f*i,-10.0f,0.0f);
		glVertex3f(1.0f*i, 10.0f,0.0f);
		glVertex3f(-10.0f,1.0f*i,0.0f);
		glVertex3f( 10.0f,1.0f*i,0.0f);
		if(i==0)
		{
			glEnd();
			glLineWidth(1);
			glBegin(GL_LINES);
		}
	}
	glEnd();
}
//---------------------------------------------------
void Application::Draw()
{
	m_pWindow->Clear();
	glLoadIdentity();
	glTranslatef(m_Position.x,m_Position.y,m_Position.z);
	glRotatef(m_Rotation.x,1.0f,0.0f,0.0f);
	glRotatef(m_Rotation.y,0.0f,1.0f,0.0f);
	glRotatef(m_Rotation.z,0.0f,0.0f,1.0f);
	DrawGrid();
	glEnd();
	m_pWindow->Swap();
}
//---------------------------------------------------
void Application::KeyDown(int KeyIdx)
{

}
//---------------------------------------------------
void Application::KeyUp(int KeyIdx)
{

}
//---------------------------------------------------
LRESULT CALLBACK Application::StWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, void* WndProcOwner)
{
	if(WndProcOwner!=0)
		return ((Application*)WndProcOwner)->WndProc(hWnd,uMsg,wParam,lParam);
	else
		return DefWindowProc(hWnd,uMsg,wParam,lParam);
}
//---------------------------------------------------
LRESULT CALLBACK Application::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
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
		m_Keys[wParam] = true;
		KeyDown(wParam);
		return 0;
	case WM_KEYUP:
		m_Keys[wParam] = false;
		KeyUp(wParam);
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
	case WM_SIZE:
		ReSizeGLScene(LOWORD(lParam),HIWORD(lParam));  // LoWord=Width, HiWord=Height
		return 0;
	}

	// Pass All Unhandled Messages To DefWindowProc
	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}