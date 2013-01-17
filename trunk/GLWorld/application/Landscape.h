#ifndef LANDSCAPE_H
#define LANDSCAPE_H

#include "Vertex.h"
#include "picture.h"
#include "Polygon.h"
#include "matrix.h"

#define LANDSCAPE_MAXHEIGHT (255+255+255)

class Landscape
{
private:

	int m_PolyCount;
	int m_VertCount;

	int* m_VertIndices;
	vertex* m_Verts;
	CPolygon* m_Polys;
	int m_xSize, m_ySize;
	picture m_HeightMap;
	picture m_HeightTex;

public:

	float TotalRot;

	Landscape()
	{
		m_Verts=0;
		m_VertIndices=0;
		m_Polys=0;
		SetHeightMap("D://height_colors.bmp");
	}
	Landscape(int xSize, int ySize) : m_xSize(xSize), m_ySize(ySize)
	{
		m_Verts=0;
		m_VertIndices=0;
		m_Polys=0;
		SetHeightMap("D://height_colors.bmp");
	}
	Landscape(int xSize, int ySize, char* HeightMapSourcePath) : m_xSize(xSize), m_ySize(ySize)
	{
		m_Verts=0;
		m_VertIndices=0;
		m_Polys=0;
		SetHeightMap(HeightMapSourcePath);
	}

	int Draw(bool bFilled, bool bDrawNormals=false)
	{
		for(int i=0;i<m_PolyCount;i++)
			m_Polys[i].Draw(m_Verts, bFilled, bDrawNormals);
		return true;
	}

	
	int Transform(matrix a)
	{
		for(int i=0;i<m_VertCount;i++)
		{
			m_Verts[i]=a*m_Verts[i];
			m_Verts[i].n=a*m_Verts[i].n;
		}
		for(int i=0;i<m_PolyCount;i++)
		{
			m_Polys[i].center=a*m_Polys[i].center;
			m_Polys[i].n=a*m_Polys[i].n;
		}
		return true;
	}

	void SetHeightMap(char* HeightMapSourcePath)
	{
		m_HeightTex.load("D://height_colors.bmp");
		m_HeightMap.load(HeightMapSourcePath);
		ApplyHeightMap();
	}

	void ApplyHeightMap()
	{
		if(m_Verts!=0)
		{
			delete m_Verts;
			m_Verts=0;
		}
		if(m_VertIndices!=0)
		{
			delete m_VertIndices;
			m_VertIndices=0;
		}
		if(m_Polys!=0)
		{
			delete m_Polys;
			m_Polys=0;
		}
		/* Generate all vertices at their respective position */
		m_VertCount=m_xSize*m_ySize;
		m_Verts=new vertex[m_VertCount];
		for(int y=0;y<m_ySize;y++)
		{
			for(int x=0;x<m_xSize;x++)
			{
				m_Verts[y*m_xSize+x].wx=(float)x/10;
				m_Verts[y*m_xSize+x].wz=(float)y/10;
				m_Verts[y*m_xSize+x].u=(float)x/m_xSize*10;
				m_Verts[y*m_xSize+x].v=(float)y/m_ySize*10;

				m_Verts[y*m_xSize+x].wy=m_HeightMap.content[y*m_HeightMap.xsize+x].r+m_HeightMap.content[y*m_HeightMap.xsize+x].g+m_HeightMap.content[y*m_HeightMap.xsize+x].b;
				int test=(int)(m_Verts[y*m_xSize+x].wy/LANDSCAPE_MAXHEIGHT*m_HeightTex.xsize);
				m_Verts[y*m_xSize+x].col=m_HeightTex.content[test];
				m_Verts[y*m_xSize+x].wy-=255+200;
				m_Verts[y*m_xSize+x].wy/=500;
			}
		}
		/* Generate and fill the index-buffer and create the respective polygons */
		m_VertIndices=new int[(m_xSize-1)*(m_ySize-1)*5];	// Our Index Buffer containing 5 indices for 2 polygons, as we handle quads like this: //   0---1   
																																				   //   | / |
		m_PolyCount=(m_xSize-1)*(m_ySize-1)*2;				// Number of polygons of this landscape												   //   2---3
		m_Polys=new CPolygon[m_PolyCount];					// Array containing the polygons													   // IB: 02123 P1: 021 P2: 123

		for(int y=0;y<m_ySize-1;y++)
		{
			for(int x=0;x<m_xSize-1;x++)
			{
				// fill the index buffer with the data for this quad
				m_VertIndices[(y*(m_xSize-1)+x)*5]  =    y*m_xSize+x;
				m_VertIndices[(y*(m_xSize-1)+x)*5+1]=(y+1)*m_xSize+x;
				m_VertIndices[(y*(m_xSize-1)+x)*5+2]=    y*m_xSize+x+1;
				m_VertIndices[(y*(m_xSize-1)+x)*5+3]=(y+1)*m_xSize+x;
				m_VertIndices[(y*(m_xSize-1)+x)*5+4]=(y+1)*m_xSize+x+1;
				// create the 2 triangles by providing the vertex indices for this quad
				m_Polys[(y*(m_xSize-1)+x)*2  ].Create(3,m_VertIndices+(y*(m_xSize-1)+x)*5  , m_Verts);
				m_Polys[(y*(m_xSize-1)+x)*2+1].Create(3,m_VertIndices+(y*(m_xSize-1)+x)*5+2, m_Verts);
				// add the polygon-normal to all of it's vertices' normals
				m_Verts[    y*m_xSize+x  ].n+=m_Polys[(y*(m_xSize-1)+x)*2].n;
				m_Verts[(y+1)*m_xSize+x  ].n+=m_Polys[(y*(m_xSize-1)+x)*2].n;
				m_Verts[    y*m_xSize+x+1].n+=m_Polys[(y*(m_xSize-1)+x)*2].n;
				m_Verts[    y*m_xSize+x+1].n+=m_Polys[(y*(m_xSize-1)+x)*2+1].n;
				m_Verts[(y+1)*m_xSize+x  ].n+=m_Polys[(y*(m_xSize-1)+x)*2+1].n;
				m_Verts[(y+1)*m_xSize+x+1].n+=m_Polys[(y*(m_xSize-1)+x)*2+1].n;
			}
		}
		// Normalize all vertex normals
		for(int y=0;y<m_ySize;y++)
			for(int x=0;x<m_xSize;x++)
				Normal(m_Verts[y*m_xSize+x].n);
	}
};

#endif