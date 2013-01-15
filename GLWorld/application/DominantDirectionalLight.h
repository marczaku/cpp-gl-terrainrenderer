#ifndef DOMINANT_DIRECTIONAL_LIGHT
#define DOMINANT_DIRECTIONAL_LIGHT

#include "gl/GL.h"
#include "Vector.h"
#include "Color.h"
#include "matrix.h"

class DominantDirectionalLight
{
public:
	vertex m_Position;
	vector m_Direction;
	vector m_Color;

	DominantDirectionalLight()
	{
		m_Position=vertex(0,0,0);
		m_Direction=vector(0,0,0);
		m_Color=vector(0,0,0);
	}

	int Draw(bool bFilled, bool bDrawNormals=false)
	{
		glPointSize(10);
		glColor3ub(255,255,255);
		glBegin( GL_POINTS );
		glVertex3d(m_Position.wx,m_Position.wy,m_Position.wz);
		glEnd();
		glBegin( GL_LINES );
		glVertex3d(m_Position.wx,m_Position.wy,m_Position.wz);
		glVertex3d(m_Position.wx+m_Direction.wx,m_Position.wy+m_Direction.wy,m_Position.wz+m_Direction.wz);
		glEnd();
		return true;
	}

	int Transform(matrix a)
	{
		m_Position=a*m_Position;
		m_Direction=a*m_Direction;
		return true;
	}
	
	void rotate_x( GLdouble alpha )
	{
		matrix a;
		a.rotate_x(alpha);
		m_Direction=a*m_Direction;
	}
    void rotate_y( GLdouble alpha )
	{
		matrix a;
		a.rotate_y(alpha);
		m_Direction=a*m_Direction;
	}
    void rotate_z( GLdouble alpha )
	{
		matrix a;
		a.rotate_z(alpha);
		m_Direction=a*m_Direction;
	}
};

#endif