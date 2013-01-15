#ifndef UTILITY_FUNCTIONS
#define UTILITY_FUNCTIONS

#include "gl/glew.h"
#include <stdio.h>
#include "screen_interface.h"

char *load_file( char *filename )
{
  FILE *input = fopen( filename, "rb" );
  if( input == NULL ) exit_error( filename );

  char *content = NULL;
  long file_size = 0;

  fseek( input, 0, SEEK_END );
  file_size = ftell( input );
  rewind( input );

  if( (content = new char[ file_size + 1 ]) == NULL )
    exit_error( "*content: Fehler während der Reservierung von Arbeitsspeicher.\n" );
    
  fread( content, sizeof(char), file_size, input );
  content[ file_size ] = '\0';

  fclose( input );

  return content;
}

void check_shader( GLuint shader )
{
  GLint s;  glGetShaderiv( shader, GL_COMPILE_STATUS, &s );

  if( s == GL_FALSE )
  {
    glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &s );
    if( s > 0 )
    {
      char *text = new char[ s + 50 ];
      if( text == NULL ) exit_nomemory( "check_shader()", "text[]" );
      
      GLint type;
      glGetShaderiv( shader, GL_SHADER_TYPE, &type );
      if( type == GL_VERTEX_SHADER ) sprintf( text, "Der Vertex Shader enthält folgende Fehler:\n\n" );
      else sprintf( text, "Der Fragment Shader enthält folgende Fehler:\n\n" );

      long title_length = strlen( text );
      glGetShaderInfoLog( shader, s, &s, &text[ title_length ] );
      exit_error( text );
    }

    else
    {
      glGetShaderiv( shader, GL_SHADER_TYPE, &s );
      if( s == GL_VERTEX_SHADER ) exit_error( "Unbekannter Fehler im Vertex Shader.\n" );
      exit_error( "Unbekannter Fehler im Fragment Shader.\n" );
    }
  }
}

void check_program( GLuint program, GLenum mode )
{
  GLint s;  glGetProgramiv( program, mode, &s );

  if( s == GL_FALSE )
  {
    glGetProgramiv( program, GL_INFO_LOG_LENGTH, &s );
    if( s > 0 )
    {
      char *text = new char[ s + 100 ];
      if( text == NULL ) exit_nomemory( "check_program()", "text[]" );

      sprintf( text, "Das GLSL-Unterprogramm enthält folgende Fehler:\n\n" );

      long title_length = strlen( text );
      glGetProgramInfoLog( program, s, &s, &text[ title_length ] );
      exit_error( text );
    }

    else exit_error( "Unbekannter Fehler innerhalb des GLSL-Unterprogramms.\n" );
  }
}

GLuint load_program( char *vertex_name, char *fragment_name )
{
  GLuint vertex_shader, fragment_shader, shader_program;

  {
    vertex_shader = glCreateShader( GL_VERTEX_SHADER );

    char *vertex_source = load_file( vertex_name );
    glShaderSource( vertex_shader, 1, (const char **) &vertex_source, NULL );
    if( vertex_source ) delete [] vertex_source;

    glCompileShader( vertex_shader );    check_shader( vertex_shader );
  }

  {
    fragment_shader = glCreateShader( GL_FRAGMENT_SHADER );
  
    char *fragment_source = load_file( fragment_name );
    glShaderSource( fragment_shader, 1, (const char **) &fragment_source, NULL );
    if( fragment_source ) delete [] fragment_source;

    glCompileShader( fragment_shader );  check_shader( fragment_shader );
  }

  {
    shader_program = glCreateProgram();

    glAttachShader( shader_program, vertex_shader );
    glAttachShader( shader_program, fragment_shader );

    glLinkProgram( shader_program );
    check_program( shader_program, GL_LINK_STATUS );

    glValidateProgram( shader_program );
    check_program( shader_program, GL_VALIDATE_STATUS );
  }

  return shader_program;

}

#endif