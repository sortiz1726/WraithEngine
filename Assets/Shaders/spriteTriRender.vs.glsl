#version 400 core

layout (location = 0) in vec4 position;

uniform mat4 world_matrix;
uniform mat4 view_matrix;
uniform mat4 proj_matrix;
uniform mat4 data_matrix;
             
void main(void)
{
	vec4 v[3];

	// Effectively-------------------------
		// v[0].x = data_matrix[0].x;
		// v[0].y = data_matrix[0].y;
		// v[0].z = 0.0f;
		// v[0].w = 1.0f;

		// v[1].x = data_matrix[1].x;
		// v[1].y = data_matrix[1].y;
		// v[1].z = 0.0f;
		// v[1].w = 1.0f;

		// v[2].x = data_matrix[2].x;
		// v[2].y = data_matrix[2].y;
		// v[2].z = 0.0f;
		// v[2].w = 1.0f;

	// Since the shader can be repeat and divided on a per vertex basis
	// we have no control which one gets attack first, so make it agnostic
	// I can just use v[gl_VertexID] directly

	v[gl_VertexID].x = data_matrix[gl_VertexID].x;
	v[gl_VertexID].y = data_matrix[gl_VertexID].y;
	v[gl_VertexID].z = 0.0f;
	v[gl_VertexID].w = 1.0f;

	// This is Not needed...
	// position[gl_VertexID] = v[gl_VertexID];

	// create the transformed vert
    gl_Position = proj_matrix * view_matrix * world_matrix *  v[gl_VertexID];
	gl_Position.w = 1.0;
}
