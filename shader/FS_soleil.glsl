#version 330

uniform sampler2D texture;

in vec2 vs_vertexTexCoor;

out vec4 out_fragColor;

void main()
{
   vec3 ITex = texture2D(texture,vs_vertexTexCoor).rgb;
   out_fragColor = vec4(ITex,1.0f);
}
