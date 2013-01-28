//Application.cpp
#include "stdafx.h"
#include "Application.h"

Application::Application(HINSTANCE hInstance)
{
	ZeroMemory(m_Keys,sizeof(bool)*256);
	m_Position = Vector(0.0,0.0,-30.0);
	m_Rotation = Vector(-63.0,0.0,-23.0);
	m_Velocity = Vector(0.0,0.0,0.0);
	m_RotVelocity = Vector(0.0,0.0,0.0);
	m_pInputManager = new InputManager();
	m_pWindow = new GLWindow(hInstance);
	m_pWindow->SetWndProcFunction(StWndProc, (void*)this);
	m_pWindow->Show();
}
//---------------------------------------------------
Application::~Application()
{
	delete m_pWindow;
	delete m_pInputManager;
}
//---------------------------------------------------
void Application::Init()
{
	glewInit();
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	m_pLandscape = new Landscape(10,10);
}
//---------------------------------------------------
void Application::Update(double DeltaTime)
{
	m_pInputManager->Update(DeltaTime);

	m_Velocity.z=m_pInputManager->m_aForward*0.01;
	m_Velocity.x=m_pInputManager->m_aStrafe*-0.01;

	m_Rotation.x+=m_pInputManager->m_MouseDeltaY*0.1;
	m_Rotation.z+=m_pInputManager->m_MouseDeltaX*0.1;

	m_pInputManager->m_MouseDeltaX=0.0f;
	m_pInputManager->m_MouseDeltaY=0.0f;

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
		glVertex3f(1.0*i,-10.0,0.0);
		glVertex3f(1.0*i, 10.0,0.0);
		glVertex3f(-10.0,1.0*i,0.0);
		glVertex3f( 10.0,1.0*i,0.0);
		if(i==0)
		{
			glEnd();
			glLineWidth(1);
			glBegin(GL_LINES);
		}
	}

	glVertex3f(.0,0.0,0.0);
	glVertex3f( 0.0,0.0,10.0);
	glEnd();
}
//---------------------------------------------------
void Application::Draw()
{
	m_pWindow->Clear();
	glLoadIdentity();
	glTranslatef(m_Position.x,m_Position.y,m_Position.z);
	glRotatef(m_Rotation.x,1.0,0.0,0.0);
	glRotatef(m_Rotation.y,0.0,1.0,0.0);
	glRotatef(m_Rotation.z,0.0,0.0,1.0);
	//DrawGrid();
	m_pLandscape->Draw();
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
		m_pInputManager->KeyDown(wParam);
		KeyDown(wParam);
		return 0;
	case WM_KEYUP:
		m_pInputManager->KeyUp(wParam);
		KeyUp(wParam);
		return 0;
	case WM_LBUTTONUP:
		m_pInputManager->MouseLeftUp();
		return 0;
	case WM_MOUSEMOVE:
		if(wParam==MK_LBUTTON)
			m_pInputManager->SetMousePos(LOWORD(lParam),HIWORD(lParam));
		return 0;
	case WM_SIZE:
		m_pWindow->OnResize(LOWORD(lParam),HIWORD(lParam));  // LoWord=Width, HiWord=Height
		return 0;
	}

	// Pass All Unhandled Messages To DefWindowProc
	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}