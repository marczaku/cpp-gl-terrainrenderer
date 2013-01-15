#ifndef VECTOR_H
#define VECTOR_H

#include <gl/GL.h>

struct vector
{
	GLdouble wx, wy, wz;

	vector( void ) : wx( 0 ), wy( 0 ), wz( 0 ) { }
	vector( GLdouble x, GLdouble y, GLdouble z ) : wx( x ), wy( y ), wz( z ) { }

	vector& operator += (const vector& v)        {wx+=v.wx; wy+=v.wy; wz+=v.wz; return *this;}
	vector& operator /= (const float f)        {wx/=f; wy/=f; wz/=f; return *this;}
};

inline bool operator == (const vector& a, const vector& b){return a.wx==b.wx && a.wy==b.wy && a.wz==b.wz;}

inline vector operator - (const vector& a, const vector& b)        {return vector(a.wx-b.wx, a.wy-b.wy,a.wz-b.wz);}
inline vector operator + (const vector& a, const vector& b)        {return vector(a.wx+b.wx, a.wy+b.wy,a.wz+b.wz);}
inline vector operator / (const vector& a, const float f)        {return vector(a.wx/f, a.wy/f,a.wz/f);}
inline vector operator * (const vector& a, const float f)        {return vector(a.wx*f, a.wy*f,a.wz*f);}
inline vector Cross (const vector& a, const vector& b)
{
	return vector(
		a.wy*b.wz-a.wz*b.wy,
		a.wz*b.wx-a.wx*b.wz,
		a.wx*b.wy-a.wy*b.wx);
}

inline vector Normal (const vector& a)
{
	double length=sqrt(a.wx*a.wx+a.wy*a.wy+a.wz*a.wz);
	return vector(a.wx/length,a.wy/length,a.wz/length);
}

#endif