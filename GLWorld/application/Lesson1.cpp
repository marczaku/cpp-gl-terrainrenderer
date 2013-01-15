#include <windows.h>		// Header File For Windows
#include <gl\glew.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library
#include <math.h>
#include "screen_interface.h"
#include "Landscape.h"
#include "utility_functions.h"
#include "DominantDirectionalLight.h"

/* Configuration globals */
bool	g_WireFrameMode=true; //F2
bool	g_DrawNormals=false; //F3

long long previousTime;
long long currentTime;
double secondsPerCount;
double deltaTime;

GLint g_hDominantLightDirection;
Landscape* g_Landscape;
DominantDirectionalLight* g_DominantDirectionalLight;
matrix g;
LPPOINT g_OldPoint;
LPPOINT g_NewPoint;
CPolygon g_Square;
GLint   g_hTime;
float	g_fTime;
int		g_iTimeDir;
float	g_newRot;
bool	g_bF2Down=false;
bool	g_bF3Down=false;

vector g_Velocity,g_Acceleration,g_MaxVelocity;

int UpdateGLScene(double deltaTime)
{
	g_fTime+=g_iTimeDir*static_cast<float>(deltaTime);
	if(g_fTime>=1.0f)
	{
		g_iTimeDir=-1;
		g_fTime=1.0f;
	}
	else if(g_fTime<=0.0f)
	{
		g_iTimeDir=1;
		g_fTime=0.0f;
	}
	glUniform1f( g_hTime, g_fTime);
	glUniform3f( g_hDominantLightDirection, g_DominantDirectionalLight->m_Direction.wx, g_DominantDirectionalLight->m_Direction.wy, g_DominantDirectionalLight->m_Direction.wz);

	g_Landscape->Transform(g);
	g_DominantDirectionalLight->Transform(g);
	g_Landscape->TotalRot=g_newRot;
	g.clear();
	return TRUE;
}

int DrawGLScene(GLvoid)									// Here's Where We Do All The Drawing
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	g_Landscape->Draw(g_WireFrameMode,g_DrawNormals);
	//glUniform3f( g_hTime, 0, 0, 0 );
	g_DominantDirectionalLight->Draw(g_WireFrameMode,g_DrawNormals);

	return TRUE;										// Keep Going
}

int InitGL(GLvoid)										// All Setup For OpenGL Goes Here
{
	g_fTime=0;
	glewInit();
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	gluPerspective( 70, GLdouble( x_res ) / y_res, 0.01, 10000.0 );
	
	
	{
		glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );

		picture surface( "D://surface.bmp" );

		GLuint texture_id;
		glActiveTexture(GL_TEXTURE0);
		glGenTextures( 1, &texture_id );
		glBindTexture( GL_TEXTURE_2D, texture_id );

		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );

		glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, surface.xsize, surface.ysize, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface.content );
	
	}

	{
		glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );

		picture surface( "D://surface2.bmp" );

		GLuint texture_id;
		glActiveTexture(GL_TEXTURE1);
		glGenTextures( 1, &texture_id );
		glBindTexture( GL_TEXTURE_2D, texture_id );

		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );

		glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, surface.xsize, surface.ysize, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface.content );
	}

	{
		glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );

		picture surface( "D://weightmap.bmp" );

		GLuint texture_id;
		glActiveTexture(GL_TEXTURE2);
		glGenTextures( 1, &texture_id );
		glBindTexture( GL_TEXTURE_2D, texture_id );

		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );

		glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, surface.xsize, surface.ysize, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface.content );
	}

	GLuint prog=load_program("D://program2.vert","D://program2.frag");
	glUseProgram(prog);

	
	GLint texture_location = glGetUniformLocation( prog, "surface_texture" );
    if( texture_location == -1 ) exit_error( "Variable 'surface_texture' konnte im aktuellen Unterprogramm nicht erfasst werden.\n" );
    glUniform1i( texture_location, 0 );

	g_hDominantLightDirection = glGetUniformLocation( prog, "DominantLightDirection" );
    if( g_hDominantLightDirection == -1 ) exit_error( "Variable 'DominantLightDirection' konnte im aktuellen Unterprogramm nicht erfasst werden.\n" );
    glUniform3f( g_hTime, 0, 0, 0 );
	
	/*
	texture_location = glGetUniformLocation( prog, "surface_texture2" );
    if( texture_location == -1 ) exit_error( "Variable 'surface_texture2' konnte im aktuellen Unterprogramm nicht erfasst werden.\n" );
    glUniform1i( texture_location, 1 );

	texture_location = glGetUniformLocation( prog, "weight_texture" );
    if( texture_location == -1 ) exit_error( "Variable 'weight_texture' konnte im aktuellen Unterprogramm nicht erfasst werden.\n" );
    glUniform1i( texture_location, 2 );

	g_hTime = glGetUniformLocation( prog, "time" );
    if( g_hTime == -1 ) exit_error( "Variable 'time' konnte im aktuellen Unterprogramm nicht erfasst werden.\n" );
    glUniform1f( g_hTime, 0 );*/

	g_Landscape = new Landscape(257,257,"D://Heightmap.bmp");
	g_DominantDirectionalLight= new DominantDirectionalLight();
	g_DominantDirectionalLight->m_Position=vertex(0,10,0);
	g_DominantDirectionalLight->m_Direction=vector(0,-1,0);
	
	matrix a;
	a.translate(0.0f,0.0f,-15.0f);

	g_Landscape->Transform(a);
	g_DominantDirectionalLight->Transform(a);

	g.clear();
 
	return TRUE;										// Initialization Went OK
}

int WINAPI WinMain(	HINSTANCE	hInstance,			// Instance
					HINSTANCE	hPrevInstance,		// Previous Instance
					LPSTR		lpCmdLine,			// Command Line Parameters
					int			nCmdShow)			// Window Show State
{
	MSG		msg;									// Windows Message Structure
	BOOL	done=FALSE;								// Bool Variable To Exit Loop
	double	deltaTime;

	{
		long CountsPerSecond=0;
		QueryPerformanceCounter((LARGE_INTEGER*)&previousTime);
		QueryPerformanceFrequency((LARGE_INTEGER*)&CountsPerSecond); 
		secondsPerCount = 1.0 / (double)CountsPerSecond;
	}

	// Ask The User Which Screen Mode They Prefer
	bFullScreen =  !(MessageBox(NULL,"Would You Like To Run In Fullscreen Mode?", "Start FullScreen?",MB_YESNO|MB_ICONQUESTION)==IDNO);						// Windowed Mode

	// Create Our OpenGL Window
	if (!CreateGLWindow("Engine Programming",x_res,y_res,32,bFullScreen))
		return 0; // Quit If Window Was Not Created

	while(!done)									// Loop That Runs While done=FALSE
	{
		QueryPerformanceCounter((LARGE_INTEGER*)&currentTime);
		deltaTime=(double)(currentTime-previousTime)*secondsPerCount;

		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))	// Is There A Message Waiting?
		{
			if (msg.message==WM_QUIT)				// Have We Received A Quit Message?
			{
				done=TRUE;							// If So done=TRUE
			}
			else									// If Not, Deal With Window Messages
			{
				TranslateMessage(&msg);				// Translate The Message
				DispatchMessage(&msg);				// Dispatch The Message
			}
		}
		else										// If There Are No Messages
		{
			// Draw The Scene.  Watch For ESC Key And Quit Messages From DrawGLScene()
			if ((active && !DrawGLScene()) || keys[VK_ESCAPE])	// Active?  Was There A Quit Received?
			{
				done=TRUE;							// ESC or DrawGLScene Signalled A Quit
			}
			else									// Not Time To Quit, Update Screen
			{
				SwapBuffers(hDC);					// Swap Buffers (Double Buffering)
			}
			
			UpdateGLScene(deltaTime);

			g.rotate_x(-g_Landscape->TotalRot);
			g.rotate_y((float)xDelta/4);
			g_newRot=g_Landscape->TotalRot+(float)yDelta/4;
			g.rotate_x(g_Landscape->TotalRot+(float)yDelta/4);
			xDelta=0;
			yDelta=0;

			if(!keys[VK_SHIFT])
				g_MaxVelocity=vector(0.02,0.02,0.02);
			else
				g_MaxVelocity=vector(0.1,0.1,0.1);

			g_Acceleration=vector(0,0,0);

			if(keys[VK_UP]||keys['W'])
				g_Acceleration.wz=0.01;
			if(keys[VK_DOWN]||keys['S'])
				g_Acceleration.wz=-0.01;
			if(keys[VK_RIGHT]||keys['D'])
				g_Acceleration.wx=-0.01;
			if(keys[VK_LEFT]||keys['A'])
				g_Acceleration.wx=0.01;

			if(keys[VK_UP]||keys['U'])
				g_DominantDirectionalLight->rotate_z(1);
			if(keys[VK_DOWN]||keys['J'])
				g_DominantDirectionalLight->rotate_z(-1);
			if(keys[VK_RIGHT]||keys['K'])
				g_DominantDirectionalLight->rotate_x(-1);
			if(keys[VK_LEFT]||keys['H'])
				g_DominantDirectionalLight->rotate_x(1);

			if(g_Acceleration.wz==0.0)
				g_Velocity.wz=0.0f;
			if(g_Acceleration.wx==0.0f)
				g_Velocity.wx=0.0f;

			g_Velocity+=g_Acceleration*static_cast<float>(deltaTime);
			if(g_Velocity.wx>g_MaxVelocity.wx) g_Velocity.wx=g_MaxVelocity.wx;
			if(g_Velocity.wy>g_MaxVelocity.wy) g_Velocity.wy=g_MaxVelocity.wy;
			if(g_Velocity.wz>g_MaxVelocity.wz) g_Velocity.wz=g_MaxVelocity.wz;
			if(g_Velocity.wx<-g_MaxVelocity.wx) g_Velocity.wx=-g_MaxVelocity.wx;
			if(g_Velocity.wy<-g_MaxVelocity.wy) g_Velocity.wy=-g_MaxVelocity.wy;
			if(g_Velocity.wz<-g_MaxVelocity.wz) g_Velocity.wz=-g_MaxVelocity.wz;
			g.translate(g_Velocity.wx*deltaTime,g_Velocity.wy*deltaTime,g_Velocity.wz*deltaTime);

			if(keys[VK_F2] && !g_bF2Down)
			{
				g_bF2Down=true;
				g_WireFrameMode=!g_WireFrameMode;
			}
			else if(!keys[VK_F2])
				g_bF2Down=false;

			if(keys[VK_F3] && !g_bF3Down)
			{
				g_bF3Down=true;
				g_DrawNormals=!g_DrawNormals;
			}
			else if(!keys[VK_F3])
				g_bF3Down=false;

			if (keys[VK_F1])						// Is F1 Being Pressed?
			{
				keys[VK_F1]=FALSE;					// If So Make Key FALSE
			}

		}
	}

	// Shutdown
	KillGLWindow();									// Kill The Window
	return (msg.wParam);							// Exit The Program
}