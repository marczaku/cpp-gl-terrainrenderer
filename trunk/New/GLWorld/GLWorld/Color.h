// Color.h

#pragma once

#include <math.h>

#define ColFToByte 255
#define ColByteToF (0.003921568627450980392156862745098f)


class Color
{
public:
	char  r, g, b, a;

	Color(){}

	//byte constructors
	Color(const char _r, const char _g, char const _b) : r(_r), g(_g), b(_b){}
	Color(const char _r, const char _g, char const _b, const char _a) : r(_r), g(_g), b(_b), a(_a){}
	Color(const char* _rgba) : r(_rgba[0]), g(_rgba[1]), b(_rgba[2]), a(_rgba[3]){}


	Color& operator = (const Color& c)                                              {r=c.r,g=c.g,b=c.b,a=c.a;return *this;}

	Color& operator += (const Color& c)                                             {r+=c.r,g+=c.g,b+=c.b,a+=c.a;return *this;}

	Color& operator -= (const Color& c)                                             {r-=c.r,g-=c.g,b-=c.b,a-=c.a;return *this;}
};

inline Color operator + (const Color& a, const Color& b)        {return Color(a.r+b.r, a.g+b.g,a.b+b.b+a.a+b.a);}
inline Color operator - (const Color& a, const Color& b)        {return Color(a.r-b.r, a.g-b.g,a.b-b.b+a.a-b.a);}
inline Color operator - (const Color& c)                                        {return Color(-c.r,-c.g,-c.b,-c.a);}

inline bool operator == (const Color& a, const Color& b){return a.r==b.r && a.g==b.g && a.b==b.b && a.a==b.a;}
inline bool operator != (const Color& a, const Color& b){return a.r!=b.r || a.g!=b.g || a.b!=b.b || a.a!=b.a;}