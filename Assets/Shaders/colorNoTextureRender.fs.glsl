#version 400 core

out vec4 color;

in VS_OUT
{
    vec3 color;
} fs_out;

	
void main(void)
{
	color = vec4(fs_out.color,1.0); 
}