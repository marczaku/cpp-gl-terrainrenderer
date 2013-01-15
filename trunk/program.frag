uniform sampler2D surface_texture;
uniform sampler2D surface_texture2;
uniform sampler2D weight_texture;
uniform float	  time;

varying vec3 color;

void main()
{
  vec3 color1 = vec3( texture2D( surface_texture, gl_TexCoord[ 0 ].st ) );
  vec3 color2 = vec3( texture2D( surface_texture2, gl_TexCoord[ 0 ].st ) );
  vec3 weight = vec3( texture2D( weight_texture, gl_TexCoord[ 1 ].st ) );

  vec3 EndColor = color.x*vec3( (color1*(1-weight.x)+color2*weight.x)*(1-time)+(color2*(1-weight.x)+color1*weight.x)*(time));

  gl_FragColor = vec4(EndColor,1.0);

    //gl_FragColor=color.x*vec4(color,1.0);
}
