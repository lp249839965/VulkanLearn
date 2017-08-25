#version 450

#extension GL_ARB_separate_shader_objects : enable
#extension GL_ARB_shading_language_420pack : enable

layout (binding = 1) uniform samplerCube envTex;

layout (location = 0) in vec3 inSampleDir;

layout (location = 0) out vec4 outFragColor;

const float exposure = 4.5;
const float whiteScale = 11.2;
const float gamma = 1.0 / 2.2;

vec3 Uncharted2Tonemap(vec3 x)
{
	float A = 0.15;
	float B = 0.50;
	float C = 0.10;
	float D = 0.20;
	float E = 0.02;
	float F = 0.30;
	return ((x*(A*x+C*B)+D*E)/(x*(A*x+B)+D*F))-E/F;
}

void main() 
{
	vec3 final = texture(envTex, normalize(inSampleDir)).xyz;
	
	final = Uncharted2Tonemap(final * exposure);
	final = final * (1.0 / Uncharted2Tonemap(vec3(whiteScale)));
	final = pow(final, vec3(gamma));

	outFragColor = vec4(final, 1.0);
}