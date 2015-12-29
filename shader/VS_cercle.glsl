#version 330

uniform mat4 matrice_monde;
uniform mat4 matrice_vue;
uniform mat4 matrice_projection;

in vec3 vextexPosition;

void main()
{
    vec4 position_monde = matrice_monde * vec4(vextexPosition, 1.0f);
    gl_Position = matrice_projection * matrice_vue * position_monde;
}
