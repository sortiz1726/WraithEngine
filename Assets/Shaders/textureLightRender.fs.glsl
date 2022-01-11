#version 400 core

// Not allowed in 400, only 420
// layout (binding = 0) uniform sampler2D tex_object;

// Uniforms
	const int NumTextures = 4; 
	uniform sampler2D tex_object[NumTextures];

// Varying
	in VS_OUT
	{
		vec4 vFragColor;
		vec3 vTex;
	} fs_in;

	out vec4 color;

void main(void) 
{ 
	color = fs_in.vFragColor * texture(tex_object[ int(fs_in.vTex.z) ], fs_in.vTex.xy );
}
