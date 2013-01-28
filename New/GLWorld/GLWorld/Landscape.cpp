// Landscape.cpp

#include "stdafx.h"
#include "Landscape.h"
#include "gl/GL.h"

Landscape::Landscape()
{
	m_Position = Vector(0.0,0.0,0.0);
	m_Width=0;
	m_Length=0;
	m_Scale= Vector(1.0,1.0,1.0);
}

Landscape::Landscape(int Width, int Length)
{
	m_Position = Vector(0.0,0.0,0.0);
	m_Scale= Vector(1.0,1.0,1.0);
	m_Width=Width;
	m_Length=Length;
	m_NumVerts=(m_Width+1)*(m_Length+1);
	m_Verts = new Vertex[m_NumVerts];
	int i=0;
	for(double x=-(double)Width*0.5;x<=(double)Width*0.5;x++)
	{
		for(double y=-(double)Length*0.5;y<=(double)Length*0.5;y++)
		{
			m_Verts[i] = Vertex(x,y,0.0)*m_Scale+m_Position;
			i++;
		}
	}
}

void Landscape::LoadHeights(char* FileName)
{

}

void Landscape::Draw()
{
	glBegin(GL_POINTS);
	for(int i=0;i<m_NumVerts;i++)
	{
		glVertex3d(m_Verts[i].wx,m_Verts[i].wy,m_Verts[i].wz);
	}
	glEnd();
}