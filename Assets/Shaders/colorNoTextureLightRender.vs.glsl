#version 400 core

// These come from the model
layout (location = 0) in vec4 vVertex;
layout (location = 1) in vec3 vSourceColor;
layout (location = 2) in vec3 vNormal;

out VS_OUT
{
	vec4 vSrcColor;
    vec4 vFragColor;
} vs_out;

uniform mat4 world_matrix;
uniform mat4 view_matrix;
uniform mat4 proj_matrix;

uniform vec3 vLightPos;
uniform vec4 vColor;

void main(void)
{              
	// Light stuff
	mat4 mvMatrix;
	mvMatrix = view_matrix * world_matrix;

	// Stuff from old super bible, Point light (Diffuse only), with srcColor(modulated)
	mat3 mNormalMatrix;
	mNormalMatrix[0] = normalize(mvMatrix[0].xyz);
	mNormalMatrix[1] = normalize(mvMatrix[1].xyz);
	mNormalMatrix[2] = normalize(mvMatrix[2].xyz);
	vec3 vNorm = normalize(mNormalMatrix * vNormal);
	vec4 ecPosition;
	vec3 ecPosition3;
	ecPosition = mvMatrix * vVertex;
	ecPosition3 = ecPosition.xyz /ecPosition.w;
	vec3 vLightDir = normalize(vLightPos - ecPosition3);
	float fDot = max(0.0, dot(vNorm, vLightDir));

	vs_out.vFragColor.rgb = vColor.rgb * fDot;
	vs_out.vFragColor.a = vColor.a;

	// transform the verts
    gl_Position = proj_matrix * view_matrix * world_matrix * vVertex;      

	// transport the model's souce color to Fragment shader
    vs_out.vSrcColor = vec4(vSourceColor,1.0);
}


//"uniform mat4 mvMatrix;"
//uniform mat4 pMatrix;"
//"uniform vec3 vLightPos;"
//"uniform vec4 vColor;"
//"attribute vec4 vVertex;"
//"attribute vec3 vNormal;"
//"varying vec4 vFragColor;"
//"attribute vec2 vTexCoord0;"
//"varying vec2 vTex;"
												  
//"void main(void) { "
//					 " mat3 mNormalMatrix;"
//					  " mNormalMatrix[0] = normalize(mvMatrix[0].xyz);"
//					  " mNormalMatrix[1] = normalize(mvMatrix[1].xyz);"
//					 " mNormalMatrix[2] = normalize(mvMatrix[2].xyz);"
//					  " vec3 vNorm = normalize(mNormalMatrix * vNormal);"
//					  " vec4 ecPosition;"
//					  " vec3 ecPosition3;"
//					  " ecPosition = mvMatrix * vVertex;"
//					 " ecPosition3 = ecPosition.xyz /ecPosition.w;"
//					  " vec3 vLightDir = normalize(vLightPos - ecPosition3);"
//							" float fDot = max(0.0, dot(vNorm, vLightDir)); "
//						 " vFragColor.rgb = vColor.rgb * fDot;"
//						 " vFragColor.a = vColor.a;"
//						  " vTex = vTexCoord0;"
//						 " mat4 mvpMatrix;"
//						  " mvpMatrix = pMatrix * mvMatrix;"
//						  " gl_Position = mvpMatrix * vVertex; "
//												  "}";
