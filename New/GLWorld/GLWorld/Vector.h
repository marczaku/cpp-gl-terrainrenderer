// Vector.h

#pragma once

struct Vector
{
	double x, y, z;

	Vector( void ) : x( 0 ), y( 0 ), z( 0 ) { }
	Vector( double x, double y, double z ) : x( x ), y( y ), z( z ) { }

	Vector& operator += (const Vector& v)        {x+=v.x; y+=v.y; z+=v.z; return *this;}
	Vector& operator /= (const float f)			{x/=f; y/=f; z/=f; return *this;}
};

inline bool operator == (const Vector& a, const Vector& b){return a.x==b.x && a.y==b.y && a.z==b.z;}

inline Vector operator - (const Vector& a, const Vector& b)        {return Vector(a.x-b.x, a.y-b.y,a.z-b.z);}
inline Vector operator + (const Vector& a, const Vector& b)        {return Vector(a.x+b.x, a.y+b.y,a.z+b.z);}
inline Vector operator / (const Vector& a, const float f)			{return Vector(a.x/f, a.y/f,a.z/f);}
inline Vector operator * (const Vector& a, const float f)			{return Vector(a.x*f, a.y*f,a.z*f);}
inline Vector Cross (const Vector& a, const Vector& b)
{
	return Vector(
		a.y*b.z-a.z*b.y,
		a.z*b.x-a.x*b.z,
		a.x*b.y-a.y*b.x);
}

inline float Dot (const Vector& a, const Vector& b)
{
	return 
		a.x*b.x+a.y*b.y+a.z*b.z;
}

inline Vector Normal (const Vector& a)
{
	//double length=sqrt(a.wx*a.wx+a.wy*a.wy+a.wz*a.wz);
	//return vector(a.wx/length,a.wy/length,a.wz/length);
}