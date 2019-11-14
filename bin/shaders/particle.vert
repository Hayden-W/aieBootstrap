#version 400

in vec3 position;
in vec4 vColor;
in vec2 vuv;

uniform mat4 projectionView;

out vec4 fColor;
out vec2 fuv;

void main()
{
	fColor = vColor;
	fuv = vuv;
	gl_Position = projectionView * vec4(position, 1);
}