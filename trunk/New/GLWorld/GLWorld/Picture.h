// Picture.h

#pragma once

#include "Color.h"
#include <stdio.h>

typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned long ulong;

class Picture
{
private:
	void LoadBmp8( FILE *bmp_file );
	void LoadBmp24( FILE *bmp_file );

public:
	long xsize, ysize;
	Color *content;

	void Load( char *filename );

	Picture( void ) : xsize( 0 ), ysize( 0 ), content( NULL ) { }
	Picture( char *filename ) {  Load( filename );  }
	~Picture( void ) {  if( content ) delete [] content;  }  

protected:
	Picture( const Picture &p ) {}
};