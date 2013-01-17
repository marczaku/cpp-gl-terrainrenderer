uniform sampler2D tex1,tex2,tex3,tex4;
uniform vec3 DominantLightDirection;

varying vec3 pos;
varying vec3 normal;

varying float outw1,outw2,outw3,outw4;

void main()
{
  vec4 diff;
  vec4 spec;

  // Calculate diffuse value
  float intensity=dot(normalize(DominantLightDirection),normalize(normal));
  if(intensity<0.0)
	intensity=0.0;
  //diff = vec4( texture2D( surface_texture, gl_TexCoord[ 0 ].st ));
  diff =intensity*( 
outw1*vec4(vec4( texture2D( tex1, gl_TexCoord[ 0 ].st )))+
outw2*vec4( texture2D( tex2, gl_TexCoord[ 0 ].st ))+
outw3*vec4( texture2D( tex3, gl_TexCoord[ 0 ].st ))+
outw4*vec4( texture2D( tex4, gl_TexCoord[ 0 ].st )));

  diff =intensity*( 
outw1*vec4(vec4( texture2D( tex1, gl_TexCoord[ 0 ].st )))+
outw2*vec4( texture2D( tex2, gl_TexCoord[ 0 ].st ))+
outw3*vec4( texture2D( tex3, gl_TexCoord[ 0 ].st ))+
outw4*vec4( texture2D( tex4, gl_TexCoord[ 0 ].st )));
//outw1*vec4(vec4(0.0,0.0,0.0,1.0))+
//outw2*vec4(vec4(1.0,0.0,0.0,1.0))+
//outw3*vec4(vec4(0.0,0.0,0.0,1.0))+
//outw4*vec4(vec4(0.0,0.0,1.0,1.0));


  //Calculate specular value
  float specular_power=0;
  vec3 v = -pos;
  v=normalize(v);
  vec3 r = reflect(normalize(DominantLightDirection),normalize(normal));
  r=normalize(r);
  if (specular_power != 0.0) {
    spec = vec4(1.0,1.0,1.0,1.0) * pow(max(0.0,dot(r, v)), specular_power);
  } else {
    spec = vec4(0.0, 0.0, 0.0, 0.0);
  }

  gl_FragColor = diff+spec;
}
