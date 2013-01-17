varying vec3 normal;
varying vec3 pos;
attribute float w1,w2,w3,w4;

varying float outw1,outw2,outw3,outw4;

void main()
{
  gl_TexCoord[ 0 ] = gl_MultiTexCoord0;
  gl_TexCoord[ 1 ] = gl_MultiTexCoord1;
  normal = gl_NormalMatrix * gl_Normal;

  //gl_Position = gl_Modelview * gl_Projection * gl_Vertex;

  pos = gl_ModelViewMatrix * gl_Vertex;
  gl_Position = ftransform();

  outw1=w1;
  outw2=w2;
  outw3=w3;
  outw4=w4;
}
