#version 330

uniform mat4 matrice_monde;
uniform mat4 matrice_vue;
uniform mat4 matrice_projection;

uniform mat4 matrice_normal;

uniform vec3 position_lumiere;
uniform vec3 position_camera;

in vec3 vextexPosition;
in vec3 vertexNormal;
in vec2 vextexTexcoor;

out vec3 vs_normal;
out vec3 vs_camera;
out vec3 vs_lumiere;
out vec2 vs_vertexTexCoor;

void main()
{
    vec4 position_monde = matrice_monde * vec4(vextexPosition, 1.0f);
    gl_Position = matrice_projection * matrice_vue * position_monde;

    vs_vertexTexCoor = vextexTexcoor;
}
