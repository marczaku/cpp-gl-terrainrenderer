uniform sampler2D surface_texture;
uniform vec3 DominantLightDirection;

varying vec3 pos;
varying vec3 normal;

void main()
{
  vec4 diff;
  vec4 spec;

  // Calculate diffuse value
  float intensity=dot(normalize(DominantLightDirection),normalize(normal));
  if(intensity<0.0)
	intensity=0.0;
  diff = vec4( texture2D( surface_texture, gl_TexCoord[ 0 ].st ));

  //Calculate specular value
  float specular_power=40;
  vec3 v = -pos;
  v=normalize(v);
  vec3 r = reflect(normalize(DominantLightDirection),normalize(normal));
  r=normalize(r);
  if (specular_power != 0.0) {
    spec = vec4(1.0,1.0,1.0,1.0) * pow(max(0.0,dot(r, v)), specular_power);
  } else {
    spec = vec4(0.0, 0.0, 0.0, 0.0);
  }

  gl_FragColor = intensity*vec4(0.5,0.5,0.5,1.0)+spec;
}
