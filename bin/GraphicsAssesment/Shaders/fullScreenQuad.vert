#version 400

//FULLSCREEN QUAD

in vec3 vPosition;
in vec4 vColor;
in vec2 vuv;

out vec2 fuv;

void main()
{
	fuv = vuv;
	gl_Position = vec4(vPosition, 1);
} 

