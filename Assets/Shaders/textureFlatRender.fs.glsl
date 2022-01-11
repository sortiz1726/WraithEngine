#version 400 core

// Not allowed in 400, only 420
// layout (binding = 0) uniform sampler2D tex_object;

const int NumTextures = 4; 
uniform sampler2D tex_object[NumTextures];

in VS_OUT
{
    vec3 textCoordinate;
} fs_in;

out vec4 color;

void main(void)
{
    color = texture(tex_object[ int(fs_in.textCoordinate.z) ], fs_in.textCoordinate.xy );
}


