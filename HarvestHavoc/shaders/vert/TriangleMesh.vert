#version 450 // GLSL v4.5

layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec3 vNormal;
layout (location = 2) in vec4 vColor;

layout (location = 0) out vec4 outColor;

void main()
{
	gl_Position = vec4(vPosition, 1.0f);
	outColor = vColor;
}