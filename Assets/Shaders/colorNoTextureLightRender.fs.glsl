#version 400 core

out vec4 color;

in VS_OUT
{
	vec4 vSrcColor;
    vec4 vFragColor;
} vs_out;

	
void main(void)
{
	color = vs_out.vSrcColor * vs_out.vFragColor;
}