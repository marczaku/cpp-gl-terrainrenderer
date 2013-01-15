uniform sampler2D surface_texture;
uniform vec3 DominantLightDirection;

varying vec3 normal;

void main()
{
  vec3 licht=DominantLightDirection;
  float intensity=dot(normalize(licht),normalize(normal));
  if(intensity<0.0)
	intensity=0.0;
  vec3 color1 = vec3( texture2D( surface_texture, gl_TexCoord[ 0 ].st ) );
  vec3 EndColor = intensity*color1;
  gl_FragColor = vec4(EndColor,1.0);
}
