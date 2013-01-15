#ifndef VERTEX_H
#define VERTEX_H

//#include <gl/GL.h>
#include "Color.h"
#include "Vector.h"

struct vertex
{
	GLdouble wx, wy, wz;
	GLdouble u,v;
	GLdouble u2,v2;
	vector n;
	Color col;

	vertex( void ) : wx( 0 ), wy( 0 ), wz( 0 ) { }
	vertex( GLdouble x, GLdouble y, GLdouble z ) : wx( x ), wy( y ), wz( z ) { }

	vertex& operator += (const vertex& v)        {wx+=v.wx; wy+=v.wy; wz+=v.wz; return *this;}
	vertex& operator /= (const float f)        {wx/=f; wy/=f; wz/=f; return *this;}

	operator vector& ()                          {return vector(wx,wy,wz);}
};

inline bool operator == (const vertex& a, const vertex& b){return a.wx==b.wx && a.wy==b.wy && a.wz==b.wz;}

inline vertex operator - (const vertex& a, const vertex& b)        {return vertex(a.wx-b.wx, a.wy-b.wy,a.wz-b.wz);}
inline vertex operator + (const vertex& a, const vertex& b)        {return vertex(a.wx+b.wx, a.wy+b.wy,a.wz+b.wz);}
inline vertex Cross (const vertex& a, const vertex& b)
{
	return vertex(
		a.wy*b.wz-a.wz*b.wy,
		a.wz*b.wx-a.wx*b.wz,
		a.wx*b.wy-a.wy*b.wx);
}

inline vertex Normal (const vertex& a)
{
	double length=sqrt(a.wx*a.wx+a.wy*a.wy+a.wz*a.wz);
	return vertex(a.wx/length,a.wy/length,a.wz/length);
}

#endif