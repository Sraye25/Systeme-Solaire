#version 330

uniform mat4 matrice_monde;
uniform mat4 matrice_vue;
uniform mat4 matrice_projection;

in vec3 position;
out vec4 color;

void main()
{
    vec4 position_monde = matrice_monde * vec4(position, 1.0f);
    gl_Position = matrice_projection * matrice_vue * position_monde;

    color = vec4(1.0f,1.0f,1.0f,1.0f);
}
