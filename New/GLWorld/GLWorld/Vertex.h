//Vertex.h

#pragma once

#include "Color.h"
#include "Vector.h"

struct Vertex
{
	double wx,wy,wz;

	Vertex( void ) : wx( 0 ), wy( 0 ), wz( 0 )
	{
	}
	Vertex( double x, double y, double z ) : wx( x ), wy( y ), wz( z )
	{
	}

	Vertex& operator += (const Vertex& v)        {wx+=v.wx; wy+=v.wy; wz+=v.wz; return *this;}
	Vertex& operator /= (const float f)        {wx/=f; wy/=f; wz/=f; return *this;}

	operator Vector& ()                          {return Vector(wx,wy,wz);}
};

inline bool operator == (const Vertex& a, const Vertex& b){return a.wx==b.wx && a.wy==b.wy && a.wz==b.wz;}

inline Vertex operator - (const Vertex& a, const Vertex& b)        {return Vertex(a.wx-b.wx, a.wy-b.wy,a.wz-b.wz);}
inline Vertex operator + (const Vertex& a, const Vertex& b)        {return Vertex(a.wx+b.wx, a.wy+b.wy,a.wz+b.wz);}
inline Vertex operator + (const Vertex& a, const Vector& b)        {return Vertex(a.wx+b.x, a.wy+b.y,a.wz+b.z);}
inline Vertex operator * (const Vertex& a, const Vector& b)        {return Vertex(a.wx*b.x, a.wy*b.y,a.wz*b.z);}
inline Vertex Cross (const Vertex& a, const Vertex& b)
{
	return Vertex(
		a.wy*b.wz-a.wz*b.wy,
		a.wz*b.wx-a.wx*b.wz,
		a.wx*b.wy-a.wy*b.wx);
}

inline Vertex Normal (const Vertex& a)
{
	double length=sqrt(a.wx*a.wx+a.wy*a.wy+a.wz*a.wz);
	return Vertex(a.wx/length,a.wy/length,a.wz/length);
}