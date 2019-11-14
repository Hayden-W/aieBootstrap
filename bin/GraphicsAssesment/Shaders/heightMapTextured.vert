#version 400

//Height map

in vec4 vPosition;
in vec4 vColor;
in vec2 vuv;
in vec3 vNormal;

out vec2 fuv;
out vec4 fColor;
out vec3 fNormal;
out vec4 fPosition;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main ()
{
	fColor = vColor;
	fuv = vuv;
	fNormal = vNormal;
	fPosition = vPosition;
	gl_Position = projection * view * model * vPosition;
}
