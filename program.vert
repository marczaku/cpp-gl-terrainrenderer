varying vec3 color;

void main()
{
  gl_TexCoord[ 0 ] = gl_MultiTexCoord0;
  gl_TexCoord[ 1 ] = gl_MultiTexCoord1;
  vec3 licht=vec3 (0.0,0.0,-1.0);
  float intensity=dot(normalize(licht),normalize(gl_Normal));
  if(intensity<0.0)
	intensity=0.0;
  //color=vec3(1.0,0.0,0.0)+intensity*vec3(-1.0,1.0,0.0);
// fake ao
  color=(0.2+0.8*intensity)*vec3(1.0,1.0,1.0);
  //color=vec3(1.0,0.0,0.0)+intensity*vec3(-1.0,0.0,1.0);

  gl_Position = ftransform();
}
