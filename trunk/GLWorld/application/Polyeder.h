//#ifndef POLYEDER_H
//#define POLYEDER_H
//
//#include "Vertex.h"
//#include "Polygon.h"
//#include "matrix.h"
//
////Polyeder class
//class Polyeder
//{
//public:
//	vertex* Vertices;
//	CPolygon* CPolygons;
//	int VertCount;
//	int PolyCount;
//
//	int Create(int _VertCount, vertex* _Vertices, int _PolyCount, CPolygon* _CPolygons)
//	{
//		Vertices=_Vertices;
//		VertCount=_VertCount;
//		CPolygons=_CPolygons;
//		PolyCount=_PolyCount;
//		return true;
//	}
//
//	int Draw(bool bFilled)
//	{
//		for(int i=0;i<PolyCount;i++)
//			CPolygons[i].Draw(Vertices, bFilled);
//		return true;
//	}
//
//	int Transform(matrix a)
//	{
//		for(int i=0;i<VertCount;i++)
//			Vertices[i]=a*Vertices[i];
//		return true;
//	}
//};
//
//#define PHI 1.618033988749895f //phi is the length of the long side of a
//
//Polyeder g_mypolyeder;
//Polyeder g_mytetraeder;
//Polyeder g_myicosaeder;
//CPolygon  g_cube_sides[6];
//CPolygon  g_tetraeder_polys[4];
//CPolygon  g_icosaeder_polys[20];
//
////These are the coords of all neccessary CPolygons
//vertex cube_coords[8] =
//{
//	vertex(  20,  20,  20 ),
//	vertex(  20,  20, -20 ),
//	vertex(  20, -20,  20 ),
//	vertex(  20, -20, -20 ),
//	vertex( -20,  20,  20 ),
//	vertex( -20,  20, -20 ),
//	vertex( -20, -20,  20 ),
//	vertex( -20, -20, -20 )
//};
//
//vertex isocaeder_coords[12]=
//{
//	vertex(-PHI/2.0f,0.5f,0.0f),
//	vertex(-PHI/2.0f,-0.5f,0.0f),
//	vertex(PHI/2.0f,-0.5f,0.0f),
//	vertex(PHI/2.0f,0.5f,0.0f),
//	vertex(0.0f,-PHI/2.0f,0.5f),
//	vertex(0.0f,-PHI/2.0f,-0.5f),
//	vertex(0.0f,PHI/2.0f,-0.5f),
//	vertex(0.0f,PHI/2.0f,0.5f),
//	vertex(0.5f ,0.0f,-PHI/2.0f),      
//	vertex(-0.5f,0.0f,-PHI/2.0f),	  
//	vertex(-0.5f,0.0f,PHI/2.0f ),	  
//	vertex(0.5f ,0.0f,PHI/2.0f )		  
//};
//
//// these are the vertex-indices of all CPolygons
//int cube_front[4]={1,3,7,5};
//int cube_back[4]={4,6,2,0};
//int cube_left[4]={5,7,6,4};
//int cube_right[4]={0,2,3,1};
//int cube_top[4]={0,1,5,4};
//int cube_bottom[4]={3,2,6,7};
//int tetraeder_a[3]={0,6,3};
//int tetraeder_b[3]={5,6,0};
//int tetraeder_c[3]={5,3,6};
//int tetraeder_d[3]={0,3,5};
//int icosaeder_plane_a[4]={0,1,2,3};
//int icosaeder_plane_b[4]={4,5,6,7};
//int icosaeder_plane_c[4]={8,9,10,11};
//int isocaeder_a[3]={10,11,7};
//int isocaeder_b[3]={7,11,3};
//int isocaeder_c[3]={7,3,6};
//int isocaeder_d[3]={7,6,0};
//int isocaeder_e[3]={7,0,10};
//int isocaeder_f[3]={11,2,3};
//int isocaeder_g[3]={11,4,2};
//int isocaeder_h[3]={10,4,11};
//int isocaeder_i[3]={10,1,4};
//int isocaeder_j[3]={10,0,1};
//int isocaeder_k[3]={3,2,8};
//int isocaeder_l[3]={0,9,1};
//int isocaeder_m[3]={2,5,8};
//int isocaeder_n[3]={8,5,9};
//int isocaeder_o[3]={9,5,1};
//int isocaeder_p[3]={4,5,2};
//int isocaeder_q[3]={5,4,1};
//int isocaeder_r[3]={8,9,6};
//int isocaeder_s[3]={6,3,8};
//int isocaeder_t[3]={6,9,0};
//
//void InitCube()
//{
//	/*
//	g_cube_sides[0].Create(4,cube_top); g_cube_sides[0].Color[0]=255;
//	g_cube_sides[1].Create(4,cube_bottom); g_cube_sides[1].Color[1]=255;
//	g_cube_sides[2].Create(4,cube_left); g_cube_sides[2].Color[2]=255;
//	g_cube_sides[3].Create(4,cube_right); g_cube_sides[3].Color[2]=255; g_cube_sides[3].Color[1]=255;
//	g_cube_sides[4].Create(4,cube_front); g_cube_sides[4].Color[2]=255; g_cube_sides[4].Color[2]=255;
//	g_cube_sides[5].Create(4,cube_back); g_cube_sides[5].Color[0]=255; g_cube_sides[5].Color[2]=255;
//	g_mypolyeder.Create(8,cube_coords,6,g_cube_sides);*/
//}
//
//void InitTetraeder()
//{
//	/*
//	g_tetraeder_polys[0].Create(3,tetraeder_a); g_tetraeder_polys[0].Color[0]=255;
//	g_tetraeder_polys[1].Create(3,tetraeder_b); g_tetraeder_polys[1].Color[1]=255;
//	g_tetraeder_polys[2].Create(3,tetraeder_c); g_tetraeder_polys[2].Color[2]=255;
//	g_tetraeder_polys[3].Create(3,tetraeder_d); g_tetraeder_polys[3].Color[1]=255; g_tetraeder_polys[3].Color[0]=255;
//	g_mytetraeder.Create(8,cube_coords,4,g_tetraeder_polys);*/
//}
//
//void InitIcosaeder()
//{
//	g_icosaeder_polys[ 0].Create(3,isocaeder_a);
//	g_icosaeder_polys[ 1].Create(3,isocaeder_b);
//	g_icosaeder_polys[ 2].Create(3,isocaeder_c);
//	g_icosaeder_polys[ 3].Create(3,isocaeder_d);
//	g_icosaeder_polys[ 4].Create(3,isocaeder_e);
//	g_icosaeder_polys[ 5].Create(3,isocaeder_f);
//	g_icosaeder_polys[ 6].Create(3,isocaeder_g);
//	g_icosaeder_polys[ 7].Create(3,isocaeder_h);
//	g_icosaeder_polys[ 8].Create(3,isocaeder_i);
//	g_icosaeder_polys[ 9].Create(3,isocaeder_j);
//	g_icosaeder_polys[10].Create(3,isocaeder_k);
//	g_icosaeder_polys[11].Create(3,isocaeder_l);
//	g_icosaeder_polys[12].Create(3,isocaeder_m);
//	g_icosaeder_polys[13].Create(3,isocaeder_n);
//	g_icosaeder_polys[14].Create(3,isocaeder_o);
//	g_icosaeder_polys[15].Create(3,isocaeder_p);
//	g_icosaeder_polys[16].Create(3,isocaeder_q);
//	g_icosaeder_polys[17].Create(3,isocaeder_r);
//	g_icosaeder_polys[18].Create(3,isocaeder_s);
//	g_icosaeder_polys[19].Create(3,isocaeder_t);
//	int random_color=0;
//	for(int i=0;i<20;i++)
//	{
//		random_color=rand()%205+50;
//		g_icosaeder_polys[i].col.r=random_color;
//		g_icosaeder_polys[i].col.g=random_color;
//		g_icosaeder_polys[i].col.b=random_color;
//	}
//	g_myicosaeder.Create(12,isocaeder_coords,20,g_icosaeder_polys);
//}
//
//
//#endif