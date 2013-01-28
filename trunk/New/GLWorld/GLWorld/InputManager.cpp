// InputManager.cpp

#include "stdafx.h"
#include "InputManager.h"

InputManager::InputManager()
{
	ZeroMemory(m_Keys,sizeof(bool)*256);
	m_MouseLeft=false;
	m_aForward=0.0;
	m_aStrafe=0.0;
	m_MouseDeltaX=0.0;
	m_MouseDeltaY=0.0;
	m_MouseX=0.0;
	m_MouseY=0.0;
}
InputManager::~InputManager()
{
	
}

void InputManager::Update(double DeltaTime)
{
	m_aForward=0.0;
	m_aStrafe=0.0;
	if(m_Keys['W']) m_aForward += 1.0;
	if(m_Keys['S']) m_aForward -= 1.0;
	if(m_Keys['A']) m_aStrafe  -= 1.0;
	if(m_Keys['D']) m_aStrafe  += 1.0;
}
void InputManager::KeyDown(int KeyNum)
{
	m_Keys[KeyNum]=true;
}
void InputManager::KeyUp(int KeyNum)
{
	m_Keys[KeyNum]=false;
}
void InputManager::MouseLeftUp()
{
	m_MouseLeft=false;
}
void InputManager::SetMousePos(int MouseX, int MouseY)
{
	if(m_MouseLeft)
	{
		m_MouseDeltaX=(double)MouseX-m_MouseX;
		m_MouseDeltaY=(double)MouseY-m_MouseY;
	}
	else
		m_MouseLeft=true;
	m_MouseX = MouseX;
	m_MouseY = MouseY;
}