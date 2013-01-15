#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>

#include "screen_interface.h"

MSG msg;
unsigned char key_pressed( void );

int WINAPI WinMain( HINSTANCE hinst, HINSTANCE pinst, LPSTR cmdl, int cmds )
{
  screen_interface.open_window( hinst, 640, 480 );

  while( 1 )
  {
    if( key_pressed() ) break; 

    glBegin( GL_POINTS );

      GLubyte c = rand() % 256;
      GLdouble sx = rand() % x_res;
      GLdouble sy = rand() % y_res;

      glColor3ub( c, c, c );
      glVertex2d( sx, sy );

    glEnd();

	glFlush();
  }

  return msg.wParam;
}

unsigned char key_pressed( void )
{
  if( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
  {
    if( msg.message == WM_QUIT || msg.message == WM_KEYDOWN ) return 1;

    TranslateMessage( &msg );
    DispatchMessage( &msg );
  }

  return 0;
}
