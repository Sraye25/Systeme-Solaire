#version 330

uniform sampler2D texture;

in vec2 gs_uv;
in vec4 vcolor;
out vec4 out_fragColor;

void main()
{
   vec4 t = texture2D(texture,gs_uv);

   if(t.a < 0.5) discard;
   //if(t.r == 0.0 && t.g == 0.0 && t.b == 0.0) discard;

   out_fragColor = t;
}
