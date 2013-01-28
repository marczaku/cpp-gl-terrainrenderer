// Landscape.h

#pragma once

#include "Vector.h"
#include "Picture.h"
#include "Vertex.h"

class Landscape
{
public:
	Vector	m_Position;
	int		m_Width;
	int		m_Length;
	Vector	m_Scale;
	Picture	m_HeightData;
	Vertex*	m_Verts;
	int		m_NumVerts;

	Landscape();
	Landscape(int Width, int Length);

	void LoadHeights(char* FileName);
	void Draw();
};