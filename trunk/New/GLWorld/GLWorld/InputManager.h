//Application.h

#pragma once
#include "stdafx.h"

class InputManager
{
public:
	bool		m_Keys[256];
	bool		m_MouseLeft;
	double		m_aForward;
	double		m_aStrafe;
	double		m_MouseX,m_MouseY;
	double		m_MouseDeltaX,m_MouseDeltaY;
	

public:
	InputManager();
	~InputManager();

	void Update(double DeltaTime);
	void KeyDown(int KeyNum);
	void KeyUp(int KeyNum);
	void SetMousePos(int MouseX, int MouseY);
	void MouseLeftUp();
};