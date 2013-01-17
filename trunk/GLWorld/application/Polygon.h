#ifndef POLYGON_H
#define POLYGON_H

#include "Vertex.h"
#include "Color.h"
#include <gl/GL.h>
extern GLint g_hW1,g_hW2,g_hW3,g_hW4;

//CPolygon-Class (Compiler was bitching around, if I named it CPolygon, too lazy to find the error's source ;)
class CPolygon
{
public:
	int* Indices;
	int Size;
	Color col;
	vector n;
	vertex center;

	int Create(int _Size, int* _Indices, vertex* Vertices=0)
	{
		Size=_Size;
		Indices=_Indices;
		col.r=1;
		col.g=1;
		col.b=1;

		if(Vertices!=0)
		{
			n=Normal(Cross(Normal((vector)(Vertices[Indices[0]]-Vertices[Indices[1]])),Normal(vector(Vertices[Indices[2]]-Vertices[Indices[1]]))));
			center=vertex(0,0,0);
			for(int i=0;i<Size;i++)
				center+=Vertices[Indices[i]];
			center/=(float)Size;
		}

		return true;
	}

	int Draw(vertex* Vertices, bool bFilled, bool bDrawNormal=false)
	{
		if(bDrawNormal)
		{
			for(int i=0;i<Size;i++)
			{
				glBegin( GL_LINES );
				glVertex3d(Vertices[Indices[i]].wx,Vertices[Indices[i]].wy,Vertices[Indices[i]].wz);
				glVertex3d(Vertices[Indices[i]].wx-Vertices[Indices[i]].n.wx/25,Vertices[Indices[i]].wy-Vertices[Indices[i]].n.wy/25,Vertices[Indices[i]].wz-Vertices[Indices[i]].n.wz/25);
				glEnd();
			}
		}

		if(bFilled)
			glBegin( GL_POLYGON );
		else
			glBegin( GL_LINE_LOOP );
		for(int i=0;i<Size;i++)
		{
			glNormal3d(Vertices[Indices[i]].n.wx,Vertices[Indices[i]].n.wy,Vertices[Indices[i]].n.wz);
			glMultiTexCoord2d(GL_TEXTURE0,Vertices[Indices[i]].u,Vertices[Indices[i]].v);
			glVertexAttrib1f(g_hW1,Vertices[Indices[i]].w[0]);
			glVertexAttrib1f(g_hW2,Vertices[Indices[i]].w[1]);
			glVertexAttrib1f(g_hW3,Vertices[Indices[i]].w[2]);
			glVertexAttrib1f(g_hW4,Vertices[Indices[i]].w[3]);
			glColor3ub(Vertices[Indices[i]].col.r,Vertices[Indices[i]].col.g,Vertices[Indices[i]].col.b);
			glVertex3d(Vertices[Indices[i]].wx,Vertices[Indices[i]].wy,Vertices[Indices[i]].wz);
		}
		glEnd();
		return true;
	}
};

#endif