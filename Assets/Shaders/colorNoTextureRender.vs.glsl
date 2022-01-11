#version 400 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec3 vColor;

out VS_OUT
{
    vec3 color;
} vs_out;

uniform mat4 world_matrix;
uniform mat4 view_matrix;
uniform mat4 proj_matrix;

void main(void)
{              
    gl_Position = proj_matrix * view_matrix * world_matrix * position;      
    vs_out.color = vColor;
}