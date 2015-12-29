#version 330

layout(points) in;
layout(triangle_strip, max_vertices=4) out;

uniform mat4 matrice_projection;

in vec4 color[];

out vec2 gs_uv;
out vec4 vcolor;

void main()
{
    for (int i=0; i<gl_in.length(); i++)
    {
        vcolor = color[0];

        gl_Position = gl_in[i].gl_Position + matrice_projection * (vec4(-3.0,-0.75,0.0,0.0));
        gs_uv = vec2(0.0, 1.0);
        EmitVertex();

        gl_Position = gl_in[i].gl_Position + matrice_projection * (vec4(3.0,-0.75,0.0,0.0));
        gs_uv = vec2(1.0, 1.0);
        EmitVertex();

        gl_Position = gl_in[i].gl_Position + matrice_projection * (vec4(-3.0,0.75,0.0,0.0));
        gs_uv = vec2(0.0, 0.0);
        EmitVertex();

        gl_Position = gl_in[i].gl_Position + matrice_projection * (vec4(3.0,0.75,0.0,0.0));
        gs_uv = vec2(1.0, 0.0);
        EmitVertex();

        EndPrimitive();
    }
}
