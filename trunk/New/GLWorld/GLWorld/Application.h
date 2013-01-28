//Application.h

#pragma once
#include "stdafx.h"
#include "GLWindow.h"
#include "InputManager.h"
#include <gl\glew.h>
#include "Vector.h"
#include "Landscape.h"

class Application
{
private:
	GLWindow*		m_pWindow;
	InputManager*	m_pInputManager;
	bool			m_bRunning;
	float			m_x,m_y,m_z;
	bool			m_Keys[256];
	Vector			m_Position;
	Vector			m_Rotation;
	Vector			m_RotVelocity;
	Vector			m_Velocity;
	Landscape*		m_pLandscape;

public:
	Application(HINSTANCE hInstance);
	~Application();

	void Init();
	void Update(double DeltaTime);
	void Draw();
	void KeyDown(int KeyIdx);
	void KeyUp(int KeyIdx);
	static LRESULT CALLBACK StWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, void* WndProcOwner);
	LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};