#version 400 core

in vec4 position;

out VS_OUT
{
    vec4 color;
} vs_out;

uniform mat4 world_matrix;
uniform mat4 view_matrix;
uniform mat4 proj_matrix;
uniform vec4 wire_color;

void main(void)
{              
    gl_Position = proj_matrix * view_matrix * world_matrix * position;      
    vs_out.color = wire_color;
}